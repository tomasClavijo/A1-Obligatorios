#include "MultisetInt.h"

#ifdef MULTISET_INT_IMP

struct _cabezalMultisetInt {
	NodoListaIntDobleDato* principio;
	unsigned int cantElementos;
};

/* FUNCIONES AUXILIARES */

//PRE: -
//POS: Retorna la cantidad de ocurrencias que presenta el elemento (e) en el multiset (s).
int ocurrencias(MultisetInt s, int e) {
	NodoListaIntDobleDato* auxiliar = s->principio;
	while (auxiliar != NULL) {
		if (auxiliar->dato1 == e) {
			return auxiliar->dato2;
		}
		auxiliar = auxiliar->sig;
	}
	return 0;
}

//PRE: -
//POS: Retorna true en caso de haber borrado el elemento, y false en caso de no haberlo hecho.
bool borrarElemento(NodoListaIntDobleDato*& principio, int dato) {
	if (principio != NULL) {
		if (principio->dato1 == dato) {
			NodoListaIntDobleDato* aBorrar = principio;
			principio = principio->sig;
			delete aBorrar;
			return true;
		}
		else {
			return borrarElemento(principio->sig, dato);
		}
	}
	else {
		return false;
	}
}

//PRE: -
//POS: Reemplaza en el multiset (s) las ocurrencias del elemento (e).
void remplazarOcurrencias(MultisetInt& s, int e, int ocurrencias) {
	NodoListaIntDobleDato* auxiliar = s->principio;
	while (auxiliar != NULL) {
		if (auxiliar->dato1 == e) {
			auxiliar->dato2 = ocurrencias;
			return;
		}
		auxiliar = auxiliar->sig;
	}
}

//PRE: -
//POS: Elimina el elemento de la lista.
void borrarTotal(NodoListaIntDobleDato*& principio, int dato) {
	if (principio != NULL) {
		if (principio->dato1 == dato) {
			NodoListaIntDobleDato* aBorrar = principio;
			principio = principio->sig;
			delete aBorrar;
		}
		else {
			return borrarTotal(principio->sig, dato);
		}
	}
}

//PRE: -
//POS: Retorna el menor entre dos valores.
int minimo(int a, int b) {
	if (a > b) {
		return b;
	}
	else {
		return a;
	}
}

