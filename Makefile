# Compilator used
CC=gcc

# Compilator flags
CFLAGS=-pthread -lm

# Source files
SOURCES=main.c src/sobel.c

# Executable name
EXECUTABLE=ppm-converter

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)