#include <stdio.h>
#include <stdlib.h>
#include "TDAmgrafo.h"

int main(int argc, char *argv[]){
	TDAgrafo* grafo=leerGrafoNoDirigido(argv[1]);
	
	if(grafo==NULL){
		return 0;
	}
	mostrarMatrizAdyacencia(grafo);

	int visitados[grafo->cantv];
	int distancias[grafo->cantv];
	int precedencia[grafo->cantv];
	printf("---BSF---\n");
	BSF(grafo, 2,visitados,distancias,precedencia);
	printf("Arreglo de visitados:");
	for(int i=0; i<grafo->cantv; i++){
		printf(" %d", visitados[i]);
	}
	printf("\n");
	printf("Arreglo de distancias:");
	for(int i=0; i<grafo->cantv; i++){
		printf(" %d", distancias[i]);
	}
	printf("\n");
	printf("Arreglo de precedencia:");
	for(int i=0; i<grafo->cantv; i++){
		printf(" %d", precedencia[i]);
	}
	printf("\n");

	printf("---DSF---\n");
	DSF(grafo, 2,visitados,distancias,precedencia);
	printf("Arreglo de visitados:");
	for(int i=0; i<grafo->cantv; i++){
		printf(" %d", visitados[i]);
	}
	printf("\n");
	printf("Arreglo de distancias:");
	for(int i=0; i<grafo->cantv; i++){
		printf(" %d", distancias[i]);
	}
	printf("\n");
	printf("Arreglo de precedencia:");
	for(int i=0; i<grafo->cantv; i++){
		printf(" %d", precedencia[i]);
	}
	printf("\n");

	return 1;
}
