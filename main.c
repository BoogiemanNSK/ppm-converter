#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/sobel.h"

#define FORMAT_STRING_SIZE 4

/*
 * Function to read arguments into variables.
 * Input and Output files are necessary and threads number is optional.
 * Returns -1 in case of missed parameters.
 */
int read_args(int argc, char **argv, char **input_file, char **output_file, int *threads_num)
{
	for (int i = 1; i < argc; i++) {
    		if (strcmp(argv[i], "-i") == 0)
      			*input_file = argv[i + 1];

    		if (strcmp(argv[i], "-o") == 0)
      			*output_file = argv[i + 1];
    		
		if (strcmp(argv[i], "-t") == 0)
      			*threads_num = atoi(argv[i + 1]);
	}

	if (*input_file == NULL) {
    		printf("[ERROR] Input file is not specified!\n");
    		return -1;
  	}

  	if (*output_file == NULL) {
    		printf("[ERROR] Output file is not specified!\n");
    		return -1;
  	}

  	if (*threads_num == -1) {
    		printf("[WARNING] Num of threads was not specified. Setting to 1 as default.\n");
    		*threads_num = 1;
  	}
  	
	return 0;
}

/*
 * Parses data from specified file path to the image structure.
 */
void read_image(struct image *in)
{
	FILE *f;

	if ((f = fopen(in->path, "r")) == NULL) {
		printf("[ERROR] Could not open input file for reading!\n");
	}

	in->format = malloc(FORMAT_STRING_SIZE);
	fscanf(f, "%s %d %d %d", in->format, &(in->width), &(in->height), &(in->max_val));

 	in->matrix = (struct pixel ***)malloc(sizeof(struct pixel **) * in->height);
 	for (int i = 0; i < in->height; i++) {
 		in->matrix[i] = (struct pixel **)malloc(sizeof(struct pixel *) * in->width);
   		for (int j = 0; j < in->width; j++) {
   			in->matrix[i][j] = (struct pixel *)malloc(sizeof(struct pixel));
   			fscanf(f, "%d %d %d", &(in->matrix[i][j]->r), 
			      &(in->matrix[i][j]->g), &(in->matrix[i][j]->b));
   		}
 	}

 	fclose(f);
}

/*
 * Writes data from resulting structure to the specified file.
 */
void write_image(struct image *out)
{
	FILE *f;

  	if ((f = fopen(out->path, "w")) == NULL) {
  		printf("[ERROR] Could not open output file for writing!\n");
  	}

  	fprintf(f, "%s\n%d %d\n%d\n", out->format, out->width, out->height, out->max_val);
  
  	for (int i = 0; i < out->height; i++) {
    		for (int j = 0; j < out->width; j++) {
      			fprintf(f, "%d %d %d  ", out->matrix[i][j]->r,
			      out->matrix[i][j]->g, out->matrix[i][j]->b);
    		}
    		fprintf(f, "\n");
  	}

  	fclose(f);
}

/*
 * MAIN
 */
int main(int argc, char **argv)
{
  	struct image *img = (struct image*)malloc(sizeof(struct image));
  
  	char *input_file = NULL;
  	char *output_file = NULL;
  	int threads_num = -1;
  	int err = 0;

  	err = read_args(argc, argv, &input_file, &output_file, &threads_num);
  	if (err != 0) { return err; }

  	img->path = input_file;
  	read_image(img);

  	sobel(img, threads_num);
  	
	img->path = output_file;  
	write_image(img);

  	return 0;
}