#include "ColaInt.h"

#ifdef COLA_INT_IMP

struct _cabezalColaInt {
	NodoListaInt* primero, * ultimo;
	int cantDeElementos;
};

ColaInt crearColaInt() {
	ColaInt cola = new _cabezalColaInt;
	cola->primero = NULL;
	cola->ultimo = NULL;
	cola->cantDeElementos = 0;
	return cola;
}

void encolar(ColaInt& c, int e) {
	NodoListaInt* nuevo = new NodoListaInt;
	nuevo->dato = e;
	nuevo->sig = NULL;
	if (c->primero == NULL) {
		c->primero = nuevo;
		c->ultimo = nuevo;
	}
	else {
		c->ultimo->sig = nuevo;
		c->ultimo = nuevo;
	}
	c->cantDeElementos++;
}

int principio(ColaInt c) {
	assert(!esVacia(c));
	return c->primero->dato;
}

void desencolar(ColaInt& c) {
	assert(!esVacia(c));
	NodoListaInt* temp = c->primero;
	c->primero = c->primero->sig;
	if (c->primero == NULL) {
		c->ultimo = NULL;
	}
	delete temp;
	c->cantDeElementos--;
}

bool esVacia(ColaInt c) {
	return (c->primero == NULL);
}

unsigned int cantidadElementos(ColaInt c) {
	return c->cantDeElementos;
}

ColaInt clon(ColaInt c) {
	ColaInt retorno = crearColaInt();
	NodoListaInt* auxiliar = c->primero;
	while (auxiliar != NULL) {
		encolar(retorno, auxiliar->dato);
		auxiliar = auxiliar->sig;
	}
	return retorno;
}

void destruir(ColaInt& c) {
	NodoListaInt* temp;
	while (c->primero != NULL) {
		temp = c->primero;
		c->primero = c->primero->sig;
		delete temp;
	}
	delete c;
	c = NULL;
}

#endif