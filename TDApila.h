#include <stdio.h>
#include <stdlib.h>

/*------------ ESTRUCTURA DE DATOS ------------*/
typedef struct nodoP{
	int dato;
	struct nodoP *next;
}NodoP;

typedef struct pila{
	NodoP *top;
}TDApila;

/*------------ SCOPE DE FUNCIONES ------------*/
TDApila *crearPilaVacia();
NodoP *crearNodoP();
int top(TDApila* P);
void push(TDApila *p, char valor);
int pop(TDApila *p);
void mostrarPila(TDApila *p);

/*------------ FUNCIONES ------------*/
TDApila *crearPilaVacia(){
	TDApila *p = (TDApila*)malloc(sizeof(TDApila));
	p->top = NULL;
	return p;
}

NodoP *crearNodoP(){
	NodoP *n = (NodoP*)malloc(sizeof(NodoP));
	n->next = NULL;
	return n;
}

int top(TDApila* P){
	return P->top->dato;
}

void push(TDApila *p,char valor){
	NodoP *n = crearNodoP();
	n->dato = valor;

	n->next = p->top;
	p->top = n;
}

int pop(TDApila *p){
	NodoP *aux;
	int valor;
	if(p->top==NULL){
	}
	else{
		valor = p->top->dato;
		aux = p->top;
		p->top = aux->next;
		
		free(aux);
		return valor;
	}
}

void mostrarPila(TDApila *p){
	TDApila *ptemp = crearPilaVacia();
	NodoP *aux = crearNodoP();
	while(p->top!=NULL){
		aux = p->top;
		push(ptemp,aux->dato);
		printf("%d\n",aux->dato);
		pop(p);
		p->top = aux->next;
	}
	while(ptemp->top!=NULL){
		aux = ptemp->top;
		push(p,aux->dato);
		pop(p);
		ptemp->top = aux->next;
	}
}