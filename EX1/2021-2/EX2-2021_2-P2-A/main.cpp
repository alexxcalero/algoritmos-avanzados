/*
 * Proyecto : EX2-2021_2-P2-A
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 15 de octubre de 2024, 00:40
 */

#include <iostream>
#include <algorithm>
#define N 4
#define M 4
using namespace std;

void calcularDistancias(int almacen[N][M], int n, int m) {
	int solucion[N][M];
	solucion[0][0] = 0;

	// Inicializo la primera fila
	for(int i = 1; i < m; i++)
		solucion[0][i] = abs(almacen[0][i - 1] - almacen[0][i]) + solucion[0][i - 1];
	// Inicializo la primera columna
	for(int j = 1; j < n; j++)
		solucion[j][0] = abs(almacen[j - 1][0] - almacen[j][0]) + solucion[j - 1][0];

	// Analizo el resto del almacen
	for(int i = 1; i < n; i++) {
		for(int j = 1; j < m; j++) {
			int deArriba = abs(almacen[i][j - 1] - almacen[i][j]) + solucion[i][j - 1];
			int deIzq = abs(almacen[i - 1][j] - almacen[i][j]) + solucion[i - 1][j];
			int deDiag = abs(almacen[i - 1][j - 1] - almacen[i][j]) + solucion[i - 1][j - 1];
			solucion[i][j] = min(deArriba, min(deIzq, deDiag));
		}
	}

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			cout << solucion[i][j] << " ";
		}
		cout << endl;
	}

	cout << "La distancia total recorrida minima es de " << solucion[n - 1][m - 1] << " metros\n";
}

int main(int argc, char** argv) {
	int almacen[N][M] = {
		{4, 2, 2, 4},
		{1, 4, 6, 8},
		{2, 5, 9, 1},
		{1, 3, 11, 12}
	};
	int n = N, m = M;
	calcularDistancias(almacen, n, m);
	return 0;
}
