#include <stdio.h>
#include <stdlib.h>
#include "transformaciones.h"

/* Imprime*/
void imprimir(float *vector, int nbytes) {
	for(int i=0; i<nbytes; ++i){
		printf("%x ", vector[i]);
	}
	printf("\n");
}

int main ( int argc, char *argv[] ) {
	int cantidadTransf = 1;
	float trans[3] = {0, 0, 0};
	int cantidadX = 16;
	int cantidadY = 16;
	float  imagenVectorial[32] = {1,2,3,4,5,6,7,8,9,10,11,2,3,4,5,6,7,8,9,10,21,2,3,4,5,6,7,8,9,30,31,32};
	
	transfomarImagen(cantidadTransf, &trans, cantidadX, cantidadY, &imagenVectorial);
	imprimir(&imagenVectorial, 32);
}


