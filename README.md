# PPM Image Sobel Operator

This program performs Sobel transformation on a given input .ppm image and saves result to the specified path.

### Compilation

Run ``make`` to compile code into an executable.

### Usage

When compiled, run:
``
./ppm-converter -i [Input file] -o [Output file] (-t [Num of threads])
``

### Important
* Please, avoid using _#commments_ in .ppm files and be sure to use ASCII encoded files only.
* Specifying number of threads is optional, though you will be warned (there is 1 thread by default).
