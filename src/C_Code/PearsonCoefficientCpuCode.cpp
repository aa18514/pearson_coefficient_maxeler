#include "Maxfiles.h" 		
#include <MaxSLiCInterface.h>	
#include "PearsonCoefficient.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <chrono>
#define SAMPLE_SIZE 100000
#define FILE_PATH "/mnt/data/cccad3/aa18514/pearson_coefficient/first_layer_done/pearson_coefficient_maxeler/src/C_Code/data.csv"
#define OUTPUT_SIZE 4
/* 
 * for more information on how regression coefficient is calculated please have a look at pearson coefficient evaluation 
 *
 * 
 */

using namespace std; 

double calculate_throughput(float duration, float C){
	return 1; 
}
double calculate_pearson_coefficient(float* x, float * y, float* computed_result){
	double  sum_xy = 0; 
	double sum_xx = 0; 
	double sum_yy = 0; 
	double sum_y = 0; 
	long long int sum_x = 0;
	for(int i = 0; i < SAMPLE_SIZE; i++){
		sum_x +=   x[i];
		sum_y +=   y[i];
		sum_xx +=  x[i] * x[i];
		sum_yy +=  y[i]  * y[i];
		sum_xy +=  x[i] * y[i];
	}
	float numerator = (float((sum_xy) - (((1/(SAMPLE_SIZE)) * sum_x * sum_y))));
	float denominator = (sum_xx - (1/SAMPLE_SIZE) * sum_x * sum_x) * (sum_yy - (1/SAMPLE_SIZE) * sum_y * sum_y); 	
	return numerator/sqrt(denominator);
}

