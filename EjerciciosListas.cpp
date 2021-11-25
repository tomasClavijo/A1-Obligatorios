#include "EjerciciosListas.h"

NodoLista* listaVacia() 
{
	return NULL;
}
bool esVacia(NodoLista* l) 
{
	return l == listaVacia();
}
void insertoPrimero(NodoLista*& l, int d) // C++
{
	NodoLista* nuevo = new NodoLista();
	assert(nuevo);
	nuevo->dato = d;
	nuevo->sig = l;
	l = nuevo;
}
NodoLista* invertirParcial(NodoLista* l) 
{
	assert(!esVacia(l));
	NodoLista* ret = listaVacia();
	while (!esVacia(l->sig))
	{
		insertoPrimero(ret, l->dato);
		l = l->sig;
	}

	return ret;
}

void eliminarNesimoDesdeElFinal(NodoLista*& lista, int &n) 
{
	if (lista == NULL || n < 1) {
		return;
	}
	else {
		eliminarNesimoDesdeElFinal(lista->sig, n);
		n--;
		if (0 == n) {
			NodoLista* auxBorrar = lista;
			lista = lista->sig;
			delete auxBorrar;
		}
	}
}

/*
insOrd :: A x ALista -> ALista
insOrd (e, []) = e.[]
insOrd (e,x.S) = si e<=x: e.x.S
insOrd (e, x.S) = si e>x: x.insOrd(e,S)
*/
void insertarOrdenado(NodoLista*& l, int dato) {
	if (l == NULL) {
		NodoLista* nuevoNodo = new NodoLista;
		assert(nuevoNodo);
		nuevoNodo->dato = dato;
		nuevoNodo->sig = NULL;
		l = nuevoNodo;
	}
	else {
		if (dato <= l->dato) {
			NodoLista* nuevoNodo = new NodoLista;
			assert(nuevoNodo);
			nuevoNodo->dato = dato;
			nuevoNodo->sig = l;
			l = nuevoNodo;
		}
		else {
			insertarOrdenado(l->sig, dato);
		}
	}
}
/*
Ord :: ALista -> ALista
Ord ([]) = []
Ord (x.S) = insOrd(x, Ord(S))
*/
NodoLista* listaOrdenadaInsertionSort(NodoLista* l) 
{
	if (l == NULL) {
		return NULL;
	} 
	else {
		NodoLista* listaOrdenada = listaOrdenadaInsertionSort(l->sig);
		insertarOrdenado(listaOrdenada, l->dato);
		return listaOrdenada;
	}
	return NULL;
}
/*PLANTEO SIN RECURSION.

NodoLista* listaOrdenadaInsertionSort(NodoLista* l)
{
	NodoLista* listaRetorno == NULL;
	while (l != NULL){
		insertarOrdenado(listaRetorno, l-> dato);
		l = l->sig;
	}
	return listaRetorno

*/
/*
Min :: ALista -> A
Min ([]) = error("La lista es vacía")
Min (x.[]) = x
Min (x.S) = si x<=Min(S) : x
Min (x.S) = si x>Min(S) : Min(S)
*/

/* PLANTEO CON RECURSIÓN
* 
int minimo(NodoLista* lista) {
	if (lista != NULL) {
		if (lista->sig == NULL) {
			return lista->dato;
		}
		else {
			if (lista->dato <= minimo(lista->sig)) {
				return lista->dato;
			}
			else {
				return minimo(lista->sig);
			}
		}
	}
}
*/
int minimo(NodoLista* lista) {
	int minimo = lista->dato;
	while (lista != NULL) {
		if (lista->dato < minimo) {
			minimo = lista->dato;
		}
		lista = lista->sig;
	}
	return minimo;
}
/*
elim :: A x ALista -> ALista
elim (e, []) = []
elim (e, x.S) = si e==x: S
elim (e, x.S) = si e!=x: x.elim(x,S)
*/
void elim(NodoLista*& lista, int dato) {
	if (lista != NULL) {
		if (lista->dato == dato) {
			NodoLista* aBorrar = lista; // Funcion para borrar principio de una lista. 
			lista = lista->sig;
			delete aBorrar;
		}
		else {
			elim(lista->sig, dato);
		}
	}
}

void agregarPrincipio(NodoLista*& lista, int dato) {
	NodoLista* nuevo = new NodoLista;
	nuevo->dato = dato;
	nuevo->sig = lista;
	lista = nuevo;
}

