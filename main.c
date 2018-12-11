#include <stdio.h>
#include <stdlib.h>
#include "transformaciones.h"

int main ( int argc, char *argv[] ) {
	int cantidadTransf = 1;
	unsigned float * trans = {0, 0, 0};
	int cantidadX = 50;
	int cantidadY = 50;
	unsigned float * imagenVectorial = {1,2,3,4,5,6,7,8,9,10,21,2,3,4,5,6,7,8,9,10,31,2,3,4,5,6,7,8,9,10,41,2,3,4,5,6,7,8,9,10,51,2,3,4,5,6,7,8,9,10,61,2,3,4,5,6,7,8,9,10,71,2,3,4,5,6,7,8,9,10,81,2,3,4,5,6,7,8,9,10,91,2,3,4,5,6,7,8,9,10,101,2,3,4,5,6,7,8,9,10};
	
	transfomarImagen(cantidadTransf, &trans, cantidadX, cantidadY, &imagenVectorial);
	imprimir(imagenVectorial, 100);
}

/* Imprime*/
void imprimir(void *vector, int nbytes) {
	for(int i=0; i<nbytes; ++i){
		printf("%x ", vector[i]);
	}
	printf("\n");
}