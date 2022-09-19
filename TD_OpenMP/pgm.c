#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"

/* Allocates a matrix of int */
char * malloc_image(int w, int h) {
  char * img;
  int x;

  img = (char*) malloc(w*h*sizeof(char));
  return img;
}

/* Creates a new image */
image * create_image(int w, int h, int colors) {
  image * im = (image*) malloc(sizeof(image));
  im->w = w; im->h = h; im->colors = colors;
  im->img = malloc_image(w,h);
  return im;
}

/* Returns an image from a PGM file */
image * read_pgm(char * file) {
  char a, b;
  int x, y, k;
  int w, h, colors;
  FILE * f;
  
  if (!(f = fopen(file, "r"))) fprintf( stderr,"Cannot read file\n");

  /* Check PGM header */
  fscanf(f, "%c%c\n",&a, &b);
  if (a != 'P' && b != '2') 
    fprintf( stderr,"Not a PGM file.\n");

  /* Read height and width */
  fscanf(f, "%d%d\n", &w, &h);

  /* Read the max value */
  fscanf(f, "%d\n", &colors);
  
  /* Create the image */
  image * im = create_image(w,h,colors);
  
  /* Load the greyscale image into img*/
  for (y = 0; y < h; y++)
    for (x = 0; x < w; x++){
      fscanf(f, "%d", &k);
      im->img[y+x*h] = k;
    }
  fclose(f);
  return im;
}

void write_pgm(char * file, image * img) {
  int x,y;
  FILE * f;

  if (!(f = fopen(file, "w"))) fprintf( stderr,"Cannot write file\n");
  
  /* Write PGM header */
  fprintf(f, "P2\n");
  fprintf(f, "# %s\n", file);
  
  /* Write dimensions */
  fprintf(f, "%d %d\n", img->w, img->h);

  /* Write colors max value */
  fprintf(f, "%d\n", img->colors);

  /* Write image */
  for (y = 0; y < img->h; y++)
    for (x = 0; x < img->w; x++){
      fprintf(f, "%d\n", img->img[y+x*img->h]);
    }
  fclose(f);
}
