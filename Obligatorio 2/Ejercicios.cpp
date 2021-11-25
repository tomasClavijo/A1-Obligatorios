#include "Ejercicios.h"

void EnlistarAux(ListaOrdInt arbolEnlistado, NodoABInt* a) {
	if (a != NULL) {
		agregar(arbolEnlistado, a->dato);
		EnlistarAux(arbolEnlistado, a->der);
		EnlistarAux(arbolEnlistado, a->izq);
	}
}
ListaOrdInt Enlistar(NodoABInt* a)
{
	ListaOrdInt arbolEnlistado = crearListaOrdInt();
	EnlistarAux(arbolEnlistado, a);
	return arbolEnlistado;
}

ListaOrdInt UnionListaOrd(ListaOrdInt l1, ListaOrdInt l2)
{
	ListaOrdInt listaUnionOrd = crearListaOrdInt();
	if (esVacia(l1) && esVacia(l2)) {
		return listaUnionOrd;
	}
	else {
		ListaOrdInt clonLista1 = clon(l1);
		ListaOrdInt clonLista2 = clon(l2);
		while (!esVacia(clonLista2)) {
			agregar(listaUnionOrd, minimo(clonLista2));
			borrarMinimo(clonLista2);
		}
		while (!esVacia(clonLista1)) {
			agregar(listaUnionOrd, minimo(clonLista1));
			borrarMinimo(clonLista1);
		}
		delete clonLista1;
		delete clonLista2;
	}
	return listaUnionOrd;
}

/* FUNCION AUXILIAR*/
ListaOrdInt enlistarPila(PilaInt p1) {
	_cabezalListaOrdInt* ret = crearListaOrdInt();
	while (!esVacia(p1)) {
		agregar(ret, top(p1));
		pop(p1);
	}
	return ret;
}
/*FIN FUNCION AUXILIAR*/
bool EstaContenida(PilaInt p1, PilaInt p2)
{
	bool estaContenida = false;
	ListaOrdInt l1 = enlistarPila(p1);
	ListaOrdInt l2 = enlistarPila(p2);

	if (esVacia(l1) || esVacia(l2)) {
		return true;
	}
	else {
		while (!esVacia(l1) && !esVacia(l2)) {
			if (minimo(l1) == minimo(l2)) { // En caso de estar contenida, elimino en ambas.
				borrarMinimo(l1);
				borrarMinimo(l2);
				estaContenida = true;
			}
			else if (minimo(l1) > minimo(l2)) { // En este caso, l2 tiene mayor cantidad de repeticiones, o elementos que no se encuentran en p1.
				borrarMinimo(l2);
			}
			else {
				estaContenida = false; // Si minimo(l2) > minimo(l1), es que ese elemento de p1 no está contenido en p2
				return estaContenida;
			}
		}
	}
	return estaContenida;
}

ListaOrdInt ObtenerRepetidos(MultisetInt m) 
{
	MultisetInt clonMultiset = clon(m);
	ListaOrdInt listaRepetidos = crearListaOrdInt();
	ListaOrdInt listaElementos = crearListaOrdInt(); 
	while (!esVacio(clonMultiset)) { 
		int elementoMultiset = elemento(clonMultiset);
		agregar(listaElementos, elementoMultiset);
		borrar(clonMultiset, elementoMultiset);
	}
	while (!esVacia(listaElementos) && cantidadElementos(listaElementos) >= 2) {
		int elementoAnterior = minimo(listaElementos);
		borrarMinimo(listaElementos);
		int minimoElemento = minimo(listaElementos);
		if (elementoAnterior == minimoElemento && !existe(listaRepetidos, minimoElemento)) {
			agregar(listaRepetidos, minimoElemento);
		}
		borrarMinimo(listaElementos);
		elementoAnterior = minimoElemento;
	}
	return listaRepetidos;
}

MultisetInt Xor(MultisetInt m1, MultisetInt m2)
{
	MultisetInt unionCon = unionConjuntos(m1, m2);
	MultisetInt interseccionCon = interseccionConjuntos(m1, m2);
	MultisetInt diferencia = diferenciaConjuntos(unionCon, interseccionCon);
	return diferencia;
}

ColaPrioridadInt MenorPrioridad(ColaPrioridadInt c) {
	ColaPrioridadInt clonCola = clon(c);
	ColaPrioridadInt menorCola = crearColaPrioridadInt(cantidadElementos(clonCola));
	int dato = 0;
	int elementosCant = 0;
	int prioridad = 0;
	while (!esVacia(clonCola)) {
		elementosCant = cantidadElementos(clonCola);
		if (principioPrioridad(clonCola) < prioridad) {
			destruir(menorCola);
			menorCola = crearColaPrioridadInt(elementosCant);
		}
		dato = principio(clonCola);
		prioridad = principioPrioridad(clonCola);
		encolar(menorCola, dato, prioridad);
		desencolar(clonCola);
	}
	return menorCola;
}

