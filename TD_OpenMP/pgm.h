/** 
 * Provides functions for reading 
 * a pgm image from a file into an array 
 * and writing it back. 
 */

#ifndef __PGM_H
#define __PGM_H 
typedef struct 
{
  unsigned char *img;
  int w,h;
  int colors;
} image;

char * malloc_image(int w, int h);
image * read_pgm(char * file);
void write_pgm(char * file, image * img);
image * create_image(int w, int h, int colors);
#endif
