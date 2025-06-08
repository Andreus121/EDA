#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "TDAlista.h"
#include "TDAcola.h"
#include "TDApila.h"

/*------------- ESTRUCTURA DE DATOS -------------*/
typedef struct matrizGrafo{
	int cantv;
	int* V;
	int** MA;
}TDAgrafo;

/*----------------- SCOPE FUNCIONES -----------------*/
//Funciones basicas
TDAgrafo* crearGrafoVacio(int vertices);
void mostrarMatrizAdyacencia(TDAgrafo* grafo);
int adyacenciaNodos(TDAgrafo * grafo, int vertA, int vertB);
TDAlista* obtenerAdyacentes(TDAgrafo* grafo, int vertice);

//Lectura de grafos
TDAgrafo* leerGrafoNoDirigidoNoPonderado(char *nombreArchivo);
TDAgrafo* leerGrafoNoDirigidoPonderado(char *nombreArchivo);
TDAgrafo* leerGrafoDirigidoNoPonderado(char *nombreArchivo);
TDAgrafo* leerGrafoDirigidoPonderado(char *nombreArchivo);

//Funciones extra
int esCamino(TDAgrafo* grafo,TDAlista* camino);
int esCompleto(TDAgrafo* grafo);
int esComplemento(TDAgrafo* grafo1, TDAgrafo* grafo2);
int gradoDeVertice(TDAgrafo* grafo, int vertice);
int gradoPromedio(TDAgrafo* grafo);
int esRegular(TDAgrafo* grafo);

//Funciones escenciales
void BSF(TDAgrafo* grafo, int inicio, int* visitados, int* distancias,int* precedencia);
void DSF(TDAgrafo* grafo, int inicio, int* visitados, int* distancias,int* precedencia);

/*----------------- FUNCIONES BASICAS -----------------*/

TDAgrafo* crearGrafoVacio(int vertices){
	TDAgrafo* grafo = (TDAgrafo*)malloc(sizeof(TDAgrafo));
	grafo->cantv = vertices;
	grafo->MA = (int**)malloc(vertices * sizeof(int*));
	int i,j;
	for (i = 0; i < vertices; i++){
		grafo->MA[i] = (int*)malloc(vertices * sizeof(int));
		//Inicializa en cero
		for(j=0;j<vertices;j++){
			grafo->MA[i][j] = 0;
		}
	}
	return grafo;
}

void mostrarMatrizAdyacencia(TDAgrafo* grafo){
	int i, j;
	for (i = 0; i < grafo->cantv; i++){
		for (j = 0; j < grafo->cantv; j++) 
		{
			printf("%d ", grafo->MA[i][j]);
		}
		printf("\n");
	}
}

int adyacenciaNodos(TDAgrafo * grafo, int vertA, int vertB){
	if (grafo->MA[vertA][vertB] == 1){
		return 1;
	}
	return 0;
}

TDAlista* obtenerAdyacentes(TDAgrafo* grafo, int vertice){
	TDAlista* L = crearLista();
	for(int i=0; i < grafo->cantv;i++){
		if(grafo->MA[vertice][i] == 1){
			insertarFin(L,i);
		}
	}
	return L;
}

/*--------------- LECTURA DE GRAFOS ---------------*/
//Leer grafo no dirigido ni ponderado
TDAgrafo* leerGrafoNoDirigidoNoPonderado(char *nombreArchivo){
	FILE*pf;		   //para abrir archivo
	pf = fopen(nombreArchivo,"r");
	int n_vertices, m_aristas;
	int i,j,k;
	if (pf ==NULL){
		printf("Error de archivo\n");
		return NULL;
	}
	else{
		//Cantidad de nodos y aristas
		fscanf(pf, "%d %d", &n_vertices,&m_aristas); 		
		TDAgrafo *G=crearGrafoVacio(n_vertices);	
		//dependiendo de las lineas de archivo, 
		// 1 para grafo no dirigido no ponderado
		for(k=0;k<m_aristas;k++){
			fscanf(pf,"%d %d",&i, &j);
			G->MA[i][j] = 1;
			G->MA[j][i] = 1;
		}
		fclose(pf);
		return  G;
	}
}

//Leer grafo no dirigido y ponderado
TDAgrafo* leerGrafoNoDirigidoPonderado(char *nombreArchivo){
	FILE*pf;		   //para abrir archivo
	pf = fopen(nombreArchivo,"r");
	int n_vertices, m_aristas;
	int i,j,k,h;
	if (pf ==NULL){
		printf("Error de archivo\n");
		return NULL;
	}
	else{
		//Cantidad de nodos y aristas
		fscanf(pf, "%d %d", &n_vertices,&m_aristas); 		
		TDAgrafo *G=crearGrafoVacio(n_vertices);	
		//dependiendo de las lineas de archivo, 
		// 1 para grafo no dirigido no ponderado
		for(k=0;k<m_aristas;k++){
			fscanf(pf,"%d %d %d",&i, &j,&h);
			G->MA[i][j] = h;
			G->MA[j][i] = h;
		}
		fclose(pf);
		return  G;
	}
}

