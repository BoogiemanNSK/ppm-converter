# PPM Image Sobel Operator

This program performs Sobel transformation on a given input .ppm image and saves result to the specified path.

### Compilation

Run _make_ to compile code into an executable (_ppm-converter_).

### Usage

When compiled, run _./ppm-converter -i [Input file] -o [Output file] (-t [Num of threads])_

### Important
* Please, avoid using _#commments_ in .ppm files and be sure to use ASCII encoded files only.
* Specifying number of threads is optional, though you will be warned (there is 1 thread by default).
