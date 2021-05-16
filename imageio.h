
#ifndef IMAGE_IO_H
#define IMAGE_IO_H

#include <stdlib.h>
#include <tiffio.h>
#include <png.h>

//added by Fore
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif
//
// COMPILATION
//
// Should be compiled with -ltiff and -lpng

// Sets tbe width and height to the appropriate values and mallocs
// a char *buffer loading up the values in row-major, RGBA format.
// The memory associated with the buffer can be deallocated with free().
// If there was an error reading file, then 0 is returned, and
// width = height = -1. 
unsigned char *loadImageRGBA( char *fileName, int *width, int *height);

// Saves image given by buffer with specicified with and height
// to the given file name, returns true on success, false otherwise.
// The image format is RGBA.
bool saveImageRGBA(char *fileName, unsigned char *buffer, int width, int height);

// returns index into image buffer for given coordinate
#define indxRGBA(X,Y,W) (((Y) * (W) + (X)) * 4)

//added by Tong
void save_image( char *n1, int x0, int y0, int width, int height );
void load_image( char *fname, int x0, int y0  );
#endif
