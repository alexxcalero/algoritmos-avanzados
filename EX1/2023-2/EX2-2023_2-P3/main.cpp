/*
 * Proyecto : EX2-2023_2-P3
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 15 de octubre de 2024, 10:16
 */

#include <iostream>
#define N 9
using namespace std;

int solucion[N];
int indSol = 0;

void inicializarSolucion(int solucion[]) {
	for(int i = 0; i < N; i++)
		solucion[i] = -1;
}

bool verificarEtiqueta(int etiqueta, int pos, int envios[N][N]) {
	for(int i = 0; i < N; i++) {
		if(envios[pos][i] == 1 || envios[i][pos] == 1)
			continue;

		if(envios[pos][i] != 0 && solucion[i] == etiqueta)
			return false;

		if(envios[i][pos] != 0 && solucion[i] == etiqueta)
			return false;
	}

	return true;
}

bool asignarEtiquetas(int envios[N][N], int cantEtiquetas, int pos) {
	if(pos == N) {
		cout << "Activos:   ";
		for(int i = 0; i < indSol; i++)
			cout << i + 1 << " ";
		cout << "\nEtiquetas: ";
		for(int i = 0; i < indSol; i++)
			cout << solucion[i] + 1 << " ";
		cout << endl;
		return true;
	}

	for(int i = 0; i < cantEtiquetas; i++) {
		if(verificarEtiqueta(i, pos, envios)) {
			solucion[indSol] = i;
			indSol++;
			if(asignarEtiquetas(envios, cantEtiquetas, pos + 1))
				return true;
			indSol--;
			solucion[indSol] = -1;
		}
	}

	return false;
}

int main(int argc, char** argv) {
	int envios[N][N] = {
		{1, 2, 0, 6, 0, 0, 0, 0, 2},
		{7, 1, 5, 2, 0, 0, 0, 0, 7},
		{0, 3, 1, 2, 3, 8, 9, 7, 5},
		{2, 7, 5, 1, 2, 0, 0, 0, 0},
		{0, 0, 5, 3, 1, 4, 0, 0, 0},
		{0, 0, 9, 0, 6, 1, 2, 0, 0},
		{0, 0, 3, 0, 0, 7, 1, 4, 0},
		{0, 0, 4, 0, 0, 0, 9, 1, 9},
		{5, 3, 6, 0, 0, 0, 0, 4, 1}
	};
	int cantEtiquetas = 4;
	inicializarSolucion(solucion);
	if(asignarEtiquetas(envios, cantEtiquetas, 0))
		cout << "Se pudo asignar etiquetas a todos los activos\n";
	else
		cout << "No hay solucion\n";
	return 0;
}
