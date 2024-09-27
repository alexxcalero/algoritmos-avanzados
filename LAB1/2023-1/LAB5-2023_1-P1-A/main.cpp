/*
 * Proyecto : LAB5-2023_1-P1-A
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 6 de setiembre de 2024, 19:32
 */

#include <iostream>
#define REQ 3
using namespace std;

int soluciones[10];
int indice = 0;
int cantSoluciones = 0;

bool validarControl(int i, int cant, int requisitos[][REQ]) {
	if(requisitos[i][0] == -1)
		return true;

	int cantReq = 0;
	for(int k = 0; k < REQ; k++)
		if(requisitos[i][k] != -1)
			cantReq++;

	int cont = 0;
	for(int k = 0; k < REQ; k++)
		for(int l = 0; l < cant; l++)
			if(requisitos[i][k] == soluciones[l])
				cont++;

	if(cantReq == cont)
		return true;
	else
		return false;
}

bool buscarSoluciones(int controles[], int inversiones[], int beneficio[], int requisitos[][REQ], int n, int p, int i) {
	if(i == n || p < 0)
		return false;

	if(p == inversiones[i] && validarControl(i, indice, requisitos)) {
		soluciones[indice] = controles[i];
		cantSoluciones++;
		cout << "Solucion " << cantSoluciones << ": ";
		for(int k = 0; k <= indice; k++)
			cout << soluciones[k] << " ";
		cout << endl;
		//return true;
		return false;
	}

	soluciones[indice] = controles[i];
	indice++;
	if(validarControl(i, indice, requisitos) && buscarSoluciones(controles, inversiones, beneficio, requisitos, n, p - inversiones[i], i + 1))
		return true;
	else {
		indice--;
		return buscarSoluciones(controles, inversiones, beneficio, requisitos, n, p, i + 1);
	}
}

int main(int argc, char** argv) {
	int n = 8, p = 100;
	int controles[n] = {1, 2, 3, 4, 5, 6, 7, 8};
	int inversiones[n] = {32, 8, 40, 40, 20, 4, 20, 20};
	int beneficio[n] = {60, 32, 120, 60, 32, 20, 48, 60};
	int requisitos[n][REQ] = {
		{-1},
		{-1},
		{1, 2, -1},
		{-1},
		{-1},
		{2},
		{6},
		{6}
	};

	buscarSoluciones(controles, inversiones, beneficio, requisitos, n, p, 0);

	if(cantSoluciones > 0)
		cout << "Se encontraron " << cantSoluciones << " soluciones\n";
	else
		cout << "No se encontraron soluciones\n";

	return 0;
}
