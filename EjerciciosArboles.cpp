#include "EjerciciosArboles.h"


int max(int a, int b) {
	if (a >= b) {
		return a;
	}
	else {
		return b;
	}
}

int altura(NodoAB* raiz){
	int alturaArbol = 0;
	if (raiz == NULL) {
		return 0;
	}
	else {
		alturaArbol = 1 + max(altura(raiz->izq), altura(raiz->der));
		return alturaArbol;
	}
}

bool sonIguales(NodoAB* p, NodoAB* q) {
	if (p == NULL && q == NULL) {
		return true;
	}
	else if ((p != NULL && q == NULL) || (p == NULL && q != NULL)) {
		return false;
	}
	else {
		if (p->dato == q->dato) {
			return (sonIguales(p->izq, q->izq) && sonIguales(p->der, q->der));
		}
		else {
			return false;
		}
	}
}

bool existeCaminoConSuma(NodoAB* raiz, int sum) {\
	if (raiz == NULL) {
		return (0 == sum);
	}
	else if (raiz->izq == NULL && raiz->der != NULL) {
		sum = sum - raiz->dato;
		return existeCaminoConSuma(raiz->der, sum);
	}
	else if (raiz->izq != NULL && raiz->der == NULL) {
		sum = sum - raiz->dato;
		return existeCaminoConSuma(raiz->izq, sum);
	}
	else if (raiz->izq == NULL && raiz->der == NULL) {
		return (raiz->dato == sum);
	}
	else {
		sum = sum - raiz->dato;
		return (existeCaminoConSuma(raiz->der, sum) || existeCaminoConSuma(raiz->izq, sum));
	}
}

bool esArbolBalanceado(NodoAB *raiz) {
	if (raiz == NULL) {
		return true;
	}
	else {
		if ((abs((altura (raiz->izq)) - (altura(raiz->der)))) <=1) {
			return (esArbolBalanceado(raiz->izq) && esArbolBalanceado(raiz->der));
		}
		else {
			return false;
		}
	}
}

NodoLista* copiarLista(NodoLista* lista) {
	if (lista == NULL) {
		return NULL;
	}
	else {
		NodoLista* nuevo = new NodoLista;
		nuevo->dato = lista->dato;
		nuevo->sig = copiarLista(lista->sig);
		return nuevo;
	}
}
NodoLista* concatenar(NodoLista* l1, NodoLista* l2) {
	if (l1 == NULL) {
		return copiarLista(l2);
	}
	else if (l1 != NULL && l2 == NULL) {
		return copiarLista(l1);
	}
	else {
		NodoLista* nodo = new NodoLista;
		nodo->dato = l1->dato;
		nodo->sig = concatenar(l1->sig, l2);
		return nodo;
	}
}
NodoLista* enNivel(NodoAB *a, int k) {

	if (a == NULL) {
		return NULL;
	}
	else if (k == 1) {
		NodoLista* listaRetorno = new NodoLista();
		listaRetorno->dato = a->dato;
		listaRetorno->sig = NULL;
		return listaRetorno;
	}
	else {
		k--;
		return concatenar(enNivel(a->izq, k), enNivel(a->der, k));
	}
}

void auxiliarCantNodosEntreNiveles(NodoAB* a, int actualNivel, int*& vectorContador) {
	if (a != NULL) {
		vectorContador[actualNivel]++;
		auxiliarCantNodosEntreNiveles(a->der, actualNivel + 1, vectorContador);
		auxiliarCantNodosEntreNiveles(a->izq, actualNivel + 1, vectorContador);
	}
}
int cantNodosEntreNiveles(NodoAB* a, int desde, int hasta) {
	int alturaArbol = altura(a);
	int* vectorContador = new int[alturaArbol + 1];
	for (int i = 0; i <= alturaArbol; i++) {
		vectorContador[i] = 0;
	}
	auxiliarCantNodosEntreNiveles(a, 1, vectorContador);
	int cantidadNodos = 0;
	for (int i = 0; i <= alturaArbol; i++) {
		if (i <= hasta && i >= desde) {
			cantidadNodos = cantidadNodos + vectorContador[i];
		}
	}
	return cantidadNodos;
}

