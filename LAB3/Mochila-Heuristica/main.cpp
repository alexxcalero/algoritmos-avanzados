/*
 * Proyecto : Mochila-Heuristica
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 4 de octubre de 2024, 13:14
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int cargaMochila(int peso, vector<int> &paquetes) {
	int residual = peso;

	sort(paquetes.begin(), paquetes.end());

	for(int i = paquetes.size() - 1; i >= 0; i--)
		if(residual >= paquetes[i])
			residual -= paquetes[i];

	return residual;
}

int main(int argc, char** argv) {
	vector<int> paquetes = {2, 3, 5, 12, 2};
	int peso = 16;
	int residual = cargaMochila(peso, paquetes);
	if(residual == 0)
		cout << "Si se completo el peso total de la mochila -> Residual = 0\n";
	else
		cout << "No se completo el peso total de la mochila -> Residual = " << residual << endl;
	return 0;
}
