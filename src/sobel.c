#include "sobel.h"

// Kernel matrices
const int gx_kernel[KERNEL_SIZE][KERNEL_SIZE] =
		{{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
const int gy_kernel[KERNEL_SIZE][KERNEL_SIZE] =
		{{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

/*
 * Sobel transformation function.
 * The result of a transformaion will be stored back in the passed image structure.
 * Time that is required to perform a transformation will be printed to the console.
 * Execution is separated between specified number of threads, each of them will 
 * count their part of image (equally distributed).
 */
void sobel(struct image *in, int threads)
{
	struct timeval t0, t1;
	gettimeofday(&t0, 0);

	// Transforming original image to grayscale (mid value of colors)
	origin = (int**)malloc(sizeof(int*) * in->height);
	for (int i = 0; i < in->height; i++) {
		origin[i] = (int*)malloc(sizeof(int) * in->width);
		for (int j = 0; j < in->width; j++) {
			origin[i][j] = (in->matrix[i][j]->r +
					in->matrix[i][j]->g + 
					in->matrix[i][j]->b) / 3;
		}
	}

	// Threads separated execution
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

	// Waiting when all threads are finished their work.
	for (int i = 0; i < threads; i++) {
		pthread_join(ts[i], NULL);
	}

	free(origin);

	// Printing real time of execution
	gettimeofday(&t1, 0);
	long dsec = t1.tv_sec - t0.tv_sec;
	long dusec = t1.tv_usec - t0.tv_usec;
	if (dusec < 0) { dsec--; dusec += 1000000; }

	long elapsed = dsec * 1000 + dusec / 1000;
	printf("Time taken: %ld ms\n", elapsed);
}

/*
 * Threads-handled part of Sobel transormation.
 * Passed argument has to be a filled structure convolution_args.
 * Result will be saved back to the passed structure.
 */
void * convolution(void *args)
{
	struct convolution_args *in = args;

	int row, column, gx, gy, res;
	for (int i = in->from; i <= in->to; i++) {
		row = (i / in->img->width);
		column = (i % in->img->width);

		gx = 0;
		gy = 0;

		// Transformation of one pixel with horizontal kernel
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

		// Transformation of one pixel with vertical kernel
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

		// Sum of transformation
		res = sqrt(gx * gx + gy * gy);
		res = res < in->img->max_val ? res : in->img->max_val;
		
		// Writing back result
		in->img->matrix[row][column]->r = res;
		in->img->matrix[row][column]->g = res;
		in->img->matrix[row][column]->b = res;
	}
}