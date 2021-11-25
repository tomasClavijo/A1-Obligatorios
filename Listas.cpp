#include "Main.h"

void main() {
	nodoLista* l = NULL;
	insertarOrdenado(l, 40);
	insertarOrdenado(l, 2);
	insertarOrdenado(l, 70);
	insertarOrdenado(l, -235);
	imprimir(l);

	cout << endl;
	nodoLista* copiaL = copiar(l);
	imprimir(copiaL);
	system("pause");
}

bool esVacia(nodoLista* lista) {
	return lista == NULL;
}

void agregarFin(nodoLista* &lista, int dato) {
	if (lista != NULL) {
		nodoLista* auxLista = lista;
		while (auxLista->sig != NULL) {
			auxLista = auxLista->sig;
		}
		nodoLista * nodo = new nodoLista;
		nodo->dato = dato;
		nodo->sig = NULL;
		auxLista->sig = nodo;
	}
	else {
		nodoLista* nodo = new nodoLista;
		nodo->dato = dato;
		nodo->sig = NULL;
		lista = nodo;
	}
}

void agregarFinRec(nodoLista* &lista, int dato) {
	if (lista == NULL) {
		nodoLista* nodo = new nodoLista;
		nodo->dato = dato;
		nodo->sig = NULL;
		lista = nodo;
	}
	else {
		agregarFinRec(lista->sig, dato);
	}
}

void agregarPrincipio(nodoLista* &lista, int dato) {
	nodoLista* nuevo = new nodoLista;
	nuevo->dato = dato;
	nuevo->sig = lista;
	lista = nuevo;
}

void borrarPrimero(nodoLista* &lista) {
	if (lista != NULL) {
		nodoLista* auxBorrar = lista;
		lista = lista->sig;
		delete auxBorrar;
	}
}

void borrarFin(nodoLista* &lista) {
	if (lista != NULL) {
		if (lista->sig == NULL) {
			delete lista;
			lista = NULL;
		}
		else {
			nodoLista* penultimo = lista;
			while (penultimo->sig->sig != NULL) {
				penultimo = penultimo->sig;
			}
			delete penultimo->sig;
			penultimo->sig = NULL;
		}
	}
}

/*
borrarFin:: NLista -> NLista
borrarFin ([]) = []
borrarFin (x.[]) = []
borrarFin (x.S) = x.borrarFin(S)
*/
void borrarFinRec(nodoLista* &lista) {
	if (lista == NULL) {
		lista = NULL;
	}
	else if (lista->sig == NULL) {
		delete lista;
		lista = NULL;
	}
	else {
		borrarFinRec(lista->sig);
	}
}

void borrarTodo(nodoLista* &lista) {
	while (lista != NULL) {
		nodoLista* aBorrar = lista;
		lista = lista->sig;
		delete aBorrar;
	}
}

/*
borrarTodo:: NLista -> NLista
borrarTodo ([]) = []
borrarTodo (x.S) = borrarTodo(S)
*/
void borrarTodoRec(nodoLista* &lista) {
	if (lista == NULL) {
		return;
	}
	else {
		nodoLista* aux = lista->sig;
		delete lista;
		lista = NULL;
		borrarTodoRec(aux);
	}
}

/*
insertarOrdenado:: NLista -> N -> NLista
insertarOrdenado ([], n) = n.[]
insertarOrdenado (x.S, n) = si n <= x: n.(x.S)
insertarOrdenado (x.S, n) = si n > x: x.insertarOrdenado(S, n)
*/
// PRE: La lista esta ordenada
void insertarOrdenado(nodoLista* &lista, int dato) {
	if (lista == NULL) {
		/*
		nodoLista* nuevo = new nodoLista;
		nuevo->dato = dato;
		nuevo->sig = NULL;
		lista = nuevo;
		*/
		agregarPrincipio(lista, dato);
	}
	else {
		if (dato <= lista->dato) {
			/*
			nodoLista* nuevo = new nodoLista;
			nuevo->dato = dato;
			nuevo->sig = lista;
			lista = nuevo;
			*/
			agregarPrincipio(lista, dato);
		}
		else {
			insertarOrdenado(lista->sig, dato);
		}
	}
}

/*
copiar:: NLista -> NLista
copiar ([]) = []
copiar (x.S) = x'.copiar(S)
*/
nodoLista* copiar(nodoLista* lista) {
	if (lista == NULL) {
		return NULL;
	}
	else {
		nodoLista* nuevo = new nodoLista;
		nuevo->dato = lista->dato;
		nuevo->sig = copiar(lista->sig);
		return nuevo;
	}
}

void imprimir(nodoLista* lista) {
	if (lista != NULL) {
		cout << lista->dato << " ";
		imprimir(lista->sig);
	}
	else {
		return;
	}
}