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

	hipMemcpy(totalTime_d, totalTime, sizeof(clock_t), hipMemcpyDeviceToHost);
	hipDeviceSynchronize();

	for(int i =0; i < 1000; i++)
		asm_add<<<1, 1, 0,  0>>>(totalTime_d); 

	hipDeviceSynchronize();
	hipMemcpy(totalTime, totalTime_d, sizeof(clock_t), hipMemcpyHostToDevice);

	printf("number of cycle = %d \n", *totalTime);


	free(totalTime);
	free(h_b);
	hipFree(totalTime_d);
	hipFree(d_a);
	hipFree(d_b);
	return 0;

}
