#include "sobel.h"

int sobel(struct image *in, struct image *out, int threads)
{
	clock_t begin = clock();
  
	// TODO

  	clock_t end = clock();
  	printf("Time taken: %.1f ms\n", 1000.0f * ((float)(end - begin) / CLOCKS_PER_SEC));
  	return 0;
}