//PRE: -
//POS: Retorna el mayor entre dos valores.
int maximo(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

//PRE: -
//POS: Retorna el nodo e.
NodoListaIntDobleDato* nodoOcurrencia(MultisetInt s, int e) {
	NodoListaIntDobleDato* auxiliar = s->principio;
	while (auxiliar != NULL) {
		if (auxiliar->dato1 == e) {
			return auxiliar;
		}
		auxiliar = auxiliar->sig;
	}
	return auxiliar; // En caso de que no lo encuentre, auxiliar será NULL. 
}

/* FIN FUNCIONES AUXILIARES*/

MultisetInt crearMultisetInt() {
	MultisetInt nuevo = new _cabezalMultisetInt;
	nuevo->cantElementos = 0;
	nuevo->principio = NULL;
	return nuevo;
}

void agregar(MultisetInt& s, int e, unsigned int ocurrencias){
	NodoListaIntDobleDato* auxiliar = s->principio;
	while (auxiliar != NULL) {
		if (auxiliar->dato1 == e) {
			auxiliar->dato2 += ocurrencias;
			s->cantElementos += ocurrencias;
			return;
		}
		auxiliar = auxiliar->sig;
	}
	if (auxiliar == NULL) {	
		NodoListaIntDobleDato* nuevo = new NodoListaIntDobleDato;
		nuevo->dato1 = e;
		nuevo->dato2 = ocurrencias;
		nuevo->sig = s->principio;
		s->principio = nuevo;
		s->cantElementos += ocurrencias;
	}
}

void borrar(MultisetInt& s, int e) {
	if (ocurrencias(s, e) > 1) {
		remplazarOcurrencias(s, e, ocurrencias(s, e) - 1);
		s->cantElementos--;
	}
	else {
		if (borrarElemento(s->principio, e)) { 
			s->cantElementos--;
		}
	}
}

bool pertenece(MultisetInt s, int e) {
	NodoListaIntDobleDato* auxiliar = s->principio;
	while (auxiliar != NULL) {
		if (auxiliar->dato1 == e) {
			return true;
		}
		auxiliar = auxiliar->sig;
	}
	return false;
}

MultisetInt unionConjuntos(MultisetInt s1, MultisetInt s2) {
	MultisetInt nuevo = crearMultisetInt();
	NodoListaIntDobleDato* a1 = s1->principio;
	NodoListaIntDobleDato* a2 = s2->principio;

	while (a1 != NULL) {
		if (pertenece(s2, a1->dato1)) {
			int a = ocurrencias(s1, a1->dato1);
			int b = ocurrencias(s2, a1->dato1);
			agregar(nuevo, a1->dato1, maximo(a, b));
		}
		else {
			agregar(nuevo, a1->dato1, a1->dato2);
		}
		a1 = a1->sig;
	}

	while (a2 != NULL) {
		if (pertenece(s1, a2->dato1)) {
		}
		else {
			agregar(nuevo, a2->dato1, a2->dato2);
		}
		a2 = a2->sig;
	}
	return nuevo;
}

MultisetInt interseccionConjuntos(MultisetInt s1, MultisetInt s2) {
	MultisetInt nuevo = crearMultisetInt();
	NodoListaIntDobleDato* a1 = s1->principio;
	NodoListaIntDobleDato* a2 = s2->principio;
	while (a1 != NULL) {
		if (pertenece(s2, a1->dato1)) {
			agregar(nuevo, a1->dato1, minimo(ocurrencias(s1, a1->dato1), ocurrencias(s2, a1->dato1)));
		}
		a1 = a1->sig;
	}
	return nuevo;
}

MultisetInt diferenciaConjuntos(MultisetInt s1, MultisetInt s2) {
	NodoListaIntDobleDato* a1 = s1->principio;
	MultisetInt clonS1 = clon(s1);
	while (a1 != NULL) {
		if (pertenece(s2, a1->dato1)) {
			if (ocurrencias(s1, a1->dato1) == ocurrencias(s2, a1->dato1)) {
				borrarTotal(clonS1->principio, a1->dato1);
				clonS1->cantElementos -= ocurrencias(s2, a1->dato1);
			}
			else {
				borrar(clonS1, a1->dato1);
			}
		}
		a1 = a1->sig;
	}
	return clonS1;
}

bool contenidoEn(MultisetInt s1, MultisetInt s2) {
	NodoListaIntDobleDato* a1 = s1->principio;
	while (a1 != NULL) {
		if (pertenece(s2, a1->dato1) && (ocurrencias(s1, a1->dato1) <= ocurrencias(s2, a1->dato1))) {}
		else {
			return false;
		}
		a1 = a1->sig;
	}
	if (a1 == NULL) return true;
}

int elemento(MultisetInt s) {
	assert(!esVacio(s));
	return s->principio->dato1;
}

bool esVacio(MultisetInt s) {
	return s->cantElementos == 0;
}

unsigned int cantidadElementos(MultisetInt s) {
	return s->cantElementos;
}

void destruir(MultisetInt& s) {
	while (!esVacio(s)) {
		int elementoBorrar = elemento(s);
		borrar(s, elementoBorrar);
	}
	delete s;
	s = NULL;
}

MultisetInt clon(MultisetInt s) {
	MultisetInt clon = crearMultisetInt();
	NodoListaIntDobleDato* auxiliar = s->principio;
	while (auxiliar != NULL) {
		agregar(clon, auxiliar->dato1, auxiliar->dato2);
		auxiliar = auxiliar->sig;
	}
	return clon;
}

#endif