NodoLista* camino(NodoAB *arbol, int x) {
	if (arbol == NULL) {
		return NULL;
	}
	else if (arbol->dato == x) {
			NodoLista* listaRetorno = new NodoLista();
			listaRetorno->dato = arbol->dato;
			listaRetorno->sig = NULL;
			return listaRetorno;
	}
	else if (arbol->dato > x) {
		NodoLista* listaRetorno = new NodoLista();
		listaRetorno->dato = arbol->dato;
		listaRetorno->sig = NULL;
		return concatenar(listaRetorno, camino(arbol->izq, x));
	}
	else if (arbol->dato < x) {
		NodoLista* listaRetorno = new NodoLista();
		listaRetorno->dato = arbol->dato;
		listaRetorno->sig = NULL;
		return concatenar(listaRetorno, camino(arbol->der, x));
	}
}

NodoAB* invertirHastak(NodoAB* a, int k){
	if (k == 0) {
		return NULL;
	}
	if (a != NULL && k>0) {
		NodoAB* aEspejo = new NodoAB;
		aEspejo->dato = a->dato;
		aEspejo->izq = invertirHastak(a->der, k-1);
		aEspejo->der = invertirHastak(a->izq, k-1);
		return aEspejo;

	}
	return NULL;
}

NodoAB* minimo(NodoAB* a) {
	if (a == NULL) return NULL;
	while (a->izq != NULL) {
		a = a->izq;
	}
	return a;
}
void elimABB(NodoAB*& A, int dato) {
	if (A != NULL) {
		if (dato < A->dato) {
			elimABB(A->izq, dato);
		}
		else if (dato > A->dato) {
			elimABB(A->der, dato);
		}
		else {
			if (A->der == NULL && A->izq == NULL) {
				delete A;
				A = NULL;
			}
			else if (A->der != NULL && A->izq == NULL) {
				NodoAB* aBorrar = A;
				A = A->der;
				delete aBorrar;
			}
			else if (A->der == NULL && A->izq != NULL) {
				NodoAB* aBorrar = A;
				A = A->izq;
				delete aBorrar;
			}
			else {
				NodoAB* minimoDerecha = minimo(A->der);
				A->dato = minimoDerecha->dato;
				elimABB(A->der, minimoDerecha->dato); 
			}
		}
	}
}
void borrarNodoRaiz(NodoAB * & A) {
	elimABB(A, A->dato);
}

int cantNodos(NodoAB* a) {
	if (a == NULL) {
		return 0;
	}
	else {
		return 1 + cantNodos(a->izq) + cantNodos(a->der);
	}
}
void aplanarArbol(NodoAB* A, int*& vectorValores, int & posicion) {
	if (A != NULL) {
		vectorValores[posicion] = A->dato;
		posicion++;
		aplanarArbol(A->izq, vectorValores, posicion);
		aplanarArbol(A->der, vectorValores, posicion);
	}
}
bool sumaABB(NodoAB* a, int n)
{
	if (a == NULL) {
		return false;
	}
	else {
		int cantidadNodos = cantNodos(a);
		if (cantidadNodos == 1) {
			return false;
		}
		int* vectorValores = new int[cantidadNodos + 1];
		for (int i = 0; i < cantidadNodos + 1; i++) {
			vectorValores[i] = 0;
		}
		int posicion = 1;
		aplanarArbol(a, vectorValores, posicion);
		for (int i = 1; i < cantidadNodos + 1; i++) {
			for (int j = 1; j < cantidadNodos + 1; j++) {
				if (j != i) {
					int numeroUno = vectorValores[i];
					int numeroDos = vectorValores[j];
					if (vectorValores[i] + vectorValores[j] == n) {
						return true;
					}
				}
				
			}
		}
		return false;
	}
}

int maximoArbolBB(NodoAB* a) {
	if (a == NULL) {
		return 0;
	}
	else if (a->der == NULL) {
		return a->dato;
	}
	else {
		maximoArbolBB(a->der);
	}
}
int sucesor(NodoAB* a, int n)
{
	if (a == NULL) {
		return -1;
	}
	else if (a->dato <= n) {
		sucesor(a->der, n);
	}
	else if (a->dato > n) {
		if (maximoArbolBB(a->izq) <= n) {
			return a->dato;
		}
		else {
			sucesor(a->izq, n);
		}
	}
}

