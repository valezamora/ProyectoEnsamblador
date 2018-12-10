#include <stdio.h>
#include <stdlib.h>
#include "transformaciones.h"

int main ( int argc, char *argv[] ) {
	unsigned float * trans = {1, 0, 0, 0};
	unsigned float * imagenVectorial = {5,5,2.4,5,2,6,2.1,5.3,6,7,2,9};
	
	transfomarImagen(&trans, &imagenVectorial);
	
	imprimir(trans, 4);
	imprimir(imagenVectorial, 12);
}

/* Imprime*/
void imprimir(void *vector, int nbytes) {
	for(int i=0; i<nbytes; ++i){
		printf("%x ", vector[i]);
	}
	printf("\n");
}