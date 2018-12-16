#include <stdio.h>
#include <stdlib.h>
#include "transformaciones.h"

int main ( int argc, char *argv[] ) {
	int cantidadTransf = 1;
	int trans[3] = {0, 0, 0};
	int cantidadX = 32;
	float  imagenVectorial[32] = {1,2,3,4,5,6,7,8,9,10,11,2,3,4,5,6,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
	
	transformarImagen(cantidadTransf, &trans, 32, &imagenVectorial);
	
}


