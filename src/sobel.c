#include "sobel.h"

const int gx_kernel[KERNEL_SIZE][KERNEL_SIZE] =
		{{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
const int gy_kernel[KERNEL_SIZE][KERNEL_SIZE] =
		{{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

void sobel(struct image *in, int threads)
{
	clock_t begin = clock();

	origin = (int**)malloc(sizeof(int*) * in->height);
	for (int i = 0; i < in->height; i++) {
		origin[i] = (int*)malloc(sizeof(int) * in->width);
		for (int j = 0; j < in->width; j++) {
			origin[i][j] = (in->matrix[i][j]->r +
					in->matrix[i][j]->g + 
					in->matrix[i][j]->b) / 3;
		}
	}

	struct convolution_args *args;
	int block = (in->height * in->width) / threads;
	pthread_t *ts = (pthread_t *)malloc(sizeof(pthread_t) * threads);
	for (int i = 0; i < threads; i++) {
		args = (struct convolution_args *)malloc(sizeof(struct convolution_args));
		args->img = in;
		args->from = i * block;
		args->to = (i + 1) * block - 1;
		pthread_create(&ts[i], NULL, convolution, args);
	}

	for (int i = 0; i < threads; i++) {
		pthread_join(ts[i], NULL);
	}

	free(origin);

	clock_t end = clock();
	printf("Time taken: %.1f ms\n", 1000.0f * ((float)(end - begin) / CLOCKS_PER_SEC));
}

void * convolution(void *args)
{
	struct convolution_args *in = args;

	int row, column, gx, gy, res;
	for (int i = in->from; i <= in->to; i++) {
		row = (i / in->img->width);
		column = (i % in->img->width);

		gx = 0;
		gy = 0;

		for (int a = 0; a < KERNEL_SIZE; a++) {
			for (int b = 0; b < KERNEL_SIZE; b++) {
				int x = column - b + 1;
				int y = row - a + 1;
				
				x = x >= 0 ? x : 0;
				x = x < in->img->width ? x : in->img->width - 1;

				y = y >= 0 ? y : 0;
				y = y < in->img->height ? y : in->img->height - 1;
					
				gx += gx_kernel[a][b] * origin[y][x];
			}
		}

		for (int a = 0; a < KERNEL_SIZE; a++) {
			for (int b = 0; b < KERNEL_SIZE; b++) {
				int x = column - b + 1;
				int y = row - a + 1;
				
				x = x >= 0 ? x : 0;
				x = x < in->img->width ? x : in->img->width - 1;

				y = y >= 0 ? y : 0;
				y = y < in->img->height ? y : in->img->height - 1;
					
				gy += gy_kernel[a][b] * origin[y][x];
			}
		}

		res = sqrt(gx * gx + gy * gy);
		res = res < in->img->max_val ? res : in->img->max_val;
		
		in->img->matrix[row][column]->r = res;
		in->img->matrix[row][column]->g = res;
		in->img->matrix[row][column]->b = res;
	}
}