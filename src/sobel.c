#include "sobel.h"

int sobel(struct image *in, struct image *out, int threads)
{
	clock_t begin = clock();

	int gx_kernel[KERNEL_SIZE][KERNEL_SIZE] =
		{{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
	int gy_kernel[KERNEL_SIZE][KERNEL_SIZE] =
		{{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
	
	int **origin = (int**)malloc(sizeof(int*) * in->height);
	for (int i = 0; i < in->height; i++) {
		origin[i] = (int*)malloc(sizeof(int) * in->width);
		for (int j = 0; j < in->width; j++) {
			origin[i][j] = (in->matrix[i][j]->r +
					in->matrix[i][j]->g + 
					in->matrix[i][j]->b) / 3;
		}
	}

	int **gx = convolution(gx_kernel, origin, in->width, in->height);
	int **gy = convolution(gy_kernel, origin, in->width, in->height);

	int res;
	for (int i = 0; i < out->height; i++) {
		for (int j = 0; j < out->width; j++) {
			res = sqrt(gx[i][j] * gx[i][j] + gy[i][j] * gy[i][j]);
			res = res < in->max_val ? res : out->max_val;
			out->matrix[i][j]->r = res;
			out->matrix[i][j]->g = res;
			out->matrix[i][j]->b = res;
		}
	}

	free(gx);
	free(gy);
	free(origin);

  	clock_t end = clock();
  	printf("Time taken: %.1f ms\n", 1000.0f * ((float)(end - begin) / CLOCKS_PER_SEC));
  	return 0;
}

int **convolution(int kernel[KERNEL_SIZE][KERNEL_SIZE],
		int **origin, int origin_width, int origin_height)
{
	int **result = (int**)malloc(sizeof(int*) * origin_height);
	for (int i = 0; i < origin_height; i++) {
		result[i] = (int*)malloc(sizeof(int) * origin_width);
		for (int j = 0; j < origin_width; j++) {
			result[i][j] = 0;
			for (int a = 0; a < KERNEL_SIZE; a++) {
				for (int b = 0; b < KERNEL_SIZE; b++) {
					int x = j - b + 1;
					int y = i - a + 1;
					
					x = x >= 0 ? x : 0;
					x = x < origin_width ? x : origin_width - 1;

					y = y >= 0 ? y : 0;
					y = y < origin_height ? y : origin_height - 1;
					
					result[i][j] += kernel[a][b] * origin[y][x];
				}
			}
		}
	}

	return result;
}