//Leer grafo dirigido no ponderado
TDAgrafo* leerGrafoDirigidoNoPonderado(char *nombreArchivo){
	FILE*pf;		   
	pf = fopen(nombreArchivo,"r");
	int n_vertices, m_aristas;
	int i,j,k;
	if (pf ==NULL){
		printf("Error de archivo\n");
		return NULL;
	}
	else{
		//Cantidad de nodos y aristas
		fscanf(pf, "%d %d", &n_vertices,&m_aristas); 		
		TDAgrafo *G=crearGrafoVacio(n_vertices);	
		//dependiendo de las lineas de archivo, 
		// 1 para grafo no dirigido no ponderado
		for(k=0;k<m_aristas;k++){
			fscanf(pf,"%d %d",&i, &j);
			G->MA[i][j] = 1;
		}
		fclose(pf);
		return  G;
	}
}

//Leer grafo dirigido y ponderado
TDAgrafo* leerGrafoDirigidoPonderado(char *nombreArchivo){
	FILE*pf;		   
	pf = fopen(nombreArchivo,"r");
	int n_vertices, m_aristas;
	int i,j,k,h;
	if (pf ==NULL){
		printf("Error de archivo\n");
		return NULL;
	}
	else{
		//Cantidad de nodos y aristas
		fscanf(pf, "%d %d", &n_vertices,&m_aristas); 		
		TDAgrafo *G=crearGrafoVacio(n_vertices);	
		//dependiendo de las lineas de archivo, 
		// 1 para grafo no dirigido no ponderado
		for(k=0;k<m_aristas;k++){
			fscanf(pf,"%d %d %d",&i, &j,&h);
			G->MA[i][j] = h;
		}
		fclose(pf);
		return  G;
	}
}

/*----------------- FUNCIONES EXTRA -----------------*/
/*camino es que siguiendo el orden de las aristas se tengan
todas las aristaas para llegar de inicio a fin*/
int esCamino(TDAgrafo* grafo,TDAlista* camino){
	NodoL* aux1 = camino->head;
	int bandera = 0;
	//iterador para ver los elementos del camino
	while(aux1->next!=NULL){
		if(grafo->MA[aux1->dato][aux1->next->dato] != 1){
			return 0;
		}
		aux1 = aux1->next;
	}
	//si completa el ciclo el camino se cumple
	return 1;
}

/*es completo si cada vertice tiene todas sus aristas posibles
excepto consigo mismo (grafo simple)*/
int esCompleto(TDAgrafo* grafo){
	for (int i = 0; i < grafo->cantv; i++){
		for (int j = 0; j < grafo->cantv; j++){
			if(i != j && grafo->MA[i][j]!=1){
				return 0;
			}
		}
	}
	return 1;
}

/*grafo complemento es aquel que tiene todas las aristas que no tiene el otro
grafo y le faltan las aristas de este mismo*/
int esComplemento(TDAgrafo* grafo1, TDAgrafo* grafo2){
	int vertices = grafo1->cantv;
	for(int i=0; i<vertices-1 ; i++){
		for(int j=0; j<vertices-1 ; j++){
			if(i!=j){
				if(grafo1->MA[i][j] == 0 && grafo2->MA[i][j] == 0){
					return 0;
				}
			}
		}
	}
	printf("\n");
	return 1;
}

int gradoDeVertice(TDAgrafo* grafo, int vertice){
	int grado = 0;
	for(int i=0; i<grafo->cantv; i++){
		if(i!=vertice){
			if(grafo->MA[vertice][i] == 1){
				grado += 1;
			}
		}
	}
	return grado;
}

int gradoPromedio(TDAgrafo* grafo){
	int suma = 0;
	for(int i=0; i<grafo->cantv; i++){
		suma += gradoDeVertice(grafo,i);
	}
	suma = suma/grafo->cantv;
	return suma;
}

int esRegular(TDAgrafo* grafo){
	int grado = gradoDeVertice(grafo,0);
	for(int i=1 ; i<grafo->cantv;i++){
		if(grado!=gradoDeVertice(grafo,i)){
			return 0;
		}
	}
	return 1;
}

