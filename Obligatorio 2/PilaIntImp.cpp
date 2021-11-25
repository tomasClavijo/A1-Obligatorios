#include "PilaInt.h"

#ifdef PILA_INT_IMP

struct _cabezalPilaInt {
	NodoListaInt* contenido;
	int numeroDeElementos;
};

/* AUXILIARES */

//PRE: -
//POS: Agrega el elemento al principio de la lista.
void agregarPrincipio(NodoListaInt*& lista, int dato) {
	NodoListaInt* nuevo = new NodoListaInt;
	nuevo->dato = dato;
	nuevo->sig = lista;
	lista = nuevo;
}

//PRE: -
//POS: Si no es vacia, elimina el elemento al principio de la lista.
void eliminarPrincipio(NodoListaInt*& lista) {
	if (lista != NULL) {
		NodoListaInt* aBorrar = lista;
		lista = lista->sig;
		delete aBorrar;
	}
}

//PRE: -
//POS: Agrega el elemento al final de la lista.
void agregarFinal(NodoListaInt*& lista, int dato) {
	if (lista != NULL) {
		NodoListaInt* listaAuxiliar = lista;
		while (listaAuxiliar->sig != NULL) {
			listaAuxiliar = listaAuxiliar->sig;
		}
		NodoListaInt* nodo = new NodoListaInt;
		nodo->dato = dato;
		nodo->sig = NULL;
		listaAuxiliar->sig = nodo;
	}
	else {
		NodoListaInt* nodo = new NodoListaInt;
		nodo->dato = dato;
		nodo->sig = NULL;
		lista = nodo;
	}
}
/*FIN AUXILIARES*/

PilaInt crearPilaInt(){
	PilaInt pila = new _cabezalPilaInt;
	pila->numeroDeElementos = 0;
	pila->contenido = NULL;
	return pila;
}

void push(PilaInt& p, int e) {
	agregarPrincipio(p->contenido, e);
	p->numeroDeElementos++;
}

int top(PilaInt p) {
	assert(!esVacia(p));
	return (p->contenido->dato);
}

void pop(PilaInt& p) {
	assert(!esVacia(p));
	eliminarPrincipio(p->contenido);
	p->numeroDeElementos--;
}

unsigned int cantidadElementos(PilaInt p) {
	return p->numeroDeElementos;
}

bool esVacia(PilaInt p) {
	return (p->numeroDeElementos == 0);
}

PilaInt clon(PilaInt p) {
	PilaInt clon = crearPilaInt();
	clon->numeroDeElementos = p->numeroDeElementos;
	NodoListaInt* auxiliar = p->contenido;
	while (auxiliar != NULL) {
		agregarFinal(clon->contenido, auxiliar->dato);
		auxiliar = auxiliar->sig;
	}
	return clon;
}

void destruir(PilaInt& p) {
	while (p->contenido != NULL) {
		eliminarPrincipio(p->contenido);
	}
	delete p;
	p == NULL;
}


#endif