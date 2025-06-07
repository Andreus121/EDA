#include <stdio.h>
#include <stdlib.h>
#include "TDAmgrafo.h"

int main(int argc, char *argv[]){
	TDAgrafo* grafo=leerGrafoNoDirigidoPonderado(argv[1]);
	
	if(grafo==NULL){
		return 0;
	}
	
	mostrarMatrizAdyacencia(grafo);

	return 1;
}
