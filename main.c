#include <math.h>
#include <pthread.h>
#include <stdio.h>

struct image {
  char *path;
  int **matrix;
};

int read_args(int argc, char **argv, char *input_file, char *output_file, int *threads_num) {
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-i") == 0) {
      input_file = argv[i + 1];
    }
    if (strcmp(argv[i], "-o") == 0) {
      output_file = argv[i + 1];
    }
    if (strcmp(argv[i], "-t") == 0) {
      *threads_num = atoi(argv[i + 1]);
    }
  }

  if (input_file == NULL) {
    printf("[ERROR] Input file is not specified!\n");
    return -1;
  }

  if (output_file == NULL) {
    printf("[ERROR] Output file is not specified!\n");
    return -1;
  }

  if (*threads_num == -1) {
    printf("[WARNING] Num of threads was not specified. Setting to 1 as default.\n");
    *threads_num = 1;
  }

  return 0;
}

int read_image(struct image *in) {

  return 0;
}

int sobel(struct image *in, struct image *out) {

  return 0;
}

int write_image(struct image *out) {

  return 0;
}

int main(int argc, char **argv) {
  struct image *in = (struct image*)malloc(sizeof(struct image));
  struct image *out = (struct image*)malloc(sizeof(struct image));
  
  char *input_file = NULL;
  char *output_file = NULL;
  int threads_num = -1;
  int err = 0;

  err = read_args(argc, argv, input_file, output_file, &threads_num);
  if (err != 0) { return err; }

  in->path = input_file;
  out->path = output_file;

  err = read_image(in);
  if (err != 0) { return err; }

  err = sobel(in, out);
  if (err != 0) { return err; }

  err = write_image(out);
  if (err != 0) { return err; }

  return 0;
}