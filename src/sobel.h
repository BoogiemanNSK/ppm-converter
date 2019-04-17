#include <time.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>

#include "structures.h"

int sobel(struct image *in, struct image *out, int threads);