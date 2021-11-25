#include "ListaPosInt.h"

#ifdef LISTA_POS_INT_IMP

struct _cabezalListaPosInt {
	int* datos;
	unsigned int cantElementos;
	unsigned int largoArray;
};

ListaPosInt crearListaPosInt()
{
	_cabezalListaPosInt* listaPosInt = new _cabezalListaPosInt;
	listaPosInt->datos = new int[25];
	listaPosInt->largoArray = 25;
	listaPosInt->cantElementos = 0;
	return listaPosInt;
}

void agregar(ListaPosInt& l, int e, unsigned int pos)
{
	if (l->largoArray == l->cantElementos) { 
		int* datos = new int[25 + l->largoArray];
		l->largoArray += 25;
		for (int i = 0; i < l->cantElementos; i++) {
			datos[i] = l->datos[i];
		}
		delete[] l->datos;
		l->datos = datos;
	}
	if (pos >= l->cantElementos) {
		l->datos[l->cantElementos] = e;
	}
	else {
		for (int i = l->cantElementos - 1; i >= pos; i--) {
			if (i == pos) {
				l->datos[l->cantElementos] = l->datos[l->cantElementos - 1];
				l->datos[pos] = e;
			}
			else {
				l->datos[l->cantElementos] = l->datos[l->cantElementos - 1];
			}
		}
	}
	l->cantElementos++;
}


void borrar(ListaPosInt& l, unsigned int pos)
{
	if (l->cantElementos != 0) {
		if (pos >= l->cantElementos) {
			return;
		}
		else {
			for (int i = pos; i < l->cantElementos - 1; i++) {
				l->datos[i] = l->datos[i + 1];
			}
			l->cantElementos--;
		}

	}
}

int elemento(ListaPosInt l, unsigned int pos)
{
	assert(0 <= pos && pos < l->cantElementos);
	return l->datos[pos];
}

bool esVacia(ListaPosInt l)
{
	return l->cantElementos == 0;
}

unsigned int cantidadElementos(ListaPosInt l)
{
	return l->cantElementos;
}

ListaPosInt clon(ListaPosInt l)
{
	ListaPosInt clon = crearListaPosInt();
	for (int i = 0; i < l->cantElementos; i++) {
		agregar(clon, l->datos[i], i);
	}

	return clon;
}

void destruir(ListaPosInt& l)
{
	delete[] l->datos;
	delete l;
	l = NULL;
}


#endif