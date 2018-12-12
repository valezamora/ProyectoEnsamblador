#include <stdio.h>
#include <stdlib.h>
#include "transformaciones.h"

/* Imprime*/
/*
void imprimir(float *vector, int nbytes) {
	for(int i=0; i<nbytes; ++i){
		printf("%.1f , ", vector[i]);
	}
	printf("\n");
}
*/
int main ( int argc, char *argv[] ) {
	int cantidadTransf = 1;
	float trans[3] = {0, 0, 0};
	int cantidadX = 16;
	int cantidadY = 16;
	float  imagenVectorial[32] = {1,2,3,4,5,6,7,8,9,10,11,2,3,4,5,6,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
	
	transformarImagen(cantidadTransf, &trans, 16, cantidadY, &imagenVectorial);
	
	//printf ("Termino transformacion");
	//imprimir(&imagenVectorial, 32);
}


