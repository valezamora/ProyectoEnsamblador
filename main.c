#include <stdio.h>
#include <stdlib.h>
#include "transformaciones.h"

int main ( int argc, char *argv[] ) {
	int cantidadTransf = 1;
	int trans[3] = {2, 2, 0};
	int cantidadX = 32;
	float  imagenVectorial[32] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};

	printf("Imagen inicial: \n");
	for(int i =0; i<cantidadX; ++i){
		printf("%f, ", imagenVectorial[i]);
	}
	
	printf("\n\n");
	
	
	transformarImagen(cantidadTransf, &trans, 32, &imagenVectorial);
	
	printf("Resultado: \n");
	for(int i =0; i<cantidadX; ++i){
		printf("%f, ", imagenVectorial[i]);
	}
	
}


