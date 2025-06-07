#include <stdio.h>
#include <stdlib.h>

/*------------- ESTRUCTURA DE DATOS -------------*/

typedef struct nodoC{
  int dato;
  struct nodoC* next;
}NodoC;

typedef struct {
  int capacidad;
  int size;
  NodoC* frente;
  NodoC* final;
}TDAcola;

/*------------- SCOPE DE FUNCIONES -------------*/
TDAcola* crearColaVacio(int capacidad);
NodoC* crearNodoC();
int esColaVacio(TDAcola* cola);
int frente(TDAcola* cola);
int final(TDAcola* cola);
void imprimirCola(TDAcola* cola);
void encolar(TDAcola* cola, int dato);
int descolar(TDAcola* cola);
int numElementosCola(TDAcola* cola);

/*------------- FUNCIONES -------------*/
TDAcola* crearColaVacia(int capacidad){
  TDAcola* cola=(TDAcola*)malloc(sizeof(TDAcola));
  cola->capacidad=capacidad;
  cola->size=0;
  cola->frente=NULL;
  cola->final=NULL;
  return cola;
}

NodoC* crearNodoC(){
	NodoC* ndnuevo=(NodoC*)malloc(sizeof(NodoC));
	ndnuevo->next = NULL;
	return ndnuevo;
}

int esColaVacia(TDAcola* cola){
  if (cola->size == 0)
    return 1;
  else
    return 0;
}

int frente(TDAcola* cola){
  if (esColaVacia(cola))
  {
    printf("La cola está vacía\n");
  }
  else{
    return cola->frente->dato;
	}
}

int final(TDAcola* cola){
  if (esColaVacia(cola)){
    printf("La cola está vacía\n");
  }
  else{
    return cola->final->dato;
	}
}

void imprimirCola(TDAcola* cola){
	NodoC* aux = cola->frente;
	while(aux!=NULL){
		printf("%d  ",aux->dato);
		aux = aux->next;
	}
	printf("\n");
}

/*------------ Actividad 2 ------------*/
void encolar(TDAcola* cola, int dato){
	NodoC* ndnuevo = crearNodoC();
	ndnuevo->dato = dato;
	if(esColaVacia(cola)){
		cola->frente = ndnuevo;
		cola->final = ndnuevo;
		cola->size += 1;
	}
	else if(cola->size < cola->capacidad){
		cola->final->next = ndnuevo;
		cola->final = ndnuevo;
		cola->size += 1;
	}
}

/*------------ Actividad 3 ------------*/
int descolar(TDAcola* cola){
	if(esColaVacia(cola)==0){
		int valor = cola->frente->dato;
		if(cola->size == 1){
			free(cola->frente);
			cola->frente = NULL;
			cola->final = NULL;
		}
		else{
			NodoC* aux = cola->frente;
			cola->frente = aux->next;
			free(aux);
		}
		cola->size -= 1;
		return valor;
	}
}

/*------------ Actividad 4 ------------*/
int numElementosCola(TDAcola* cola){
	return cola->size;
}

/*------------ Actividad 5 ------------*/
TDAcola* reemplazarOcurrenciasSuma(TDAcola* cola, int v1, int v2){
	TDAcola* colanueva = crearColaVacia(cola->capacidad);
	if(esColaVacia(cola)==0){
		NodoC* aux = cola->frente;
		while(aux!=NULL){
			if(aux->dato == v1){
				encolar(colanueva,v2-v1);
			}
			else{
				encolar(colanueva,aux->dato);
			}
			aux = aux->next;
		}
	}
	return colanueva;
}

/*------------ Actividad 6 ------------*/
void ordenarAscendente(TDAcola* cola){
	NodoC* aux1 = cola->frente;
	NodoC* aux2;
	int temp;
	while(aux1!=NULL){
		aux2 = aux1;
		while (aux2!=NULL){
			if(aux1->dato>aux2->dato){
				temp=aux1->dato;
				aux1->dato=aux2->dato;
				aux2->dato=temp;
			}
			aux2 = aux2->next;
		}
		aux1 = aux1->next;
	}
}