/*
Ord2 :: ALista -> ALista
Ord2 ([]) = []
Ord2 (x.S) = Min(x.S).Ord2(elim(Min(x.S), x.S)
*/

void listaOrdenadaSelectionSort(NodoLista*& l)
{
	if (l == NULL) {
		return;
	}
	else {
		int minimoElemento = minimo(l);
		elim(l, minimoElemento);
		listaOrdenadaSelectionSort(l);
		agregarPrincipio(l, minimoElemento);
	}
}

void agregarFin(NodoLista* &lista, NodoLista* &finLista, int dato) {
	NodoLista* nodo = new NodoLista;
	nodo->dato = dato;
	nodo->sig = NULL;
	if (lista == NULL) {
		lista = nodo;
		finLista = nodo;
	}
	else {
		finLista->sig = nodo;
		finLista = nodo;
	}
}
/*
copiar:: NLista -> NLista
copiar ([]) = []
copiar (x.S) = x'.copiar(S)
*/
NodoLista* copiar(NodoLista* lista) {
	if (lista == NULL) {
		return NULL;
	}
	else {
		NodoLista* nuevo = new NodoLista;
		nuevo->dato = lista->dato;
		nuevo->sig = copiar(lista->sig);
		return nuevo;
	}
}
NodoLista* intercalarIter(NodoLista* l1, NodoLista* l2)
{
	/*EJERCICIO OBLIGATORIO
		PRE : Recibe dos listas simplemente encadenadas, ambas ordenadas en orden creciente
		POS : Retorna una nueva lista con todos los elementos de l1 y l2, incluyendo repetidos, ordenados en orden creciente.
		La lista retornada no puede compartir memoria con las listas recibidas, y estas no pueden ser modificadas.
		La funcion no debe recorrer l1 o l2 mas de una vez, y la lista resultado no debera recorrerse
		El ejercicio se deberá resolver de forma iterativa.

		Ejemplo
		Entrada : (((1, 3, 5, 7, 9, 9), (2, 2, 4, 6, 8))
			Salida: (1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 9)
			*/ 
	if (l1 == NULL && l2 == NULL) {
		return NULL;
	}
	else if (l1 == NULL) {
		NodoLista* listaRetorno = copiar(l2);
		return listaRetorno;
	}
	else if (l2 == NULL) {
		NodoLista* listaRetorno = copiar(l1);
		return listaRetorno;
	}
	else {
		NodoLista* listaRetorno = NULL;
		NodoLista* finLista = NULL;
		while (l1 != NULL && l2 != NULL) {
			if (l1->dato <= l2->dato) {
				agregarFin(listaRetorno, finLista, l1->dato);
				l1 = l1->sig;
			}
			else {
				agregarFin(listaRetorno, finLista, l2->dato);
				l2 = l2->sig;
			}
		}
		if (l1 == NULL) {
			while (l2 != NULL) {
				agregarFin(listaRetorno, finLista, l2->dato);
				l2 = l2->sig;
			}
		}
		else if (l2 == NULL) {
			while (l1 != NULL) {
				agregarFin(listaRetorno, finLista, l1->dato);
				l1 = l1->sig;
			}
		}
		return listaRetorno;
	}
}

NodoLista* intercalarRec(NodoLista* l1, NodoLista* l2)
{
	NodoLista* listaRetorno = NULL;
	NodoLista* finLista = NULL;

	if (l1 == NULL && l2 == NULL) {
		return NULL;
	}
	else if (l1 == NULL) {
		NodoLista* listaRetorno = copiar(l2);
		return listaRetorno;
	}
	else if (l2 == NULL) {
		NodoLista* listaRetorno = copiar(l1);
		return listaRetorno;
	}
	else {
		if (l1->dato <= l2->dato) {
			agregarFin(listaRetorno, finLista, l1->dato);
			l1 = l1->sig;
			listaRetorno -> sig = intercalarRec(l1, l2);
		}
		else {
			agregarFin(listaRetorno, finLista, l2->dato);
			l2 = l2->sig;
			listaRetorno->sig = intercalarRec(l1, l2);
		}
		return listaRetorno;
	}
}

NodoLista* insComFin(NodoLista* l, int x)
{
	NodoLista* listaRetorno = NULL;
	agregarPrincipio(listaRetorno, x);
	while (l != NULL) {
		agregarPrincipio(listaRetorno, l->dato);
		l = l->sig;
	}
	agregarPrincipio(listaRetorno, x);

	return listaRetorno;
}

