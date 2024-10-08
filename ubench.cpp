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

	

register float register0  asm("v0");
register float register1 asm("v1");
register float register2 asm("v2");
register float register3 asm("v3");
register float register4 asm("v4");
register float register5 asm("v5");
register float register6 asm("v6");
register float register7 asm("v7");
register float register8 asm("v8");
register float register9  asm("v9");
register float register10 asm("v10");
register float register11 asm("v11");
register float register12 asm("v12");
register float register13 asm("v13");
register float register14 asm("v14");
register float register15 asm("v15");
register float register16 asm("v16");
register float register17 asm("v17");
register float register18 asm("v18");
register float register19 asm("v19");
register float register20 asm("v20");
register float register21 asm("v21");
register float register22 asm("v22");
register float register23 asm("v23");
register float register24 asm("v24");
register float register25 asm("v25");
register float register26 asm("v26");
register float register27 asm("v27");
register float register28 asm("v28");
register float register29 asm("v29");
register float register30 asm("v30");
register float register31 asm("v31");
register float register32 asm("v32");
register float register33 asm("v33");
register float register34 asm("v34");
register float register35 asm("v35");
register float register36 asm("v36");







start = clock();
__asm__ volatile("s_waitcnt vmcnt(0)");
__asm__ volatile("s_memtime %0\n\t" : "=s"(start));
for(int i =0; i < 1000; i++)
{
__asm__ volatile("v_mul_f32  %0 ,%9 ,%10 \n\t" 
	"v_mul_f32  %1 ,%11 ,%12 \n\t" 
	"v_mul_f32  %2 ,%13 ,%14 \n\t" 
	"v_mul_f32  %3 ,%15 ,%16 \n\t" 
	"v_mul_f32  %4 ,%17 ,%18 \n\t" 
	"v_mul_f32  %5 ,%19 ,%20 \n\t" 
	"v_mul_f32  %6 ,%21 ,%22 \n\t" 
	"v_mul_f32  %7 ,%23 ,%24 \n\t" 
	"v_mul_f32  %8 ,%25 ,%26 \n\t" 
	//output
	:"=v"(register0),
"=v"(register1),
"=v"(register2),
"=v"(register3),
"=v"(register4),
"=v"(register5),
"=v"(register6),
"=v"(register7),
"=v"(register8)
//intput
:"v"(register0), "v"(register10),
"v"(register1), "v"(register11),
"v"(register2), "v"(register12),
"v"(register3), "v"(register13),
"v"(register4), "v"(register14),
"v"(register5), "v"(register15),
"v"(register6), "v"(register16),
"v"(register7), "v"(register17),
"v"(register8), "v"(register18)
	//clobber
: "cc","memory",
"v0", "v1" ,"v2","v3", 
"v3" ,"v5" ,"v6", 
"v7" , "v8" ,"v9", 
"v10" ,"v11" ,"v12", 
"v13" ,"v14" ,"v15", 
"v16" ,"v17" ,"v18",
"v19" ,"v20" ,"v21",
"v22" ,"v23" ,"v24",
"v25" ,"v26" ,"v27",
"v28", "v29", "v30",
"v31", "v32", "v33",
"v34", "v35");


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
