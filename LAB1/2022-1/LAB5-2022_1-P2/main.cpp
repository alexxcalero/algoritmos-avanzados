/*
 * Proyecto : LAB5-2022_1-P2
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 7 de setiembre de 2024, 01:06
 */

#include <iostream>
#define N 9
#define M 5
using namespace std;

int cantSol = 0;

int movimientos[8][2] = {
	{1,0},
	{1,1},
	{0,1},
	{-1,1},
	{-1,0},
	{-1,-1},
	{0,-1},
	{-1,1}
};

void inicializarMatriz(char matriz[][M]) {
	for(int i = 0; i < N; i++)
		for(int j = 0; j < M; j++)
			matriz[i][j] = '0';
}

void colocarMinas(char tablero[][M]) {
	tablero[0][4] = '*';
	tablero[2][2] = '*';
	tablero[4][1] = '*';
	tablero[4][2] = '*';
	tablero[4][4] = '*';
	tablero[5][1] = '*';
	tablero[5][2] = '*';
	tablero[5][4] = '*';
	tablero[6][1] = '*';
	tablero[6][3] = '*';
	tablero[7][0] = '*';
	tablero[7][1] = '*';
	tablero[7][2] = '*';
	tablero[7][3] = '*';
}

void imprimirMatriz(char matriz[][M]) {
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++)
			cout << matriz[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

bool validarMovimiento(char solucion[][M], int x, int y) {
	if(x >= 0 && y >= 0 && x < N && y < M && solucion[x][y] == '0')
		return true;
	else
		return false;
}

void descubrirMinas(char tablero[][M], char solucion[][M], int x, int y) {
	for(int i = 0; i < 8; i++) {
		int nx = x + movimientos[i][0];
		int ny = y + movimientos[i][1];
		if(validarMovimiento(solucion, nx, ny))
			if(tablero[nx][ny] == '*')
				solucion[nx][ny] = '*';
	}
}

bool hallarCamino(char tablero[][M], char solucion[][M], int x, int y, char letra) {
	if(x == N - 1 && y == M - 1) {
		cantSol++;
		cout << "Solucion " << cantSol << ":\n";
		imprimirMatriz(solucion);
		if(cantSol == 20)  // Inciso B pide mostrar las 20 primeras soluciones
			return 1;
		return 0;
	}

	descubrirMinas(tablero, solucion, x, y);

	for(int i = 0; i < 8; i++) {
		int nx = x + movimientos[i][0];
		int ny = y + movimientos[i][1];
		if(validarMovimiento(solucion, nx, ny)) {
			solucion[nx][ny] = letra;
			if(hallarCamino(tablero, solucion, nx, ny, letra + 1))
				return true;
			solucion[nx][ny] = '0';
		}
	}

	return false;
}

int main(int argc, char** argv) {
	char tablero[N][M], solucion[N][M];

	inicializarMatriz(tablero);
	inicializarMatriz(solucion);
	colocarMinas(tablero);

	solucion[0][0] = 'A';

//	imprimirMatriz(tablero);
//	imprimirMatriz(solucion);

	hallarCamino(tablero, solucion, 0, 0, 'B');

	if(cantSol > 0)
		cout << "Se encontro un camino hasta el final\n";
	else
		cout << "No se pudo encontrar un camino hasta el final\n";
	
	return 0;
}
