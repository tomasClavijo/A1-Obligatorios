#include "ListaOrdInt.h"

#ifdef LISTA_ORD_INT_IMP_2

struct _cabezalListaOrdInt {
	NodoABIntDobleDato* raiz;
	int numeroDeElementos;
};

/* AUXILIARES */

//PRE: -
//POS: Retorna el elemento maximo del árbol.
NodoABIntDobleDato * maximoArbolBB(NodoABIntDobleDato * a) {
	assert(a != NULL);
	if (a->der == NULL) {
		return a;
	}
	else {
		maximoArbolBB(a->der);
	}
}

//PRE:-
//POS: Retorna el elemento mínimo del árbol.
NodoABIntDobleDato* minimoArbolBB(NodoABIntDobleDato* a) {
	assert(a != NULL);
	if (a->izq == NULL) {
		return a;
	}
	else {
		minimoArbolBB(a->izq);
	}
}

//PRE: -
//POS: Agrega el elemento al árbol.
void agregarABBRepetidos(NodoABIntDobleDato*& raiz, int e) {
	if (raiz == NULL) {
		NodoABIntDobleDato* nuevo = new NodoABIntDobleDato;
		nuevo->dato1 = e;
		nuevo->dato2 = 1;
		nuevo->izq = NULL;
		nuevo->der = NULL;
		raiz = nuevo;
	}
	else if (raiz->dato1 == e) {
		raiz->dato2++;
	}
	else if (raiz->dato1 > e) {
		agregarABBRepetidos(raiz->izq, e);
	}
	else if (raiz->dato1 < e) {
		agregarABBRepetidos(raiz->der, e);
	}
}

//PRE: (l != NULL)
//POS: Elimina el nodo mínimo del árbol.
void eliminarMinABBMs(NodoABIntDobleDato*& l) {
	assert(l != NULL);
	if (l->izq == NULL) {
		NodoABIntDobleDato* nodoBorrar = l;
		l = l->der;
		delete nodoBorrar;
	}
	else {
		eliminarMinABBMs(l->izq);
	}
}

//PRE: -
//POS: Retorna true si el elemento se encuentra presente en el árbol, en caso contrario false.
bool existeElemento(NodoABIntDobleDato* raiz, int e) {
	if (raiz == NULL) {
		return false;
	}
	else if (raiz->dato1 == e) {
		return true;
	}
	else if (raiz->dato1 < e) {
		return existeElemento(raiz->der, e);
	}
	else {
		existeElemento(raiz->izq, e);
	}
}

//PRE: -
//POS: Si no es vacío, vacía el árbol. 
void vaciar(NodoABIntDobleDato*& raiz) {
	if (raiz != NULL) {
		vaciar(raiz->izq);
		vaciar(raiz->der);
		delete raiz;
		raiz = NULL;
	}
}

//PRE: -
//POS: Si no es vacío, borra el elemento que se pasa por parámetro.
void borrarConRepetidos(NodoABIntDobleDato*& a, ListaOrdInt& l ,int e) {
	if (a != NULL) {
		if (e < a->dato1) {
			borrarConRepetidos(a->izq, l ,e);
		}
		else if (e > a->dato1) {
			borrarConRepetidos(a->der,l ,e);
		}
		else {
			if (a->izq == NULL && a->der == NULL) {
				if (a->dato2 == 1) {
					delete a;
					a = NULL;
					l->numeroDeElementos--;
				}
				else {
					a->dato2--;
					l->numeroDeElementos--;
				}
			}
			else if (a->izq != NULL && a->der == NULL) {
				if (a->dato2 == 1) {
					NodoABIntDobleDato* borrar = a;
					a = a->izq;
					delete borrar;
					l->numeroDeElementos--;
				}
				else {
					a->dato2--;
					l->numeroDeElementos--;
				}

			}
			else if (a->izq == NULL && a->der != NULL) {
				if (a->dato2 == 1) {
					NodoABIntDobleDato* borrar = a;
					a = a->der;
					delete borrar;
					l->numeroDeElementos--;
				}
				else {
					a->dato2--;
					l->numeroDeElementos--;
				}

			}
			else {
				NodoABIntDobleDato* min_a_der = minimoArbolBB(a->der);
				a->dato1 = min_a_der->dato1;
				a->dato2 = min_a_der->dato2;
				eliminarMinABBMs(a->der);
				l->numeroDeElementos--;
			}
		}
	}
}

//PRE: -
//POS: Clona el árbol.
NodoABIntDobleDato* clonArbol(NodoABIntDobleDato* l) {
	if (l == NULL) {
		return NULL;
	}
	else {
		NodoABIntDobleDato* nuevo = new NodoABIntDobleDato;
		nuevo->dato1 = l->dato1;
		nuevo->dato2 = l->dato2;
		nuevo->izq = clonArbol(l->izq);
		nuevo->der = clonArbol(l->der);
		return nuevo;
	}
}

/* FIN AUXILIARES */


ListaOrdInt crearListaOrdInt() {
	ListaOrdInt cabezal = new _cabezalListaOrdInt;
	cabezal->raiz = NULL;
	cabezal->numeroDeElementos = 0;
	return cabezal;
}

void agregar(ListaOrdInt& l, int e) {
	agregarABBRepetidos(l->raiz, e);
	l->numeroDeElementos++;
}

void borrarMinimo(ListaOrdInt& l) {
	if (l->raiz != NULL) {
		borrarConRepetidos(l->raiz, l,minimo(l));
	}
}

void borrarMaximo(ListaOrdInt& l) {
	if (l->raiz != NULL) {
		borrarConRepetidos(l->raiz, l, maximo(l));
	}
}

void borrar(ListaOrdInt& l, int e) {
	borrarConRepetidos(l->raiz, l, e);
}

int minimo(ListaOrdInt l) {
	assert(!esVacia(l));
	NodoABIntDobleDato* nodoMinimo = minimoArbolBB(l->raiz);
	return nodoMinimo->dato1;
}

int maximo(ListaOrdInt l) {
	assert(!esVacia(l));
	NodoABIntDobleDato* nodoMaximo = maximoArbolBB(l->raiz);
	return nodoMaximo->dato1;
}

bool existe(ListaOrdInt l, int e) {
	return existeElemento(l->raiz, e);
}

bool esVacia(ListaOrdInt l) {
	return (l->numeroDeElementos == 0);
}

unsigned int cantidadElementos(ListaOrdInt l) {
	return l->numeroDeElementos;
}

ListaOrdInt clon(ListaOrdInt l) {
	ListaOrdInt cabezal = new _cabezalListaOrdInt;
	cabezal->raiz = clonArbol(l->raiz);
	cabezal->numeroDeElementos = l->numeroDeElementos;
	return cabezal;
}

void destruir(ListaOrdInt& l) {
	vaciar(l->raiz);
	delete l;
	l = NULL;

}



#endif