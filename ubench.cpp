#include <hip/hip_runtime.h>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define NBREP 1

__global__  void asm_add(clock_t *totalTime)
{
	clock_t start, stop;

	

double register0 = 99 ;
double register1 = 2 ;
double register2 = 3 ;
double register3 = 4 ;
double register4 = 5 ;
double register5 = 6 ;
double register6 = 7 ;
double register7 = 8 ;
double register8 = 9 ;
double register9 = 25 ;
double register10 = 243 ;
double register11 = 223 ;
double register12 = 22 ;
double register13 = 298 ;
double register14 = 244 ;
double register15 = 212 ;
double register16 = 144 ;
double register17 = 744 ;
double register18 = 754 ;
double register19 = 544 ;
__asm__ volatile("s_waitcnt vmcnt(0)");
start = clock();
for(int i =0; i < 1000; i++)
{
__asm__ volatile("v_mul_f64  %0 ,%9 ,%10 \n\t" 
	"v_mul_f64  %1 ,%11 ,%12 \n\t" 
	"v_mul_f64  %2 ,%13 ,%14 \n\t" 
	"v_mul_f64  %3 ,%15 ,%16 \n\t" 
	"v_mul_f64  %4 ,%17 ,%18 \n\t" 
	"v_mul_f64  %5 ,%19 ,%20 \n\t" 
	"v_mul_f64  %6 ,%21 ,%22 \n\t" 
	"v_mul_f64  %7 ,%23 ,%24 \n\t" 
	"v_mul_f64  %8 ,%25 ,%26 \n\t" 
//	"v_mul_f64  %9 ,%28 ,%29 \n\t" 
	:"=v"(register0),
"=v"(register1),
"=v"(register2),
"=v"(register3),
"=v"(register4),
"=v"(register5),
"=v"(register6),
"=v"(register7),
"=v"(register8)
//"=v"(register9)
:"v"(register0), "v"(register10),
"v"(register1), "v"(register11),
"v"(register2), "v"(register12),
"v"(register3), "v"(register13),
"v"(register4), "v"(register14),
"v"(register5), "v"(register15),
"v"(register6), "v"(register16),
"v"(register7), "v"(register17),
"v"(register8), "v"(register18)
//"v"(register9), "v"(register19)
);
}

	stop = clock();


	printf("%ld, %ld, %f\n", start, stop, (double)(stop-start)/NBREP);
	*totalTime = stop-start;

}


void checkHipError(hipError_t err, const char* message) {
        if (err != hipSuccess) {
                std::cerr << message << ": " << hipGetErrorString(err) << std::endl;
                exit(-1);
        }
}


int main(void)
{

	uint32_t *d_a,*d_b;
	uint32_t *h_b;
	h_b = (uint32_t*)malloc(sizeof(uint32_t));

	hipMalloc(&d_a, sizeof(uint32_t));
	hipMalloc(&d_b, sizeof(uint32_t));

	
	clock_t *totalTime = (clock_t*)malloc(sizeof(clock_t));
	*totalTime = 0;
	clock_t *totalTime_d;
	hipMalloc(&totalTime_d, sizeof(clock_t));

	hipMemcpy(totalTime, totalTime_d, sizeof(clock_t), hipMemcpyDeviceToHost);

	for(int i =0; i < 10000; i++)
		asm_add<<<1, 1, 0,  0>>>(totalTime_d); 
//	checkHipError(hipLaunchKernelGGL(asm_add, 1, 1, 0, 0,  d_a, d_b, totalTime_d), "error"); 

	//hipDeviceSynchronize();
	hipMemcpy(totalTime, totalTime_d, sizeof(clock_t), hipMemcpyDeviceToHost);
	hipMemcpy(h_b, d_b, sizeof(uint32_t), hipMemcpyDeviceToHost);


	printf("b = %d", *h_b);
	printf("time = %ld \n", (double)(*totalTime/NBREP));
	free(totalTime);
	free(h_b);
	hipFree(totalTime_d);
	hipFree(d_a);
	hipFree(d_b);
	return 0;

}