int main()
{

	float* pc_y_data = new float[SAMPLE_SIZE]; 
	float* pc_x_data = new float[SAMPLE_SIZE]; 
	float* x_data_8_bits = new float[21020];
	float* x_data_2_bits = new float[21020]; /* zero padded - actual size 800 */ 
	float* x_data_4_bits = new float[21020]; /* zero padded  - actual size 12000 */
	float* x_data_1_bit = new float[21020] ;
	float* data = new float[16816]; 
	float* data_1 = new float[16816];
	float* data_2 = new float[16816]; 
	float* data_3 = new float[16816];
	float* data_4 = new float[16816];
	float* result = new float[OUTPUT_SIZE]; 
	float* result4 = new float[OUTPUT_SIZE]; 
	int one_bit = 0; 
	int two_bits = 0; 
	int four_bits = 0; 
	int three_bits = 0; 
	int eight_bits = 0; 
	float a, b;
	int shift = 0; 
	int shift_two = 0; 
	int shift_three = 0;
	int shift_four = 0; 
	int shift_one = 0;  
	int p = 0; 
	int q = 0; 
	int r = 0; 
	int s = 0; 
	int o = 0; 
	int one = 0;
	int two = 0;  
	int three = 0; 
	int four = 0; 
	int sg = 0; 
	ifstream ifs(FILE_PATH); 
	while(ifs >> a >> b){
		pc_x_data[sg] = a; 
		pc_y_data[sg] = b; 
		if(b < 2){
			if((p % 32) == 0){
				shift_one = 0; 
				one = one + 1; 
			}
			if(shift_one == 0)
				x_data_1_bit[one] = b; 
			else
				x_data_1_bit[one] = int(x_data_1_bit[one]) | ((int(b) >> shift_one)); 
			one_bit += 1;
			shift_one += 1;
			p += 1;  
		}
		else if(b > 1 && b < 4){
			if((q % 16) == 0){
				shift_two = 0; 
				two = two + 1; 
			}
			if(shift_two == 0)
				x_data_2_bits[two] = b; 
			else
				x_data_2_bits[two] = int(x_data_2_bits[two]) | ((int(b) >> (2 * shift_two))); 
			two_bits += 1; 
			shift_two += 1; 
			q += 1;
		}
		else if(b > 3 && b < 16){
			if((r % 8) == 0){
				shift_three = 0;
				three = three + 1; 
			}
			if(shift_four == 0)
				x_data_4_bits[three] = b; 
			else
				x_data_4_bits[three] = int(x_data_4_bits[three]) | ((int(b) >> (8 * shift_three))); 
			shift_three += 1;  
			three_bits  += 1;
			r += 1;  
		}
		else if(b > 15 && b < 256){
			if((s % 4) == 0){
				shift = 0; 
				four += 1; 
			}
			if(shift == 0)
				x_data_8_bits[four] = b; 
			else
				x_data_8_bits[four] = int(x_data_8_bits[four]) | ((int(b) >> (4 * shift))); 
			s += 1; 
			eight_bits += 1;
			shift += 1;
		}
		else{
			o = o + 1;
		}
	sg = sg + 1; 
	}
	
	int lund_mera = 0; 	
	for(int i = 0; i < 21020/5; i++){
		data[4*i] = x_data_1_bit[i];
		data[4*i + 1] = x_data_2_bits[i]; 
		data[4*i + 2] = x_data_4_bits[i];
		data[4*i + 3] = x_data_8_bits[i];
	}
	
	for(int i = 21020/5; i < (2*21020)/5; i++){
		data_1[lund_mera] = x_data_1_bit[i];
		data_1[lund_mera + 1] = x_data_2_bits[i]; 
		data_1[lund_mera + 2] = x_data_4_bits[i]; 
		data_1[lund_mera + 3] = x_data_8_bits[i]; 
		lund_mera = lund_mera + 4; 
	}
	lund_mera = 0; 
	
	for(int i = (2 * 21020)/5; i < (3 * 21020)/5; i++){
		data_2[lund_mera] = x_data_1_bit[i]; 
		data_2[lund_mera + 1] = x_data_2_bits[i]; 
		data_2[lund_mera + 2] = x_data_4_bits[i]; 
		data_2[lund_mera + 3] = x_data_8_bits[i];
		lund_mera = lund_mera + 4;  
	}
	
	lund_mera = 0; 
	for(int i = (3 * 21020)/5; i < (4 * 21020)/5; i++){
		data_3[lund_mera] = x_data_1_bit[i]; 
		data_3[lund_mera + 1] = x_data_2_bits[i]; 
		data_3[lund_mera + 2] = x_data_4_bits[i]; 
		data_3[lund_mera + 3] = x_data_8_bits[i]; 
		lund_mera = lund_mera + 4; 
	}
	
	lund_mera = 0; 
	for(int i = (4 * 21020)/5; i < (5 * 21020)/5; i++){
		data_4[lund_mera] = x_data_1_bit[i]; 
		data_4[lund_mera + 1] = x_data_2_bits[i]; 
		data_4[lund_mera + 2] = x_data_4_bits[i]; 
		data_4[lund_mera + 3] = x_data_8_bits[i];
		lund_mera = lund_mera + 4; 
	}
	lund_mera = 0; 
 
	float total_time = 0; 
	struct timeval tv, tb; 
	max_file_t* mavMaxFile = PearsonCoefficient_init();
	max_engine_t* engine = max_load(mavMaxFile, "local:*"); 
	max_actions_t* actions = max_actions_init(mavMaxFile, "default"); 
	
	max_queue_input(actions, "x1", data,   16816 * 4);
	max_queue_input(actions, "x2", data_1, 16816 * 4); 
	max_queue_input(actions, "x3", data_2, 16816 * 4); 
	max_queue_input(actions, "x4", data_3, 16816 * 4); 
 	max_queue_input(actions, "x5", data_4, 16816 * 4); 

	max_queue_output(actions, "y01", result, OUTPUT_SIZE * 4); 
	max_set_param_double(actions, "sample_size", 1/100000); 
	max_set_ticks(actions, "PearsonCoefficientKernel", 4204);
	max_disable_validation(actions); 
	gettimeofday(&tv, NULL);	
	max_run(engine, actions);
	float pearson_coefficient = sqrt(result[3]); 
	gettimeofday(&tb, NULL);
	max_actions_free(actions); 
	max_unload(engine); 
	max_file_free(mavMaxFile);
	cout << ((((unsigned long long)tb.tv_sec - ((unsigned long long)tv.tv_sec)) + (((tb.tv_usec) - (tv.tv_usec))/1e6))) << endl;
	auto Start = std::chrono::high_resolution_clock::now();
	float pc_coefficent = calculate_pearson_coefficient(pc_x_data, pc_y_data, result);
	auto End = std::chrono::high_resolution_clock::now(); 
	cout << chrono::duration_cast<chrono::microseconds>(End - Start).count()/1e6 << endl;
	//printf("CPU implementation took %fs \n", chrono::duration_cast<chrono::nanoseconds>(End - Start).count()); 
	printf("Answer evaluation in CPU %f \n", pc_coefficient);  
	cout << "one bit: " << float(one_bit) << endl; 
	cout << "two bits:    " << float(two_bits) << endl; 
	cout << "four bits:   " << float(three_bits) << endl;
	cout << "eight bits:  " << float(eight_bits) << endl;
	cout << "overflow:    " << o << endl;
	return 0;
}
