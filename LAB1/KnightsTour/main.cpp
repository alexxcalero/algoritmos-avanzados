/*
 * Proyecto : KnightsTour
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 5 de setiembre de 2024, 22:00
 */

#include <iostream>
#include <iomanip>
#define MAX_MOV 8
#define N 100
using namespace std;

int mov[MAX_MOV][2] = {
	{2,1},
	{1,2},
	{-1,2},
	{-2,1},
	{-2,-1},
	{-1,-2},
	{1,-2},
	{2,-1}
};

void inicializarTablero(int tablero[N][N], int n) {
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			tablero[i][j] = 0;
}

void imprimirTablero(int tablero[N][N], int n) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++)
			cout << setw(5) << tablero[i][j];
		cout << endl;
	}
}

bool validarPosicion(int tablero[N][N], int x, int y, int n) {
	if(x < n && y < n && x >= 0 && y >= 0 && tablero[x][y] == 0)
		return true;
	return false;
}

bool tour(int tablero[N][N], int n, int x, int y, int cantMov) {
	if(cantMov == n * n + 1)
		return true;

	for(int i = 0; i < MAX_MOV; i++) {
		int nx = x + mov[i][0];
		int ny = y + mov[i][1];
		if(validarPosicion(tablero, nx, ny, n)) {
			tablero[nx][ny] = cantMov;
			if(tour(tablero, n, nx, ny, cantMov + 1))
				return true;
			tablero[nx][ny] = 0;
		}
	}

	return false;
}

int main(int argc, char** argv) {
	int n, x, y;
	n = 5;
	x = y = 0;

	int tablero[N][N];
	inicializarTablero(tablero, n);
	tablero[x][y] = 1;

	if(tour(tablero, n, x, y, 2)) {
		cout << "Ruta del caballo para pasar por todo el tablero:\n";
		imprimirTablero(tablero, n);
	} else {
		cout << "El caballo no pudo pasar por todo el tablero\n";
	}

	return 0;
}
