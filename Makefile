# Compilator used
CC=gcc

# Compilator flags
CFLAGS=-pthread

# Source files
SOURCES=main.c

# Executable name
EXECUTABLE=ppm-converter

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)