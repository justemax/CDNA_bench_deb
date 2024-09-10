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

	

