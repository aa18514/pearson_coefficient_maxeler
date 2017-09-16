# PEARSON COEFICIENT EVALUATOR

For more information on how the pearson coefficient is evaluated please visit:

https://en.wikipedia.org/.../Pearson_correlation_coefficient

The dataset consisting of 100,000 points has been randomly generated using C++, the chrono library is then used to measure time elapsed 
for the function callfor the DFE evaluation. The performance consists of the following components:<br>
<br> a) stream run-time 
<br> b) time to read/write on-card memory 
<br> c) time to transfer data over the PCI Express Bus 
<br> d) inter-fpga communication

Due to limited hardware, it is assumed that only a single board is used for the the calculation. Further to this, we look at transferring data over the PCI Express bus, as well generation of data from DDR. We expect to the results from DDR to be much more better than results evaluated over the PCI Express bus, as the maximum theoritical bandwith for reading-writing on-card memory (37.5 GBps) is much greater than the regular PCIE bandwith (19 GBps).
We will also look at mixed precision, which allows for better utilization of resources, and better scalability. Target platform used is MAX3424A board. MAIA platform has not been used due to limited hardware available.

## Inputs
The inputs to the board were initially 32-bit floating point streams of data namely x and y. The data is generated randomly from the script generate_dataset.cpp. Data value should not exceed 4294967295 as it leads to an overflow and an incorrect evaluation of final results. Both 1/SAMPLE_SIZE and SAMPLE_SIZE are loaded as Scalar Inputs with a complexity of O(1) to avoid the unnecessary division.

## Strategies
Analysing the distribution of data: 

![Alt text] (https://github.com/aa18514/pearson_coefficient_maxeler/data_distribution.JPG?raw=true "Optional Title") <br>
An insight into the data distribution gives us useful information - it tells us that sending 4 bytes per a single data point is wasteful, and that full use of variable word lengths should be exploited. For example, for one-bit data points, one can wrap 32 data points instead of one data point in a 32 bit word. 
Data compression techniques such as delta encoding (https://en.wikipedia.org/wiki/Delta_encoding) can assist in reducing data transfer over the PCIE bus while at the same time reducing the number of compute cycles for which the kernel runs at. Another strategy to reduce the number of BRAMs synthesized is to fuse different weight vectors by effectively structuring memory.

## Methodology
So far two methods have been tested and the results have been evaluated succesfully. <br> 

### Method 1
The first method involves using a feedback loop, however in order to cater for the floating point latency, there is a stall of 15 cycles before new input is accepted. This method does not scale well as the kernel must run for a total of 100,000 * 15 cycles but consumes fewer resources.

### Method 2
Instead of stalling for 15 cycles before accepting new input as described in method 1, it is also possible to let the data flow naturally, and accumulate the partial sums every M cycles, where M is a divisor of SAMPLE_SIZE. This consumes slightly more hardware resources but has the advantage of requiring only 100000 (single pipe).

| Pipes | M | LUT Consumption | FF Consumption | DSP consumption | BRAM consumption |
| :---: | :---: | :---: | :---: | :---: | :---: |  
| 1 | 5 | 4.76 % | 5.40 % | 0.60 % | 1.46% |

But why stop there? By partitioning data into sets of 1 bit, 2 bits, 4 bits and 8 bits and constructing data packets with variable encoding, we are able to take the total number of cycles from 100,000 to 21020, processing 60 data points in parallel. Further to this, opening by opening 5 PCIE pipes, we now process 300 data points simultaneously taking the total number of computation cycles from 100,000 to just 4204 cycles (~95.79% reduction in kernel execution time and ~79.1% reduction in PCIE data transfer time). Following number of resources are being used:

| Pipes | M | LUT Consumption | FF Consumption | DSP consumption | BRAM consumption |
| :---: | :---: | :---: | :---: | :---: | :---: |  
| 4 | 5 | 10.67 % | 12.35 % | 3.17 % | 15.08 % |

By using delta encoding we are able to further reduce the total number of cycles from 4204 to 1668.
The % increase in BRAM is due to the x-coordinate with range, 1 < x < 100000 is generated from on - chip memory. 

### Method 3
The following method requires some pre-processing of data. It then transforms the data into log - domain. This converts a multiplication into addition and a division into a quite cheap subtraction. Furthermore, for |x| < 1, log(1 + x) can be approximated as 1 + x, the results then come back as powers of 2, but replacing the division and multiplication by simple addition and subtraction leads to efficient resource utilization, and allows for much greater parallelism.

## Results
Simple Interface takes a total of 0.0044 seconds @ operating frequncy 75 MHz. 
It is possible to decouple data transfer over the PCIE bus and the kernel computation by using Advanced Static Interface. This turns out to be exactly 0.00184 seconds @ operating frequency 75 MHz, which is close to the estimated time that it takes for the kernel to run. This shows that the performance is PCIE bound. 
