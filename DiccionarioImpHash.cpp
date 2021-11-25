#include "Diccionario.h"

struct nodoLista {
	int clave;
	nodoLista* sig;
};

struct _representacionDiccionario {
	nodoLista** hash;
	unsigned int ocupadas;
	unsigned int capacidad;
};

// Inicio funciones auxiliares

unsigned int funcionHash(int clave, unsigned int capacidad) {
	return clave % capacidad;
}

void chequearFactorDeOcupacion(Diccionario &d) {
	float factorCarga = (float)d->ocupadas / (float)d->capacidad;
	if (factorCarga >= 1) {
		// Redimensionar el hash
	}
}

// Fin funciones auxiliares

Diccionario crearDiccionario(unsigned int cantidadElementosEsperados) {
	Diccionario diccionario = new _representacionDiccionario;
	diccionario->hash = new nodoLista*[cantidadElementosEsperados]; // TODO: Buscar el siguiente primo de 'cantidadElementosEsperados'
	diccionario->ocupadas = 0;
	diccionario->capacidad = cantidadElementosEsperados;
	for (unsigned int i = 0; i < diccionario->capacidad; i++) {
		diccionario->hash[i] = NULL;
	}
	return diccionario;
}

void agregar(Diccionario & d, int e)
{
	chequearFactorDeOcupacion(d);
	if (!pertenece(d, e)) {
		unsigned int cubeta = funcionHash(e, d->capacidad);
		nodoLista* nodo = new nodoLista;
		nodo->clave = e;
		nodo->sig = d->hash[cubeta];
		d->hash[cubeta] = nodo;
		d->ocupadas++;
	}
}

void borrar(Diccionario & d, int e)
{
	unsigned int cubeta = funcionHash(e, d->capacidad);
	nodoLista* listaCubeta = d->hash[cubeta];
	nodoLista* antLista = NULL;
	while (listaCubeta != NULL) {
		if (listaCubeta->clave == e) {
			nodoLista* aBorrar = listaCubeta;
			if (antLista != NULL) {
				antLista->sig = listaCubeta->sig;
			}
			else {
				d->hash[cubeta] = listaCubeta->sig;
			}
			delete aBorrar;
			d->ocupadas--;
			return;
		}
		antLista = listaCubeta;
		listaCubeta = listaCubeta->sig;
	}
}

bool pertenece(Diccionario d, int e)
{
	unsigned int cubeta = funcionHash(e, d->capacidad);
	nodoLista* listaCubeta = d->hash[cubeta];
	while (listaCubeta != NULL) {
		if (listaCubeta->clave == e)
			return true;
		listaCubeta = listaCubeta->sig;
	}
	return false;
}

bool esVacio(Diccionario d)
{
	return d->ocupadas == 0;
}

unsigned int cantidadElementos(Diccionario d)
{
	return d->ocupadas;
}

int elemento(Diccionario d)
{
	assert(!esVacio(d));
	unsigned int cubeta = 0;
	while (d->hash[cubeta] == NULL) {
		cubeta++;
	}
	return d->hash[cubeta]->clave;
}

Diccionario clon(Diccionario d)
{
	Diccionario clon = crearDiccionario(d->capacidad);
	for (unsigned int cubeta = 0; cubeta < d->capacidad; cubeta++) {
		nodoLista* lista = d->hash[cubeta];
		while (lista != NULL) {
			agregar(clon, lista->clave);
			lista = lista->sig;
		}
	}
	return clon;
}

void destruir(Diccionario & d)
{
	for (unsigned int cubeta = 0; cubeta < d->capacidad; cubeta++) {
		nodoLista* lista = d->hash[cubeta];
		while (lista != NULL) {
			nodoLista* aBorrar = lista;
			lista = lista->sig;
			delete aBorrar;
		}
	}
	delete[] d->hash;
	delete d;
	d = NULL;
}

