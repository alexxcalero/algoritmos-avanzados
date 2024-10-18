/*
 * Proyecto : EX2-2021_1-P1
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 15 de octubre de 2024, 00:10
 */

#include <iostream>
#include <iomanip>
#define C 6
using namespace std;

int solucion[C];
int indSol = 0;
int cantSol = 0;
int costoTotal = 0;

void inicializarArregloSolucion(int solucion[]) {
	for(int i = 0; i < C; i++)
		solucion[i] = -1;
}

bool verificarVacuna(int vacuna, int ciudad, int cantCiudades, int colindantes[C][C], bool refrigeracion[]) {
	if(vacuna == 0 && refrigeracion[ciudad] == false)
		return false;

	for(int i = 0; i < cantCiudades; i++) {
		if(colindantes[ciudad][i] == 1 && solucion[i] == vacuna)
			return false;

		if(colindantes[i][ciudad] == 1 && solucion[i] == vacuna)
			return false;
	}

	return true;
}

bool asignarVacunas(int colindantes[C][C], int costos[], bool refrigeracion[], int cantCiudades, int cantVacunas, int pos) {
	if(pos == cantCiudades) {
		cantSol++;
		cout << "Solucion " << cantSol << ":\n";
		cout << "Ciudad: ";
		for(int i = 0; i < indSol; i++)
			cout << setw(3) << i;
		cout << "\nVacuna: ";
		for(int i = 0; i < indSol; i++)
			cout << setw(3) << solucion[i] + 1;
		cout << "\nCosto total de $ " << costoTotal << " k\n\n";
		//return true;
		return false;
	}

	for(int i = 0; i < cantVacunas; i++) {
		if(verificarVacuna(i, pos, cantCiudades, colindantes, refrigeracion)) {
			solucion[indSol] = i;
			indSol++;
			costoTotal += costos[i];
			if(asignarVacunas(colindantes, costos, refrigeracion, cantCiudades, cantVacunas, pos + 1))
				return true;
			costoTotal -= costos[i];
			indSol--;
			solucion[indSol] = -1;
		}
	}

	return false;
}

int main(int argc, char** argv) {
	int cantCiudades = 6, cantVacunas = 4;
	bool refrigeracion[cantCiudades] = {false, false, true, false, true, false};
	int costos[cantVacunas] = {10, 5, 12, 8};
	int colindantes[C][C] = {
		{0, 1, 1, 0, 0, 1},
		{1, 0, 1, 1, 0, 0},
		{1, 1, 0, 1, 0, 1},
		{0, 1, 1, 0, 1, 1},
		{0, 0, 0, 1, 0, 1},
		{0, 0, 1, 1, 1, 0}
	};
	inicializarArregloSolucion(solucion);
	asignarVacunas(colindantes, costos, refrigeracion, cantCiudades, cantVacunas, 0);
	if(cantSol > 0)
		cout << "Se pudo asignar las vacunas\n";
	else
		cout << "No se pudo asignar las vacunas\n";
	return 0;
}
