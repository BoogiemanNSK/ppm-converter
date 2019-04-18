#include <time.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "structures.h"

#define KERNEL_SIZE 3

int sobel(struct image *in, struct image *out, int threads);
int** convolution(int kernel[KERNEL_SIZE][KERNEL_SIZE], 
		int **origin, int origin_width, int origin_height);