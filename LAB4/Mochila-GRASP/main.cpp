/*
 * Proyecto : Mochila-GRASP
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 5 de noviembre de 2024, 22:18
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <ctime>
#define MAX_ITERACIONES 10000
#define ALFA 0.3
using namespace std;

bool compara(int a, int b) {
	return a > b;
}

int verifica(vector<int> &auxPaquetes, double rcl) {
	int cont = 0;
	for(int i = 0; i < auxPaquetes.size(); i++)
		if(rcl <= auxPaquetes[i])
			cont++;
	return cont;
}

void cargaMochila(vector<int> &paquetes, int peso, int n) {
	int mejor = INT_MAX;
	vector<int> mejorSolucion;
	for(int k = 0; k < MAX_ITERACIONES; k++) {
		// Fase de construccion
		srand(time(NULL));
		vector<int> soluciones;
		vector<int> auxPaquetes = paquetes;
		sort(auxPaquetes.begin(), auxPaquetes.end(), compara);
		int residual = peso;
		while(!auxPaquetes.empty()) {
			int beta = auxPaquetes[0];
			int tau = auxPaquetes[auxPaquetes.size() - 1];
			double rcl = beta - ALFA * (beta - tau);
			int ind = verifica(auxPaquetes, rcl);
			int inda = rand() % ind;
			if(residual - auxPaquetes[inda] >= 0) {
				soluciones.push_back(auxPaquetes[inda]);
				residual -= auxPaquetes[inda];
			}
			auxPaquetes.erase(auxPaquetes.begin() + inda);
		}
		if(residual < mejor) {
			mejor = residual;
			mejorSolucion.erase(mejorSolucion.begin(), mejorSolucion.end());
			mejorSolucion.insert(mejorSolucion.begin(), soluciones.begin(), soluciones.end());
		}
	}
	cout << mejor << endl;
	for(int i = 0; i < mejorSolucion.size(); i++)
		cout << mejorSolucion[i] << " ";
}

int main(int argc, char** argv) {
	vector<int> paquetes = {10, 2, 1, 5, 9, 8};
	int n = paquetes.size();
	int peso = 14;
	cargaMochila(paquetes, peso, n);
	return 0;
}
