#include "ColaPrioridadInt.h"

#ifdef COLAPRIORIDAD_INT_IMP

struct elemento {
	int dato;
	int prioridad;
};

struct _cabezalColaPrioridadInt {
	elemento** cola;
	int cantidadElementos;
	int cota;
	int maximaPrioridad;
};

ColaPrioridadInt crearColaPrioridadInt(unsigned int cota) {
	ColaPrioridadInt nuevo = new _cabezalColaPrioridadInt;
	nuevo->cola = new elemento * [25];
	for (int i = 0; i < 25; i++) {
		nuevo->cola[i] = NULL;
	}
	nuevo->cantidadElementos = 0;
	nuevo->cota = cota;
	nuevo->maximaPrioridad = INT_MIN;
	return nuevo;
}

void encolar(ColaPrioridadInt& c, int e, int p) {
	assert(!esLlena(c));
	elemento* nuevo = new elemento;
	nuevo->dato = e;
	nuevo->prioridad = p;
	if (p > c->maximaPrioridad) {
		c->maximaPrioridad = p;
	}
	c->cola[c->cantidadElementos] = nuevo;
	c->cantidadElementos++;
}

int principio(ColaPrioridadInt c) {
	assert(!esVacia(c));
	for (int i = 0; i < c->cantidadElementos; i++) {
		if (c->cola[i]->prioridad == c->maximaPrioridad) {
			return c->cola[i]->dato;
		}
	}
}

int principioPrioridad(ColaPrioridadInt c) {
	assert(!esVacia(c));
	return c->maximaPrioridad;
}

void desencolar(ColaPrioridadInt& c) {
	assert(!esVacia(c));
	int mover = 0;
	int ultimaPosicion = c->cantidadElementos;
	for (int i = c->cantidadElementos - 1; i >= 0; i--) {
		if (c->cola[i]->prioridad == c->maximaPrioridad) {
			mover = i;
		}
	}
	for (int i = mover; i < c->cantidadElementos - 1; i++) {
		c->cola[i] = c->cola[i + 1];
	}
	c->cantidadElementos--;
	c->cola[ultimaPosicion] = NULL;
	int nuevaMaximaPrioridad = c->cola[0]->prioridad;
	for (int i = 1; i < c->cantidadElementos; i++) {
		if (c->cola[i]->prioridad >= nuevaMaximaPrioridad) {
			nuevaMaximaPrioridad = c->cola[i]->prioridad;
		}
	}
	c->maximaPrioridad = nuevaMaximaPrioridad;
}

bool esVacia(ColaPrioridadInt c) {
	return c->cantidadElementos == 0;
}

bool esLlena(ColaPrioridadInt c) {
	return c->cantidadElementos == c->cota;
}

unsigned int cantidadElementos(ColaPrioridadInt c) {
	return c->cantidadElementos;
}

ColaPrioridadInt clon(ColaPrioridadInt c) {
	ColaPrioridadInt clon = crearColaPrioridadInt(c->cota);

	for (int i = 0; i < c->cantidadElementos; i++) {
		int dato = c->cola[i]->dato;
		int prioridad = c->cola[i]->prioridad;
		encolar(clon, dato, prioridad);
	}
	return clon;
}

void destruir(ColaPrioridadInt& c) {
	delete[] c->cola;
	delete c;
	c = NULL;
}

#endif