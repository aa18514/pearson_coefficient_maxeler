#include <iostream> 
#include <fstream> 
#include <chrono> 
#include <stdlib.h> 
#include <omp.h> 
using namespace std; 
#define SAMPLE_SIZE 100000
int main(){
	std::ofstream file_opener; 
	file_opener.open("data.csv", std::ofstream::out | std::ofstream::app);
	int data[SAMPLE_SIZE]; 
	auto Start = std::chrono::high_resolution_clock::now(); 
	#pragma omp parallel for 
	for(int i = 0; i < SAMPLE_SIZE; i++){
		double a = 24; 
	}
	auto Finish = std::chrono::high_resolution_clock::now(); 
	cout << chrono::duration_cast<chrono::nanoseconds>(Finish - Start).count()/1E9 << endl; 
	Start = std::chrono::high_resolution_clock::now(); 
	for(int i = 0; i < SAMPLE_SIZE; i++){
		double a = 24 ; 
	}
	Finish = std::chrono::high_resolution_clock::now(); 
	cout << chrono::duration_cast<chrono::nanoseconds>(Finish - Start).count()/1E9 << endl; 
	for(int i =0; i < SAMPLE_SIZE; i++){
		file_opener << i << " " << (rand() % 100) << endl; 
	}
	return 0; 
}
