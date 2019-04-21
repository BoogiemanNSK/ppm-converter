/*
 * Structure that hold values of every color channel of pixel.
 */
struct pixel {
	int r, g, b;
};

/*
 * All the required data to build a ppm image.
 */
struct image {
	char *path;
	char *format;
	int width, height, max_val;
	struct pixel ***matrix;
};

/*
 * Structure that holds arguments to pass into threads-handled function.
 */
struct convolution_args {
	struct image *img;
	int from;
	int to;
};