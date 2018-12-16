#include <stdio.h> 
#include "transformaciones.h"

int main(){
	int numeroTransformaciones = 1;
	int transformacion[3] ={2,2,0};
	int numeroCaracteres = 32;
	float caracteres [32] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
	transformarImagen(numeroTransformaciones,&transformacion,numeroCaracteres,&caracteres);
	for(int i =0;i<32;i++){
		printf("%f ",caracteres[i]);
	}
}