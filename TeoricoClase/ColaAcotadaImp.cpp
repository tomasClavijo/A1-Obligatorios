#include "ColaAcotada.h"

struct _representacionColaAcotada {
	int* arr;
	unsigned int inicio;
	unsigned int fin;

	unsigned int cota;
	unsigned int cantidadElementos;
};

ColaAcotada crearCola(unsigned int cota)
{
	ColaAcotada c = new _representacionColaAcotada;
	c->arr = new int[cota];
	c->inicio = 0;
	c->fin = 0;
	c->cota = cota;
	c->cantidadElementos = 0;
	return c;
}

void encolar(ColaAcotada & c, int e)
{
	assert(!estaLlena(c));
	c->arr[c->fin] = e;
	c->fin++;
	c->cantidadElementos++;
	if (c->fin == c->cota) {
		c->fin = 0;
	}
}

int frente(ColaAcotada c)
{
	assert(!esVacia(c));
	return c->arr[c->inicio];
}

void desencolar(ColaAcotada & c)
{
	assert(!esVacia(c));
	c->inicio++;
	c->cantidadElementos--;
	if (c->inicio == c->cota) {
		c->inicio = 0;
	}
}

bool esVacia(ColaAcotada c)
{
	return c->cantidadElementos == 0;
}

bool estaLlena(ColaAcotada c)
{
	return c->cantidadElementos == c->cota;
}

void destruir(ColaAcotada & c)
{
	delete[] c->arr;
	delete c;
	c = NULL;
}