void auxiliarNivelMasNodos(NodoAB* raiz, int nivelHasta, int* vector) {
	if (raiz != NULL) {
		vector[nivelHasta]++;
		auxiliarNivelMasNodos(raiz->izq, nivelHasta + 1, vector);
		auxiliarNivelMasNodos(raiz->der, nivelHasta + 1, vector);
	}
}
int nivelMasNodos(NodoAB* raiz, int nivelHasta) {
	int alturaArbol = altura(raiz);
	int* vector = new int[alturaArbol + 1];
	for (int i = 0; i <= alturaArbol + 1; i++) {
		vector[i] = 0;
	}
	auxiliarNivelMasNodos(raiz, 1, vector);
	int maximo = 0;
	for (int i = 0; i <= nivelHasta; i++) {
		if (vector[i] > vector[maximo]) {
			maximo = i;
		}
	}
	return maximo;
}

void borrarPares(NodoAB* & a){
	if (a != NULL) {
		if (a->dato % 2 == 0) {
			NodoAB* aBorrar = a;
			a = minimo(a->der);
			delete aBorrar;
			borrarPares(a);
		}
		else {
			borrarPares(a->izq);
			borrarPares(a->der);
		}
	}
}

int alturaAG(NodoAG* raiz)
{
	if (raiz == NULL) {
		return 0;
	}
	else {
		return max(1 + alturaAG(raiz->ph), alturaAG(raiz->sh));
	}
}

int sumaPorNivelesAux(NodoAG* raiz, int contador, int resultado) {
	if (contador % 2 == 0) {
		resultado = resultado + raiz->dato;
	}
	else if (contador % 2 == 1) {
		resultado = resultado - raiz->dato;
	}

	if (raiz->sh != NULL) {
		resultado = sumaPorNivelesAux(raiz->sh, contador, resultado);
	}
	if (raiz->ph != NULL) {
		contador++;
		resultado = sumaPorNivelesAux(raiz->ph, contador, resultado);
	}
	else {
		return resultado;
	}
}
int sumaPorNiveles(NodoAG* raiz){
	int resultado = 0;
	int contador = 1;

	if (raiz == NULL) {
		return 0;
	}
	else {
		resultado = sumaPorNivelesAux(raiz, contador, resultado);
	}
	return resultado;
}

bool esPrefijo(NodoAG *a, NodoLista *l)
{
	if (a == NULL && l != NULL) {
		return false;
	}
	else if (l == NULL) {
		return true;
	}
	else if (a-> dato == l->dato){
		esPrefijo(a->ph, l->sig);
	}
	else {
		esPrefijo(a->sh, l);
	}
}

NodoLista* caminoAG(NodoAG *arbolGeneral, int dato) {
	NodoLista* retorno = new NodoLista();
	if (arbolGeneral == NULL) {
		return NULL;
	}
	else if (arbolGeneral->dato == dato) {
			retorno->dato = dato;
			retorno->sig = NULL;
			return retorno;
	}
	else {
		NodoLista* p = caminoAG(arbolGeneral->ph, dato);
		if (p != NULL) {
			NodoLista* retornoAux = new NodoLista();
			retornoAux->dato = arbolGeneral->dato;
			retornoAux->sig = p;
			return retornoAux;
		}
		else {
			return caminoAG(arbolGeneral->sh, dato);
		}
	}					
}

void auxiliarNivelConMasNodosAG(NodoAG* arbolGeneral, int nivelActual, int* vectorContador) {
	if (arbolGeneral != NULL) {
		vectorContador[nivelActual]++;
		auxiliarNivelConMasNodosAG(arbolGeneral->sh, nivelActual, vectorContador);
		auxiliarNivelConMasNodosAG(arbolGeneral->ph, nivelActual + 1, vectorContador);
	}
}

int nivelConMasNodosAG(NodoAG * arbolGeneral) { // Aplico misma idea que en ABB
	int alturaArbolAG = alturaAG(arbolGeneral);
	int maximo = 0;
	int* vectorContador = new int(alturaArbolAG + 1);
	for (int i = 0; i <= alturaArbolAG + 1; i++) {
		vectorContador[i] = 0;
	}
	auxiliarNivelConMasNodosAG(arbolGeneral, 1, vectorContador);
	for (int i = 0; i <= alturaArbolAG; i++) {
		if (vectorContador[i] > vectorContador[maximo]) {
			maximo = i;
		}
	}
	return maximo;
}
