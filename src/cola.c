#include "cola.h"
#include <stdlib.h>
#include <stdio.h>

/*Se define los struct para nodo y para cola*/

struct nodo {
	void* dato;
	struct nodo* prox;
};
typedef struct nodo nodo_t;

struct cola {
	nodo_t* prim;
	nodo_t* ult;
};


/* *****************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

cola_t* cola_crear(void) {
	cola_t* cola = malloc(sizeof(cola_t));
	if (cola == NULL) {
		return NULL;
	}
	cola->prim = NULL; 
	return cola;
}

//**********************************************************************

bool cola_esta_vacia(const cola_t *cola) {
	return cola->prim == NULL;
}

//**********************************************************************

void* cola_ver_primero(const cola_t *cola) {
	if (cola_esta_vacia(cola)) {
		return NULL;
	}
	return cola->prim->dato; 
}

//**********************************************************************

bool cola_encolar(cola_t *cola, void* valor) { 
	/*Le pido lugar al heap para el nodo nuevo*/
	nodo_t* nuevo_nodo = malloc(sizeof(nodo_t));
	if (nuevo_nodo == NULL) {
		return false;
	}

	/*Le asigno el dato al nuevo nodo*/
	nuevo_nodo->dato= valor;
	
	/*Si la cola esta vacia este nodo sera el primero y el ultimo, le
	asigno las referencias*/
	if (cola_esta_vacia(cola)) {
		cola->prim = nuevo_nodo;
		cola->ult = nuevo_nodo;
		cola->ult->prox = NULL;
		return true;
	}

	/*Si ya tiene elementos le asigno el nodo al final*/
	cola->ult->prox = nuevo_nodo;
	cola->ult = nuevo_nodo;
	nuevo_nodo->prox = NULL;
	return true;
}

//**********************************************************************

void* cola_desencolar(cola_t *cola) {
	/*Si la cola esta vacia devuelvo NULL*/
	if (cola_esta_vacia(cola)) {
		return NULL;
	}
	void* dato_devolver = cola->prim->dato;
	nodo_t* aux = cola->prim; 
	cola->prim = cola->prim->prox;
	free(aux);
	return dato_devolver; 
}

//**********************************************************************

void cola_destruir(cola_t *cola, void destruir_dato(void*)) {
	/*Recorro todos los nodos para destruirlos*/
	while (cola->prim) {
		nodo_t* aux = cola->prim;
		void* dato = aux->dato;
		cola->prim = cola->prim->prox;
		
		/*Verifico que el usuario quiere destruir los datos*/
		if (destruir_dato != NULL) {
			destruir_dato(dato);
		}
		free(aux);
	} 
	free(cola);
}













//pruebas: encolar con cola vacia y con cola que tenga elementos
// desencolar con cola vacia y con cola con elementos (cuando hay uno solo y cuando hay muchos) 

