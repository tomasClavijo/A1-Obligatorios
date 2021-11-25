#include "EjerciciosComienzo.h"

int suma(int a, int b) {
    return a + b ;
}

void tablaDel(unsigned int tablaDel, unsigned int desde, unsigned int hasta) {
	int resultado = 0;

	for (int i = desde; i < hasta; i++) {
		resultado = i * tablaDel;
		cout << i << "*" << tablaDel << "=" << resultado << ";"; 
	}

	resultado = hasta * tablaDel;
	cout << hasta << "*" << tablaDel << "=" << resultado;

	// Podria hacer el for <= hasta, pero contemplando con un if(i==hasta) { } else { }
}

void simplificar(int n, int d) {
	assert(d != 0);

	int divisorAux = d;
	int numeradorAux = n;
	int resto = 0;
	int mcd = 0;

	do {
		resto = numeradorAux % divisorAux;

		if (resto != 0) {
			numeradorAux = divisorAux;
			divisorAux = resto;
		}
		else {
			mcd = divisorAux;
		}
	} while (resto != 0 && n != 0);

	if (n == 0) {
		cout << n << "/" << d;
	}
	else {
		cout << n/mcd << "/" << d/mcd;
	}
}

int ocurrencias123Repetidos(int* vector, int largo) {
	int conteoSucesiones = 0;
	int conteoIntermedio = 0;

	for (int i = 0; i < largo; i++) {
		if (vector[i] == 1) {
			conteoIntermedio = 1;
		}
		if (vector[i] == 2 && conteoIntermedio == 1 && (vector[i-1] <= vector[i])) { /* Agrego la última condición de "vector[i-1] <= vector[i]" para evitar casos como el siguiente: 1 3 2 3, donde
																					 de no estar dicha condición, arrastraría: "conteoIntermedio = 1", y entraría en el if, contando un caso que no es */
			conteoIntermedio = 2;
		}
		if (vector[i] == 3 && conteoIntermedio == 2) {
			conteoSucesiones++;
			conteoIntermedio = 0;
		}
	}
	return conteoSucesiones;
}

int maximoNumero(unsigned int n) {
	int numeroIngresado;
	int numeroMayor = INT_MIN;

	for (int i = 0; i < n; i++) {
		cin >> numeroIngresado;
		if (numeroIngresado > numeroMayor) {
			numeroMayor = numeroIngresado;
		}
	}
	return numeroMayor;
}

void ordenarVecInt(int *vec, int largoVec) {

	for (int i = 0; i < largoVec; i++) {
		for (int j = i + 1; j < largoVec; j++) {
			if (vec[i] > vec[j]) {
				int variableAuxiliar = vec[i];
				vec[i] = vec[j];
				vec[j] = variableAuxiliar;
			}
		}
	}
}

int largoString(char* str) {

	int contador = 0;
	int largoString = 0;

	while (str[contador] != '\0') {
		largoString++;
		contador++;
	}

	return largoString;
}
char* invertirCase(char* str) {
	
	int largoStr = largoString(str);

	char* nuevoString = new char[largoStr + 1];

	for (int j = 0; j < largoStr + 1; j++) {
		nuevoString[j] = str[j];
	}

	for (int i = 0; i < largoStr; i++) {
		if ((int)nuevoString[i] >= 'A' && (int)nuevoString[i] <= 'Z') {
			nuevoString[i] = (int)nuevoString[i] + 32;
		}
		else if ((int)nuevoString[i] >= 'a' && (int)nuevoString[i] <= 'z') {
			nuevoString[i] = (int)nuevoString[i] - 32;
		}
	}

	return nuevoString;
}

int islas(char** mapa, int col, int fil){ 
	// IMPLEMENTAR SOLUCION
    return 0;
}


bool esOcurrencia(char* punteroString, char* substr) {
	
	int largoStr = largoString(punteroString); // Utilizo la función largoString definida en el ejercicio "invertirCase"
	int largoSubStr = largoString(substr);
	bool ocurrencia = false;
	bool seTermina = false;


	for (int i = 0; i <= largoStr && (seTermina == false); i++) {
		for (int j = 0; j <= largoSubStr && (seTermina == false); j++) { 
			if (substr[j] == '\0') {
				ocurrencia = true;
				seTermina = true;
			}
			else if (punteroString[i+j] == '\0'){
				seTermina = true;
			}
			else if (substr[j] == punteroString[i+j]){
			}
			else {
				break;
			}
		}
	}

	return ocurrencia;

}
unsigned int ocurrenciasSubstring(char **vecStr, int largoVecStr, char *substr)
{
	int cantidadDeOcurrencias = 0;

	for (int i = 0; i < largoVecStr; i++) {
		if (esOcurrencia(vecStr[i], substr) == true) {
			cantidadDeOcurrencias++;
		}
	}
    return cantidadDeOcurrencias;
}

