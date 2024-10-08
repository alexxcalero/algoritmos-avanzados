/*
 * Proyecto : CoinChange-Heuristica
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 4 de octubre de 2024, 13:04
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void coinChange(int monto, vector<int> &monedas) {
	vector<int> solucion;

	// Ordenamos el vector -> Se ordena de menor a mayor
	sort(monedas.begin(), monedas.end());

	// Empezamos desde el final del vector, para evaluar primero las monedas de mayor valor
	for(int i = monedas.size() - 1; i >= 0; i--) {
		while(monto >= monedas[i]) {
			monto -= monedas[i];
			solucion.push_back(monedas[i]);
		}
	}

	for(int moneda : solucion)
		cout << moneda << " ";
}

int main(int argc, char** argv) {
	int monto = 27;
	vector<int> monedas = {50, 100, 2, 1, 5, 10, 20};
	cout << "El cambio de " << monto << " soles, se realiza con las siguientes monedas: ";
	coinChange(monto, monedas);
	return 0;
}
