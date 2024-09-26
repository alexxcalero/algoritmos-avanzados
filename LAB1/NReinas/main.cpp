/*
 * Proyecto : NReinas
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 5 de setiembre de 2024, 22:37
 */

#include <iostream>
#define N 8  // Tamanho del tablero
using namespace std;

// Variable global para llevar la cantidad de soluciones encontradas
int cantSoluciones = 0;

// Inicializo el tablero con ceros
void generarTablero(int tablero[N][N]) {
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			tablero[i][j] = 0;
}

void mostrarSolucion(int tablero[N][N]) {
	cout << "Solucion " << cantSoluciones << ":\n";
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++)
			cout << tablero[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

bool validarPosicion(int tablero[N][N], int fila, int columna) {
	// Verifico hacia la izquierda en la misma fila
	for(int i = 0; i <= columna; i++)
		if(tablero[fila][i] == 1)
			return false;

	// Verifico hacia la diagonal superior izquierda
	for(int i = fila, j = columna; i >= 0 && j >= 0; i--, j--)
		if(tablero[i][j] == 1)
			return false;

	// Verifico hacia la diagonal inferior izquierda
	for(int i = fila, j = columna; i < N && j >= 0; i++, j--)
		if(tablero[i][j] == 1)
			return false;

	// Si paso todas las verificaciones, la posicion
	// donde voy a colocar a la reina es valida
	return true;
}

bool buscarSoluciones(int tablero[N][N], int columna) {
	// Cuando la columna sea igual a N (nos salimos de los limites del tablero)
	// significa que hemos encontrado una solucion y retornamos 1
	if(columna == N) {
		cantSoluciones++;
		mostrarSolucion(tablero);
		//return true;
		return false;  // Comentar esta linea, y descomentar la linea de arriba si quiero mostrar una sola solucion
	}

	for(int fila = 0; fila < N; fila++) {
		if(validarPosicion(tablero, fila, columna)) {
			tablero[fila][columna] = 1;  // Si pasa la verificacion, marco con 1 esa posicion
			if(buscarSoluciones(tablero, columna + 1))  // Llamo a la recursion
				return true;  // Retorno 1, si en ese camino encuentro una solucion
			tablero[fila][columna] = 0;  // Caso contrario, desmarco la casilla donde coloque el 1
		}
	}

	return false;  // No encuentra solucion
}

int main(int argc, char** argv) {
	int tablero[N][N];
	generarTablero(tablero);
	buscarSoluciones(tablero, 0);  // Le paso la columna inicial
	if(cantSoluciones > 0)
		cout << "Se encontraron " << cantSoluciones << " soluciones\n";
	else
		cout << "No se encontraron soluciones\n";
	return 0;
}
