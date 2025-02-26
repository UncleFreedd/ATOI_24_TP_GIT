#include <stdio.h>
#include <complex.h>
#include <math.h>
#include "ppm.h"

#define TRSH 2.0
#define ITER 1024ull

#define SIZEX 1500
#define SIZEY 1500

// Fonction pour calculer la partie réelle de 'c'
double cx(int x) {
    static const double qx = 3.0 / (double)SIZEX;
    return -2.0 + x * qx;
}

// Fonction pour calculer la partie imaginaire de 'c'
double cy(int y) {
    static const double qy = 2.0 / (double)SIZEY;
    return -1.0 + y * qy;
}

int main(int argc, char *argv[]) {
    struct ppm_image im;
    ppm_image_init(&im, SIZEX, SIZEY); // Correction de l'utilisation de &

    for (int i = 0; i < SIZEX; ++i) {
        for (int j = 0; j < SIZEY; ++j) {
            unsigned long int iter = 0;
            double complex c = cx(i) + cy(j) * I;
            double complex z = 0;

            while(iter < ITER) {
                if(cabs(z) > TRSH) {
                    break;
                }
                z = z*z + c;
                iter++;
            }

            int grey = 255.0 * log(iter) / log(ITER); // Amélioration du calcul de gris
            ppm_image_setpixel(&im, i, j, grey, grey, grey);
        }
    }

    ppm_image_dump(&im, "m.ppm");
    ppm_image_release(&im);

    return 0;
}
