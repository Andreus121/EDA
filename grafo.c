#include <stdio.h>
#include <stdlib.h>
#include "TDAmgrafo.h"

int main(int argc, char *argv[]){
	TDAgrafo* grafo=leerGrafoNoDirigidoPonderado(argv[1]);
	
	if(grafo==NULL){
		return 0;
	}
	printf("cantidad de vertices: %d\n",grafo->cantv);
	mostrarMatrizAdyacencia(grafo);

	int visitados[8];
	int distancias[8];
	int precedencia[8];

	dijkstra(grafo,0,visitados,distancias,precedencia);
	printf("Arreglo visitados  :");
	for(int i=0;i<grafo->cantv;i++){
		printf("  %d",visitados[i]);
	}
	printf("\n");
	printf("Arreglo distancias  :");
	for(int i=0;i<grafo->cantv;i++){
		printf("  %d",distancias[i]);
	}
	printf("\n");
	printf("Arreglo precedencia  :");
	for(int i=0;i<grafo->cantv;i++){
		printf("  %d",precedencia[i]);
	}
	printf("\n");
	return 1;
}