/*----------------- FUNCIONES ESCENCIALES -----------------*/
//SOLO PARA NO PONDERADOS
void bsf(TDAgrafo* grafo, int inicio, int* visitados, int* distancias,int* precedencia){
	TDAcola* pendientes = crearColaVacia(grafo->cantv);
	TDAlista* adyacentes;
	NodoL* ptraux;
	int temp;
	
	for(int i = 0; i<grafo->cantv;i++){
		visitados[i] = 0;
		distancias[i] = __INT_MAX__;
		precedencia[i] = -1;
	}

	visitados[inicio] = 1; //marcar como visitado
	distancias[inicio] = 0;
	precedencia[inicio] = -1;
	encolar(pendientes,inicio);
	printf("Orden de visitados: %d\n", inicio);
	while(pendientes->size!=0){
		temp = descolar(pendientes);
		adyacentes = obtenerAdyacentes(grafo,temp);
		ptraux = adyacentes->head;
		while(ptraux!=NULL){
			if(visitados[ptraux->dato] == 0){
				printf("Orden de visitados: %d\n", ptraux->dato);
				visitados[ptraux->dato] = 1;
				distancias[ptraux->dato] = distancias[temp]+1;
				precedencia[ptraux->dato] = temp;
				encolar(pendientes,ptraux->dato);
			}
			ptraux = ptraux->next;
		}
	}
}

/*----------------- DSF -----------------*/
void dsf(TDAgrafo* grafo, int inicio, int* visitados, int* distancias,int* precedencia){
	TDApila* pendientes = crearPilaVacia();
	TDAlista* adyacentes;
	int temp;
	NodoL* ptraux;

	for(int i = 0; i<grafo->cantv;i++){
		visitados[i] = 0;
		distancias[i] = __INT_MAX__;
		precedencia[i] = -1;
	}

	visitados[inicio] = 0;
	distancias[inicio] = 0;
	precedencia[inicio] = -1;

	push(pendientes,inicio);

	while(pendientes->top!=NULL){
		temp = pop(pendientes);

		if(visitados[temp]== 0){
			printf("Orden de Visitados: %d\n",temp);
			visitados[temp] = 1;
			adyacentes = obtenerAdyacentes(grafo,temp);
			ptraux = adyacentes->head;

			while(ptraux!=NULL){
				if(visitados[ptraux->dato]==0){
					push(pendientes,ptraux->dato);
					distancias[ptraux->dato] = distancias[temp] + 1;
					precedencia[ptraux->dato] = temp;
				}
				ptraux = ptraux->next;
			}
		}
	}
}

/*----------------- DIJKSTRA -----------------*/
int quedanSinVisitar(int* visitados,int n);
int extraerMinimo(int* distancias, int* visitados,int n);
//recorrido minimo a todos los vertices desde el vertice "inicio"
void dijkstra(TDAgrafo* grafo, int inicio, int* visitados, int* distancias, int* precedencia){
	
	for(int i=0; i<grafo->cantv; i++){
		precedencia[i] = -1;
		visitados[i] = 0;
		if(grafo->MA[inicio][i]>0){ //ya que es ponderado coloca las distancias con sus respectivos pesos
			distancias[i] = grafo->MA[inicio][i];
			precedencia[i] = inicio;
		}
		else{
			distancias[i] = __INT16_MAX__;
		}
	}

	distancias[inicio] = 0;
	visitados[inicio] = 1;
	while(quedanSinVisitar(visitados,grafo->cantv)){
		int vertice = extraerMinimo(distancias,visitados,grafo->cantv);
		printf("vertice: %d\n",vertice);
		visitados[vertice] = 1;
		TDAlista* adyacentes = obtenerAdyacentes(grafo,vertice);
		NodoL* aux = adyacentes->head;
		printf("b\n");
		while(aux!=NULL){
			//comprobar la distancia minima al vertice que tiene aux
			if(distancias[aux->dato] > distancias[vertice]+grafo->MA[vertice][aux->dato]){
				distancias[aux->dato] = distancias[vertice]+grafo->MA[vertice][aux->dato];
				precedencia[aux->dato] = vertice;
			}
			aux = aux->next;
		}
	}
}
//funciones para dijkstra
//retorna 1 si queda al menos 1 vertice sin visitar
int quedanSinVisitar(int* visitados,int n){
	for(int i= 0; i<n ; i++){
		if(visitados[i]==0){
			return 1; //encuentra uno sin visitar
		}
	}
	return 0; //ya todos fueron visitados
}
//retorne el vertice con menor distancia
int extraerMinimo(int* distancias, int* visitados,int n){
	int minimo = __INT16_MAX__;
	int vertice = -1;
	for(int i=0 ; i<n ; i++){
		if(visitados[i]==0){
			if(distancias[i]<minimo){
				minimo = distancias[i];
				vertice = i;
			}
		}
	}
	return vertice;
}