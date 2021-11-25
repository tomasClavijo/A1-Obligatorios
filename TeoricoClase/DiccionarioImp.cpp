#include "Diccionario.h"

struct _representacionDiccionario {
	bool* arr;
	unsigned int cota;
	unsigned int cantidadElementos;
};

Diccionario crearDiccionario(unsigned int cota) {
	Diccionario d = new _representacionDiccionario;
	d->arr = new bool[cota + 1];
	for (int i = 0; i <= cota; i++) {
		d->arr[i] = false;
	}
	d->cota = cota + 1;
	d->cantidadElementos = 0;
	return d;
}

void agregar(Diccionario & d, unsigned int e)
{
	assert(0 <= e && e < d->cota);
	if (!pertenece(d, e)) {
		d->arr[e] = true;
		d->cantidadElementos++;
	}
}

void borrar(Diccionario & d, unsigned int e)
{
	assert(0 <= e && e < d->cota);
	if (pertenece(d, e)) {
		d->arr[e] = false;
		d->cantidadElementos--;
	}
}

bool pertenece(Diccionario d, unsigned int e)
{
	assert(0 <= e && e < d->cota);
	return d->arr[e];
}

bool esVacio(Diccionario d)
{
	return d->cantidadElementos == 0;
}

unsigned int cantidadElementos(Diccionario d)
{
	return d->cantidadElementos;
}

unsigned int elemento(Diccionario d)
{
	assert(!esVacio(d));
	for (int i = 0; i < d->cota; i++) {
		if (d->arr[i] == true) {
			return i;
		}
	}
}

Diccionario clon(Diccionario d)
{
	/*
	Diccionario clon = new _representacionDiccionario;
	clon->arr = new bool[d->cota];
	clon->cantidadElementos = d->cantidadElementos;
	clon->cota = d->cota;
	for (int i = 0; i < clon->cota; i++) {
		clon->arr[i] = d->arr[i];
	}
	return clon;
	*/

	Diccionario clon = crearDiccionario(d->cota - 1);
	for (int i = 0; i < d->cota; i++) {
		if (d->arr[i] == true) {
			agregar(clon, i);
		}
	}
	return clon;
}

void destruir(Diccionario & d)
{
	delete[] d->arr;
	delete d;
	d = NULL;
}
