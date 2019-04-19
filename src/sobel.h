#include <time.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "structures.h"

#define KERNEL_SIZE 3

// Pre-calculated grayscale pixels
int **origin;

void sobel(struct image *in, int threads);
void * convolution(void *args);