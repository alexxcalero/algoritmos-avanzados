/*
 * Proyecto : EX2-2021_2-P2-B
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 15 de octubre de 2024, 01:14
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#define N 6
#define M 6
using namespace std;

void recolectarProductos(int almacen[N][M], int n, int m) {
	int solucion[N][M];
	solucion[0][0] = almacen[0][0];
	// Inicializo la primera fila
	for(int i = 1; i < m; i++)
		solucion[0][i] = almacen[0][i] + solucion[0][i - 1];
	// Inicializo la primera columna
	for(int i = 1; i < n; i++)
		solucion[i][0] = almacen[i][0] + solucion[i - 1][0];

	for(int i = 1; i < n; i++) {
		for(int j = 1; j < m; j++) {
			int deArriba = almacen[i][j] + solucion[i - 1][j];
			int deIzq = almacen[i][j] + solucion[i][j - 1];
			solucion[i][j] = max(deArriba, deIzq);
		}
	}

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			cout << setw(3) << solucion[i][j] << " ";
		}
		cout << endl;
	}

	cout << "La solucion de esta disposicion es de " << solucion[n - 1][m - 1] << " unidades\n";
}

int main(int argc, char** argv) {
	int almacen[N][M] = {
		{1, 2, 9, 1, 2, 3},
		{5, 1, 7, 1, 2, 1},
		{1, 7, 1, 3, 8, 1},
		{2, 2, 6, 1, 2, 2},
		{3, 6, 9, 5, 1, 5},
		{1, 1, 4, 1, 9, 1}
	};
	int n = 6, m = 6;
	recolectarProductos(almacen, n, m);
	return 0;
}
