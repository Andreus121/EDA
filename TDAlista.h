#include <stdio.h>
#include <stdlib.h>

/*------------- ESTRUCTURA DE DATOS -------------*/
typedef struct nodoL{
	int dato;
	struct nodoL * next;
}NodoL;

typedef struct lista{
  NodoL *head;
}TDAlista;

/*----------------- SCOPE DE FUNCIONES -----------------*/

TDAlista *crearLista();
NodoL *crearNodoL();
int listaVacia(TDAlista *L);
void imprimirLista(TDAlista *L);
int largoLista(TDAlista *L);
void insertarInicio(TDAlista *L, int val);
void insertarFin(TDAlista *L,int val);
void insertarPos(TDAlista *L, int val, int pos);
void eliminarInicio(TDAlista *L);
void eliminarFin(TDAlista *L);
void eliminarPos(TDAlista *L,int pos);

/*----------------- FUNCIONES -----------------*/

TDAlista *crearLista(){
	TDAlista *L = (TDAlista*)malloc(sizeof(TDAlista));
  	L->head = NULL;
	return L;
}

NodoL *crearNodoL(){
	NodoL *N;
	N = (NodoL*)malloc(sizeof(NodoL));
    N->next = NULL;
    return N;
}

int listaVacia(TDAlista *L){
	if(L->head==NULL){
		return 1;
	}
	return 0;
}

void imprimirLista(TDAlista *L){
	if(listaVacia(L)){
		printf("La lista no tiene ningun elemento\n");
		return;
	}
	NodoL *temporal = L->head;
	while(temporal != NULL){
		printf("%d  ",temporal->dato);
		temporal = temporal->next;
	}
	printf("\n");
	return;
}

int largoLista(TDAlista *L){
	int contador = 0;
	if(listaVacia(L)){
		return contador;
	}
	NodoL *aux = L->head;
	while(aux!=NULL){
		contador+=1;
		aux=aux->next;
	}
	return contador;

}

void insertarInicio(TDAlista *L, int val){
	NodoL *ndnuevo = crearNodoL();
	ndnuevo->dato = val;
	if(L->head==NULL){
		L->head=ndnuevo;
	}
	else{
		ndnuevo->next=L->head;
		L->head=ndnuevo;
	}
	
}

void insertarFin(TDAlista *L, int val){
	NodoL *ndnuevo = crearNodoL();
	ndnuevo ->dato = val;
	NodoL *temporal = L->head;
	if(listaVacia(L)){
		L->head = ndnuevo;
		return;
	}
	else{
		while(temporal->next != NULL){
			temporal = temporal->next;
		}
	}
	temporal->next=ndnuevo;
	return;
}

void insertarPos(TDAlista *L, int val, int pos){
	NodoL *ndnuevo = crearNodoL();
	ndnuevo->dato = val;
	NodoL *aux = L->head;
	if(pos>largoLista(L)){
		insertarFin(L,val);
		return;
	}
	if(pos==0){
		insertarInicio(L,val);
		return;
	}
	for(int i = 0;i<pos-1;i++){
		aux=aux->next;
	}
	ndnuevo->next=aux->next;
	aux->next=ndnuevo;
	return;
}

void eliminarInicio(TDAlista *L){
	if(listaVacia(L)){
		return;
	}
	NodoL *aux = L->head->next;
	free(L->head);
	L->head = aux;
	return;
}

void eliminarFin(TDAlista *L){
	NodoL *aux = L->head;
	if(listaVacia(L)){
		return;
	}
	else if(largoLista(L)==1){
		free(L->head);
		L->head = NULL;
		return;
	}
	else{
		while(aux->next->next!=NULL){
			aux = aux->next;
		}
	}
	free(aux->next);
	aux->next=NULL;
	return;
}

void eliminarPos(TDAlista *L, int pos){
	NodoL *aux = L->head;
	NodoL *temp;
	if(pos==0){
		eliminarInicio(L);
		return;
	}
	if(pos>largoLista(L)){
		return;
	}
	for(int i=0;i<pos-1;i++){
		aux=aux->next;
	}
	temp = aux->next->next;
	free(aux->next);
	aux->next = temp;
	return;
}

//void ordenarlista(TDAlista *L){}
