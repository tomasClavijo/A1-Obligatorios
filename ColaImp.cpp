#include "Cola.h"

struct _representacionCola {
	nodoLista* ppio;
	nodoLista* fin;
};

Cola crearCola() {
	Cola c = new _representacionCola;
	c->ppio = NULL;
	c->fin = NULL;
	return c;
}

void encolar(Cola & c, int e)
{
	nodoLista* nuevo = new nodoLista;	nuevo->dato = e;	nuevo->sig = NULL;	if (c->fin == NULL) {		c->fin = nuevo;		c->ppio = nuevo;	}	else {		c->fin->sig = nuevo;		c->fin = nuevo;	}
}

int frente(Cola c)
{
	assert(!esVacia(c));
	return c->ppio->dato;
}

void desencolar(Cola & c)
{
	assert(!esVacia(c));
	nodoLista* aBorrar = c->ppio;
	c->ppio = c->ppio->sig;
	if (c->ppio == NULL) {
		c->fin = NULL;
	}
	delete aBorrar;
}

bool esVacia(Cola c)
{
	return c->ppio == NULL;
}

void destruir(Cola & c)
{
	while (c->ppio != NULL) {
		nodoLista* aBorrar = c->ppio;
		c->ppio = c->ppio->sig;
		delete aBorrar;
	}
	delete c;
	c = NULL;
}
