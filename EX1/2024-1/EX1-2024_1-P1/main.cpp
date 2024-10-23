/*
 * Proyecto : EX1-2024_1-P1
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 13 de octubre de 2024, 12:46
 */

#include <iostream>
#include <climits>
#define N 5
#define CANT_MOV 4
using namespace std;

int costoParcial = 0;
int costoMinimo = INT_MAX;
int mejorSolucion[N][N];

int movimientos[CANT_MOV][2] {
	{-1,  0},
	{0 ,  1},
	{1 ,  0},
	{0 , -1}
};

void imprimirSolucion(int solucion[N][N]) {
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++)
			cout << solucion[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

bool validarMovimiento(int x, int y, int laberinto[N][N], int solucion[N][N]) {
	return x >= 0 && y >= 0 && x < N && y < N && solucion[x][y] == 0 && laberinto[x][y] != 0;
}

bool encontrarCamino(int laberinto[N][N], int solucion[N][N], int x, int y) {
	// Cuando estamos en la esquina inferior derecha
	if(x == N - 1 && y == N - 1) {
		solucion[x][y] = 1;  // Marco la ultima posicion en la matriz solucion
		costoParcial += laberinto[x][y];  // Incremento el costo

		if(costoParcial < costoMinimo) {
			costoMinimo = costoParcial;

			for(int i = 0; i < N; i++)
				for(int j = 0; j < N; j++)
					mejorSolucion[i][j] = solucion[i][j];  // Guardo la matriz de la mejor solucion
		}

		// Resto el costo ya que seguire probando opciones
		costoParcial -= laberinto[x][y];

		//imprimirSolucion(solucion);
		//return true;
	}

	// Recorro todos los posibles movimientos
	for(int i = 0; i < CANT_MOV; i++) {
		int nx = x + movimientos[i][0];
		int ny = y + movimientos[i][1];
		if(validarMovimiento(nx, ny, laberinto, solucion)) {
			solucion[nx][ny] = 1;  // Marco la posicion en la matriz solucion
			costoParcial += laberinto[nx][ny];  // Incremento el costo

			// Recursion asumiendo que va haber respuesta
			if(encontrarCamino(laberinto, solucion, nx, ny))
				return true;

			// Backtracking
			costoParcial -= laberinto[nx][ny];  // Resto el costo
			solucion[nx][ny] = 0;  // Desmarco de la matriz solucion
		}
	}

	return false;
}

int main(int argc, char** argv) {
	int laberinto[N][N] = {
		{1, 2, 0, 1, 0},
		{3, 2, 3, 1, 1},
		{0, 1, 2, 0, 0},
		{3, 1, 1, 2, 3},
		{0, 1, 3, 1, 1}
	};

	int solucion[N][N];
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			solucion[i][j] = 0;  // Incializo con 0 toda la matriz de solucion

	solucion[0][0] = 1;  // Empiezo en la esquina superior izquierda
	//costoParcial += solucion[0][0];
	encontrarCamino(laberinto, solucion, 0, 0);
	if(costoMinimo != INT_MAX) {
		imprimirSolucion(mejorSolucion);
		cout << "El menor costo es de " << costoMinimo << endl;
	}
	else
		cout << "No se pudo salir del laberinto\n";

	return 0;
}