char* copiaStrings(char* string) {
	int largoStringCopia = largoString(string) + 1;
	char* stringNuevo = new char[largoStringCopia];
	for (int i = 0; i < largoStringCopia; i++) {
		stringNuevo[i] = string[i];
	}
	return stringNuevo;
}
bool compararStrings(char* v1, char* v2) {
	bool aux = false;
	bool esMayor = false;
	int largoStringUno = largoString(v1);
	int largoStringDos = largoString(v2);
	int contador = 0;
	if (largoStringUno < largoStringDos) {
		while (contador != largoStringUno) {
			if ((int)v1[contador] > (int)v2[contador]) {
				esMayor = true;
				contador = largoStringUno;
			}
			else if ((int)v1[contador] < (int)v2[contador]) {
				contador = largoStringUno;
			}
			else {
				contador++;
			}
		}
	}
	if (largoStringUno > largoStringDos) {
		while (contador != largoStringDos) {
			if ((int)v1[contador] > (int)v2[contador]) {
				esMayor = true;
				contador = largoStringDos;
			}
			else if ((int)v1[contador] < (int)v2[contador]) {
				contador = largoStringDos;
				aux = true;
			}
			else {
				contador++;
			}
		}
		if (contador == largoStringDos && esMayor == false && aux == false) {
			esMayor = true;
		}
	}
	if (largoStringUno == largoStringDos) {
		while (contador != largoStringUno) {
			if ((int)v1[contador] > (int)v2[contador]) {
				esMayor = true;
				contador = largoStringUno;
			}
			else if ((int)v1[contador] < (int)v2[contador]) {
				contador = largoStringUno;
			}
			else {
				contador++;
			}
		}
	}
	return esMayor;
}
char** ordenarVecStrings(char** vecStr, int largoVecStr)
{
	char** vectorStrings = new char* [largoVecStr];
	for (int r = 0; r < largoVecStr; r++) {
		char* nuevoString = copiaStrings(vecStr[r]);
		vectorStrings[r] = nuevoString;
	}
	char* variableAuxiliar;
	for (int i = 0; i < largoVecStr; i++) {
		for (int j = i + 1; j < largoVecStr; j++) {
			if (compararStrings(vectorStrings[i], vectorStrings[j]) == true) { 
				variableAuxiliar = vectorStrings[i];
				vectorStrings[i] = vectorStrings[j];
				vectorStrings[j] = variableAuxiliar;
			}
		}
	}
	return vectorStrings;
}


int* intercalarVector(int* v1, int* v2, int l1, int l2){
	int* vectorCargado = new int[l1 + l2];
	int contadorVUno = 0;
	int contadorVDos = 0;

	for (int i = 0; i < l1 + l2; i++) {
		if (l1 == 0 || contadorVUno >= l1) {
			vectorCargado[i] = v2[contadorVDos];
			contadorVDos++;
		}
		else if (l2 == 0 || contadorVDos >= l2) {
			vectorCargado[i] = v1[contadorVUno];
			contadorVUno++;
		}
		else if (v1[contadorVUno] <= v2[contadorVDos]) {
			vectorCargado[i] = v1[contadorVUno];
			contadorVUno++;
		}
		else if (v1[contadorVUno] > v2[contadorVDos]) {
			vectorCargado[i] = v2[contadorVDos];
			contadorVDos++;
		}
	}
	if ((l1 + l2) == 0) {
		vectorCargado = NULL;
	}

	return vectorCargado;
}

/* Otro planteo para resolver el ejercicio anterior era cargar el arreglo y pasarlo por ordenarVecInt, esto afectaría directamente el órden, razón por la cual no fue aplicado.
   Se le agregaría: if (vectorCargado != NULL) {
						ordenarVecInt(vectorCargado, l1 + l2);
					}
	y dentro del For se reemplazaría lo presente por:
														if (contadorVUno < l1) {
															vectorCargado[i] = v1[contadorVUno];
															contadorVUno++;
														}
														else if (contadorVDos < l2) {
															vectorCargado[i] = v2[contadorVDos];
															contadorVDos++;
														}
*/

bool subconjuntoVector(int* v1, int* v2, int l1, int l2)
{
	bool esSubconjunto = false;
	bool elementoEncontrado = false;
	int encontrados = 0;

	if (l1 == 0) {
		esSubconjunto = true;  
	}
	else {
		for (int i = 0; i < l1; i++) { 
 			for (int j = 0; j < l2; j++) { 
				if (v1[i] == v2[j]) { 
					encontrados++; 
					break;
				}
			}
		}
		if (encontrados == l1) { 
			esSubconjunto = true;
		}
	}

	return esSubconjunto;
}

char** splitStr(char* str, char separador, int &largoRet) 
{
	// IMPLEMENTAR SOLUCION
	return NULL;
}

void ordenarVecIntMergeSort(int* vector, int largo) 
{
	// IMPLEMENTAR SOLUCION
}