NodoLista* exor(NodoLista* l1, NodoLista* l2)
{
	NodoLista* listaRetorno = NULL;
	NodoLista* finLista = NULL;
	int l1AnteriorAux = INT_MIN;
	int l2AnteriorAux = INT_MIN;

	if (l1 == NULL && l2 == NULL) {
		return NULL;
	}
	else {
		while (l1 != NULL && l2 != NULL) {
			if (l1->dato < l2->dato) {
				if (l1->dato != l1AnteriorAux) {
					agregarFin(listaRetorno, finLista, l1->dato);
					l1AnteriorAux = l1->dato;
					l1 = l1->sig;
				}
				else {
					l1 = l1->sig;
				}
			}
			else if (l1->dato > l2->dato) {
				if (l2->dato != l2AnteriorAux) {
					agregarFin(listaRetorno, finLista, l2->dato);
					l2AnteriorAux = l2->dato;
					l2 = l2->sig;
				}
				else {
					l2 = l2->sig;
				}
			}
			else {
				l1AnteriorAux = l1->dato;
				l1 = l1->sig;
				l2AnteriorAux = l2->dato;
				l2 = l2->sig;
			}
		}
		if (l1 == NULL) {
			while (l2 != NULL) {
				if (l2->dato != l2AnteriorAux) {
					agregarFin(listaRetorno, finLista, l2->dato);
					l2AnteriorAux = l2->dato;
				}
				l2 = l2->sig;
			}
		}
		if (l2 == NULL) {
			while (l1 != NULL) {
				if (l1->dato != l1AnteriorAux) {
					agregarFin(listaRetorno, finLista, l1->dato);
					l1AnteriorAux = l1->dato;
				}
				l1 = l1->sig;
			}
		}
		return listaRetorno;
	}
}
	
void borrarDuplicados(NodoLista*& l, int datoBorrar) {
	while (l != NULL && l->dato == datoBorrar) {
		NodoLista* auxiliar = l;
		l = l->sig;
		delete auxiliar;
	}
}

void eliminarDuplicadosListaOrdenadaDos(NodoLista*& l) 
{
	if (l != NULL) {
		if (l->sig != NULL) {
			if (l->dato == l->sig->dato) {
				borrarDuplicados(l, l->dato);
				eliminarDuplicadosListaOrdenadaDos(l);
			}
			else {
				eliminarDuplicadosListaOrdenadaDos(l->sig);
			}
		}
	}
}

bool palindromo(NodoLista* l)
{
	// IMPLEMENTAR SOLUCION
	return false;
}

void eliminarNodo(NodoLista*& l, int posicion) {

	if (l != NULL) {
		NodoLista* auxiliar = l;
		NodoLista* anterior = NULL;

		for (int i = 1; (auxiliar != NULL) && (posicion != i); i++) {
			anterior = auxiliar;
			auxiliar = auxiliar->sig;
		}

		if (auxiliar != NULL) {
			if (anterior == NULL) {
				l = l->sig;
				delete auxiliar;
			}
			else {
				anterior->sig = auxiliar->sig;
				delete auxiliar;
			}
		}
	}
}

void eliminarSecuencia(NodoLista*& l, NodoLista* secuencia) {

	NodoLista* auxL = l;
	NodoLista* auxSecuencia = secuencia;

	int contador = 1;
	int principioSecuencia = 0;
	int finalSecuencia = 0;
	bool existeSecuencia = false;

	if (secuencia != NULL && l != NULL) {
		while (auxL != NULL && auxSecuencia != NULL) {
			if (auxL->dato == auxSecuencia->dato) {
				if (!existeSecuencia) {
					principioSecuencia = contador;
					existeSecuencia = true;
					auxSecuencia = auxSecuencia->sig;
				}
				else if (auxSecuencia->sig == NULL && existeSecuencia) {
					auxSecuencia = auxSecuencia->sig;
					finalSecuencia = contador;
				}
				else if (existeSecuencia) {
					auxSecuencia = auxSecuencia->sig;
				}
			}
			else {
				principioSecuencia = 0;
				auxSecuencia = secuencia;
				existeSecuencia = false;
			}
			contador++;
			auxL = auxL->sig;
			}
		}
	for (int i = principioSecuencia; i <= finalSecuencia; i++) {
		eliminarNodo(l, principioSecuencia);
	}
}

void moverNodo(NodoLista* &lista, unsigned int inicial, unsigned int final)
{
	// IMPLEMENTAR SOLUCION
}
