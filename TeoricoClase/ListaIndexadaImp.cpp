#include "ListaIndexada.h"

struct nodoLista {
	int dato;
	nodoLista* sig;
};

struct _representacionListaIndexada {
	nodoLista* ppio;
	unsigned int cantElementos;
};

/* Inicio funciones auxiliares */

void insertarPos(nodoLista* &l, unsigned int n, int e) {
	if (l == NULL) {
		insertarPpio(l, e);
	}
	else {
		if (n == 0) {
			insertarPpio(l, e);
		}
		else {
			insertarPos(l->sig, n - 1, e);
		}
	}
}

void insertarPpio(nodoLista* &l, int e) {
	nodoLista* nodo = new nodoLista;
	nodo->dato = e;
	nodo->sig = l;
	l = nodo;
}

void borrarPos(nodoLista* &l, unsigned int n) {
	if (l != NULL) {
		if (n == 0) {
			nodoLista* aBorrar = l;
			l = l->sig;
			delete aBorrar;
		}
		else {
			borrarPos(l->sig, n - 1);
		}
	}
}

void vaciar(nodoLista* &l) {
	if (l != NULL) {
		nodoLista* aBorrar = l;
		vaciar(l->sig);
		delete aBorrar;
		l = NULL;
	}
}

/* Fin funciones auxiliares */

ListaIndexada crearLista() {
	ListaIndexada lista = new _representacionListaIndexada;
	lista->ppio = NULL;
	lista->cantElementos = 0;
	return lista;
}

void insertar(ListaIndexada &l, unsigned int n, int e) {
	insertarPos(l->ppio, n, e);
	l->cantElementos++;
}

bool esVacia(ListaIndexada l) {
	return l->cantElementos == 0; // return l->ppio == NULL; return largo(l) == 0;
}

bool estaDefinida(ListaIndexada l, unsigned int n) {
	return n < l->cantElementos;
}

int elemento(ListaIndexada l, unsigned int n) {
	assert(estaDefinida(l, n));
	nodoLista* aux = l->ppio;
	while (aux != NULL) {
		if (n == 0)
			return aux->dato;
		n--;
		aux = aux->sig;
	}
}

void borrar(ListaIndexada &l, unsigned int n) {
	assert(estaDefinida(l, n));
	borrarPos(l->ppio, n);
	l->cantElementos--;
}

unsigned int largo(ListaIndexada l) {
	return l->cantElementos;
}

void destruir(ListaIndexada &l) {
	vaciar(l->ppio);
	l->cantElementos = 0;
	delete l;
	l = NULL;
	/*
	Opcion 2:
	while (!esVacia(l)) {
		borrar(l, 0);
	}
	delete l;
	l = NULL;
	*/
}