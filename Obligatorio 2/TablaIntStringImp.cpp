#include "TablaIntString.h"

#ifdef TABLA_INT_STRING_IMP

struct nodoHash {
	int dominio;
	char* rango;
	nodoHash* sig;
};

struct _cabezalTablaIntString {
	nodoHash** tabla;	
	int numeroDeElementos;
	int elementosEsperados;		
};

/* FUNCIONES AUXILIARES*/

//PRE: -
//POS: Retorna el largo de la cadena string.
int largoString(const char* stringCadena) {
	int largoS = 0;
	int i = 0;
	while (stringCadena[i] != '\0') {
		largoS++;
		i++;
	}
	return largoS;
}

//PRE: - 
//POS: Realiza una copia del string.
char* copiarString(const char* string) {
	int largoS = largoString(string) + 1;
	char* stringCopia = new char[(largoS)];
	for (int i = 0; i < largoS; i++) {
		char auxiliar = string[i];
		stringCopia[i] = auxiliar;
	}
	return stringCopia;
}

/* FIN FUNCIONES AUXILIARES */

unsigned int funcionHashTabla(int d, unsigned int capacidad) {
	return d % capacidad; 
}

void factorOcupacionTabla(TablaIntString& t) {
	float factorCarga = (float)t->numeroDeElementos / (float)t->elementosEsperados;
	if (factorCarga >= 1) {
		TablaIntString nuevo = crearTablaIntString(t->elementosEsperados * 2); 
		for (int i = 0; i < t->elementosEsperados; i++) {
			if (t->tabla[i] != NULL) {
				nodoHash* auxiliar = t->tabla[i];
				while (auxiliar != NULL) {
					char* copiaChar = copiarString(auxiliar->rango);
					agregar(nuevo, auxiliar->dominio, copiaChar);
					auxiliar = auxiliar->sig;
				}
			}
		}
		destruir(t);
		t = nuevo;
	}
}

TablaIntString crearTablaIntString(unsigned int esperados) {
	TablaIntString nuevo = new _cabezalTablaIntString;
	nuevo->tabla = new nodoHash * [esperados];
	for (int i = 0; i < esperados; i++) {
		nuevo->tabla[i] = NULL;
	}
	nuevo->elementosEsperados = esperados;
	nuevo->numeroDeElementos = 0;
	return nuevo;
}

void agregar(TablaIntString& t, int d, const char* r) {
	int pos = funcionHashTabla(d, t->elementosEsperados);
	nodoHash* lista = t->tabla[pos];
	char* stringCopia = copiarString(r);	
	while (lista != NULL && lista->dominio != d) {	
		lista = lista->sig;
	}
	if (lista == NULL) {									
		nodoHash* nuevo = new nodoHash;
		nuevo->dominio = d;
		nuevo->rango = stringCopia;							
		nuevo->sig = t->tabla[pos];					
		t->tabla[pos] = nuevo;
		t->numeroDeElementos++;
	}
	else {													
		lista->rango = stringCopia;
	}
}

bool estaDefinida(TablaIntString t, int d) {
	int posicion = funcionHashTabla(d, t->elementosEsperados);
	nodoHash* lista = t->tabla[posicion];
	while (lista != NULL && lista->dominio != d) {
		lista = lista->sig;
	}
	if (lista != NULL) {
		return true;
	}
	else {
		return false;
	}
}

char* recuperar(TablaIntString t, int d) {
	assert(estaDefinida(t, d));
	int posicion = funcionHashTabla(d, t->elementosEsperados);
	nodoHash* l = t->tabla[posicion];
	while (l != NULL && l->dominio != d) {
		l = l->sig;
	}
	char* copiaString = copiarString(l->rango);
	return copiaString;
}

void borrar(TablaIntString& t, int d) {
	int posicion = funcionHashTabla(d, t->elementosEsperados);
	nodoHash*& l = t->tabla[posicion];
	while (l != NULL && l->dominio != d) {
		l = l->sig;
	}
	if (l != NULL) {
		t->numeroDeElementos--;
		nodoHash* borrar = l;
		l = l->sig;
		delete borrar;
	}
}

int elemento(TablaIntString t) {
	assert(!esVacia(t));
	for (int i = 0; i < t->elementosEsperados; i++) {
		if (t->tabla[i] != NULL) {
			return t->tabla[i]->dominio;
		}
	}
}

bool esVacia(TablaIntString t) {
	return t->numeroDeElementos == 0;
}

unsigned int cantidadElementos(TablaIntString t) {
	return t->numeroDeElementos;
}

void destruir(TablaIntString& t) {
	for (int i = 0; i < t->elementosEsperados; i++) {
		nodoHash* l = t->tabla[i];
		while (l != NULL) {
			nodoHash* borrar = l;
			delete l->rango;
			l = l->sig;
			delete borrar;
		}
	}
	delete t;
	t = NULL;
}

TablaIntString clon(TablaIntString t) {
	TablaIntString clon = crearTablaIntString(t->elementosEsperados);
	for (int posicion = 0; posicion < t->elementosEsperados; posicion++) {
		nodoHash* l = t->tabla[posicion];
		while (l != NULL) {
			agregar(clon, t->tabla[posicion]->dominio, t->tabla[posicion]->rango);
			l = l->sig;
		}
	}
	return clon;
}

#endif