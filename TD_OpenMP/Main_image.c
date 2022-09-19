#include <stdio.h>
# include <stdlib.h>
#include <omp.h>
#include "pgm.h"
#include <string.h>
# include <math.h>
//gcc Main_image.c pgm.c -o image -lm <-- (pour la lib math)
int main(int argc, char* argv[])
{ char* file = "train.pgm";
  char* fileout = "train4.pgm";
  char* Gxfile = "Gx.pgm";
  char* Gyfile = "Gy.pgm";
  char* Sfile = "S.pgm";
    char* Sfile2 = "S2.pgm";
  double* Gx;
  double* Gy;
  int i,x,y;
 printf("%s\n", file);
image* im=read_pgm(file);

image * imout = create_image(im->w, im->h,255);
imout->img = im->img;

// // mettre à 0 la moitié de l'image
// for (i=0; i<(im->w * im->h)/2;i++)
//   *(imout->img + i) = 0;

// //normalisation avec la valeur donnée en paramètre
// for (i<(im->w * im->h)/2; i< 3*(im->w * im->h)/4;i++)
//   *(imout->img + i) +=  *(argv[0]);

//écrire l'image dans un fichier
//write_pgm(fileout,imout);

int Y = im->h;
int X = im->w;
//filtre de Sobel
Gx = (double *) malloc(X*Y*sizeof(double));
Gy = (double*) malloc(X*Y*sizeof(double));
/*
image * Gx = create_image(im->w, im->h,255);
image * Gy = create_image(im->w, im->h,255);*/
image * S = create_image(im->w, im->h,255);
for (i=0; i<(X*Y);i++)
  *(Gx+ i) = 0;
  *(Gy + i) = 0;
  *(S->img + i) = 0;
for (x=1; x< X-1;x++){
  for (y=1; y< Y-1 ;y++){
    *(Gx + x*Y+y)     = 1*(*(im->img + (x-1)*Y+y-1))+ 0*(*(im->img + (x)*Y+y-1))  - 1*(*(im->img + (x+1)*Y+y-1)) 
			+ 2*(*(im->img + (x-1)*Y+y)) + 0*(*(im->img + (x)*Y+y))  - 2*(*(im->img + (x+1)*Y+y)) 
			+ 1*(*(im->img + (x-1)*Y+y+1))+ 0*(*(im->img + (x)*Y+y+1))- 1*(*(im->img + (x+1)*Y+y+1));
    //*(Gx->img + x*Y+y) = *(im->img + x*Y+y) ;
    *(Gy + x*Y+y)     = 1*(*(im->img + (x-1)*Y+y-1))+ 2*(*(im->img + (x)*Y+y-1))  + 1*(*(im->img + (x+1)*Y+y-1)) 
			+ 0*(*(im->img + (x-1)*Y+y)) + 0*(*(im->img + (x)*Y+y))  +  0*(*(im->img + (x+1)*Y+y)) 
			-1*(*(im->img + (x-1)*Y+y+1))- 2*(*(im->img + (x)*Y+y+1))- 1*(*(im->img + (x+1)*Y+y+1));
    //*(Gy->img + x*Y+y) = *(im->img + x*Y+y) ;					
  /*  *(Gx->img + x*Y+y) = 1*(*(im->img + (x-1)*Y+y-1))+ 0*(*(im->img + (x-1)*Y+y))  - 1*(*(im->img + (x-1)*Y+y+1)) 
			+ 2*(*(im->img + (x)*Y+y-1)) + 0*(*(im->img + (x)*Y+y))  - 2*(*(im->img + (x)*Y+y+1)) 
			+1*(*(im->img + (x+1)*Y+y-1))+ 0*(*(im->img + (x+1)*Y+y))- 1*(*(im->img + (x+1)*Y+y+1));
    
    *(Gy->img + x*Y+y) = 1*(*(im->img + (x-1)*Y+y-1))+ 2*(*(im->img + (x)*Y+y-1))  + 1*(*(im->img + (x-1)*Y+y+1)) 
			+ 0*(*(im->img + (x)*Y+y-1)) + 0*(*(im->img + (x)*Y+y))  +  0*(*(im->img + (x)*Y+y+1)) 
			-1*(*(im->img + (x+1)*Y+y+-1))- 2*(*(im->img + (x+1)*Y+y))- 1*(*(im->img + (x+1)*Y+y+1));
				*/			
			
			
   // *(Gy->img + x*Y+y) = *(im->img + (x-1)*Y+y-1) +2*(*(im->img + (x)*Y+y+1)) + *(im->img + (x+1)*Y+y-1) - *(im->img + (x-1)*Y+y+1) - 2*(*(im->img + x*Y+y+1)) - *(im->img + (x+1)*Y+y+1);
    *(S->img + x*Y+y) = sqrt(pow(*(Gx + x*Y+y),2) + pow(*(Gy + x*Y+y),2)  );
    
    
    
  }
}

// write_pgm(Gxfile,Gx);
// write_pgm(Gyfile,Gy);
write_pgm(Sfile,S);




// Sobel parallèle
for (i=0; i<(X*Y);i++)
  *(Gx+ i) = 0;
  *(Gy + i) = 0;
  *(S->img + i) = 0;
int rang;
// int p;
#pragma omp parallel private(rang,y) 
	{
	#pragma omp for schedule(runtime) nowait //chaque x est envoyé sur un processeur
	for (x=1; x< X-1;x++){
// 	  #pragma omp parallel for private(y) shared(S) schedule(dynamic) num_threads(2)
	  for (y=1; y< Y-1 ;y++){
	    *(Gx + x*Y+y)     = 1*(*(im->img + (x-1)*Y+y-1))+ 0*(*(im->img + (x)*Y+y-1))  - 1*(*(im->img + (x+1)*Y+y-1)) 
				+ 2*(*(im->img + (x-1)*Y+y)) + 0*(*(im->img + (x)*Y+y))  - 2*(*(im->img + (x+1)*Y+y)) 
				+ 1*(*(im->img + (x-1)*Y+y+1))+ 0*(*(im->img + (x)*Y+y+1))- 1*(*(im->img + (x+1)*Y+y+1));
	    *(Gy + x*Y+y)     = 1*(*(im->img + (x-1)*Y+y-1))+ 2*(*(im->img + (x)*Y+y-1))  + 1*(*(im->img + (x+1)*Y+y-1)) 
				+ 0*(*(im->img + (x-1)*Y+y)) + 0*(*(im->img + (x)*Y+y))  +  0*(*(im->img + (x+1)*Y+y)) 
				-1*(*(im->img + (x-1)*Y+y+1))- 2*(*(im->img + (x)*Y+y+1))- 1*(*(im->img + (x+1)*Y+y+1));
	   *(S->img + x*Y+y) = sqrt(pow(*(Gx + x*Y+y),2) + pow(*(Gy + x*Y+y),2)  );
	    rang=omp_get_thread_num();
	    printf("Rang : %d ; pixel : (%d,%d)\n",rang,x,y);
// 	    p=omp_in_parallel();
// 	  printf("p vaut : %d\n",p);
	  }
	}

	}

write_pgm(Sfile2,S);
return 0;
}