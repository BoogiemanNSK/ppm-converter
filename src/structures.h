struct pixel {
	int r, g, b;
};

struct image {
	char *path;
	char *format;
	int width, height, max_val;
	struct pixel ***matrix;
};