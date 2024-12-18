/*
 * Proyecto : EX1-2024_2-P2
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 15 de octubre de 2024, 12:19
 */

#include <iostream>
using namespace std;

char *cadena;  // Variable global donde ire agregando los parentesis
int longCad;  // Longitud de la cadena
int indCad = 0;  // Indice de la cadena

bool imprimirParentesis(int n, int cantAbre, int cantCierra) {
	// Complete la cadena, indCad == longCad
	if(indCad == longCad) {
		// Verifico que haya un balance entre parentesis de apertura y de cierre
		if(cantAbre == cantCierra) {
			for(int i = 0; i < indCad; i++)
				cout << cadena[i];
			cout << endl;
		}
		//return true;
	}

	// Si es que los parentes de apertura son menores que n
	if(cantAbre < n) {
		cadena[indCad] = '(';  // Agrego un parentesis de apertura
		indCad++;  // Aumento el indice de la cadena
		cantAbre++;  // Incremento la cantidad de parentesis de apertura
		if(imprimirParentesis(n, cantAbre, cantCierra))  // Mando a la recursion asumiendo que habra solucion
			return true;
		// Realizo el backtraking
		cantAbre--;  // Disminuyo la cantidad de parentesis de apertura
		indCad--;  // Disminuyo el indice de la cadena
	}

	// Si los parentesis de cierre son menores que los parentesis de apertura
	if(cantCierra < cantAbre) {
		cadena[indCad] = ')';  // Agrego un parentesis de cierre
		indCad++;  // Aumento el indice de la cadena
		cantCierra++;  // Incremento la cantidad de parentesis de cierre
		if(imprimirParentesis(n, cantAbre, cantCierra))  // Mando a la recursion asumiendo que habra solucion
			return true;
		// Realizo el backtraking
		cantCierra--;  // // Disminuyo la cantidad de parentesis de cierre
		indCad--;  // Disminuyo el indice de la cadena
	}

	return false;
}

int main(int argc, char** argv) {
	int n = 4;
	longCad = 2 * n;  // Asigno la longitud de la cadena
	cadena = new char[longCad];  // Doy espacio en memoria a la cadena
	imprimirParentesis(n, 0, 0);
	return 0;
}
