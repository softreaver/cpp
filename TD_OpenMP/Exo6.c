//gcc -o ./Exo6 ./Exo6.c ./pgm.c -lm -fopenmp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pgm.h"

#define NORM_COLOR  255     // La norme désirée pour la nouvelle image.

void initGivenMatrix(int *mat, const int w, const int h);
image* sobel(const image* im);
int getPixelNormalized(double pixelValue, int maxColorValue, int normalizedColor);

int static W, H;

/**
 * Charge une image pgm appelée "image.pgm" depuis le répertoire de travail.
 * Puis applique un filtre de sobel dessus, avant d'écrire une nouvelle image
 * dans le répertoire de travail appellée "image_out.pgm"
 */
int main(int argc, char* argv[]) {
    char* filePathIn = "image.pgm";
    char* filePathOut = "image_out.pgm";

    image* im = read_pgm(filePathIn);
    
    W = im->w;
    H = im->h;

    /**
     * Pour aller plus loin : 
     * 
     * Pour traiter une superposition d'images, il faudrait parallèliser l'appel de la fonction sobel() 
     * dans une boucle for().
     * 
     * Je ne suis pas sûr du résultat attendu mais à supposer qu'il faille calculer le gradient en Z (3eme dimension), cela implique
     * d'imposer un SCHEDULE(static, 3) à la directive "omp for" afin d'assurer le travail sur 3 images superposées en même temps.
     * Il faudrait également mettre à jour la fonction sobel actuelle, pour qu'elle calcule le gradient Gz en prenant les pixels aux mêmes coordonées sur les 3 images.
     * A la fin des traitements des fonctions sobel(), il faudrait refaire le même travail par paquet de 3 images sur les nouvelles ainsi créées. Et ceux jusqu'à ce que
     * le nombre d'image à traiter soit strictement inférieur à 3.
     */
    image* transformedImage = sobel(im);

    write_pgm(filePathOut, transformedImage);

    return 0;
}

/** Init all given matrix elements to 0 */
void initGivenMatrix(int *mat, const int w, const int h) {
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            *(mat + x*h+y) = 0;
        }
    }
}

/** 
 * Apply sobel filter on given image.
 * The given image won't be modified, a new image structure will be created and returned
 */
image* sobel(const image* imOrig) {
    unsigned char* imMat = imOrig->img;
    int oldMaxColor = imOrig->colors;

    // Init new image structure
    image* newIm = create_image(imOrig->w, imOrig->h, NORM_COLOR);

    // Init matrix for gradients calculation
    int Gx[W][H];
    int Gy[W][H];
    initGivenMatrix((int *)Gx, W, H);
    initGivenMatrix((int *)Gy, W, H);

/**
 *  La bonne pratique est de ne pas paralleliser les données contigus en mémoire centrale.
 *  De ce fait, j'ai parallélisé uniquement la première dimension de la matrice. La deuxième parallélisation est commentée.
 *  La clause nowait permet de réduire le coût du merge à la sortie de la région parallèle en supprimant
 *  la barrière de synchronisation implicite.
 *  Nous ne faisons pas de post traitement particulier après la boucle donc on peut se le permettre.
 * 
 *  J'aurais pu faire d'abord la normalisation en parallèle puis, parralèliser sobel. Mais moins il y a de régions parralèles, plus efficace sera le code.
 *  Ceci étant dû au coup de fork et merge, avant et après chaque constructions parallèles.
 */

    // Transformation
    int x;
    #pragma omp parallel 
    #pragma omp for schedule(runtime) nowait
    for (x = 0; x < W; x++) {
        // #pragma omp parallel
        // #pragma omp for schedule(runtime) firstprivate(x) nowait
        for (int y = 0; y < H; y++) {
            // Gradients calculations
            Gx[x][y] = getPixelNormalized(*(imMat + (x-1)*H+y-1), oldMaxColor, NORM_COLOR) - getPixelNormalized(*(imMat + (x+1)*H+y-1), oldMaxColor, NORM_COLOR)
                + 2*getPixelNormalized(*(imMat + (x-1)*H+y), oldMaxColor, NORM_COLOR) - 2*getPixelNormalized(*(imMat + (x+1)*H+y), oldMaxColor, NORM_COLOR)
                + getPixelNormalized(*(imMat + (x-1)*H+y+1), oldMaxColor, NORM_COLOR) - getPixelNormalized(*(imMat + (x+1)*H+y+1), oldMaxColor, NORM_COLOR);

            Gy[x][y] = getPixelNormalized(*(imMat + (x-1)*H+y-1), oldMaxColor, NORM_COLOR) + 2*getPixelNormalized(*(imMat + x*H+(y-1)), oldMaxColor, NORM_COLOR) + getPixelNormalized(*(imMat + (x+1)*H+y-1), oldMaxColor, NORM_COLOR)
                - getPixelNormalized(*(imMat + (x-1)*H+y+1), oldMaxColor, NORM_COLOR) - 2*getPixelNormalized(*(imMat + x*H+y+1), oldMaxColor, NORM_COLOR) - getPixelNormalized(*(imMat + (x+1)*H+y+1), oldMaxColor, NORM_COLOR);

            // New pixel calculation
            *(newIm->img + x*H+y) = sqrt(pow(Gx[x][y],2) + pow(Gy[x][y],2));
        }
    }
    return newIm;
}

/**
 * Returned the normalied value of pixelValue.
 * maxColorValue if the maximum value of pixelValue
 * normalizedColor is the new maximum color desired.
 */
int getPixelNormalized(double pixelValue, int maxColorValue, int normalizedColor) {
    return (int) ( normalizedColor * (pixelValue/maxColorValue) );
}
