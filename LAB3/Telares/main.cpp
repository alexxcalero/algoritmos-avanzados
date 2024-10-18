/*
 * Proyecto : Telares
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 5 de octubre de 2024, 00:48
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void calcularMinimos(vector<int> &tiemposTotales, int &minIndice) {
	int minI = 0;
	int minT = tiemposTotales[0];
	for(int i = 1; i < tiemposTotales.size(); i++) {
		if(tiemposTotales[i] < minT) {
			minI = i;
			minT = tiemposTotales[i];
		}
	}
	minIndice = minI;
}

int calcularMinTiempo(vector<int> &tiemposTotales) {
	int max = 0;
	for(int i : tiemposTotales)
		if(i > max)
			max = i;
	return max;
}

void tejerTelares(vector<int> &telas, int T, int K) {
	vector<int> tiemposTotales(K, 0);
	int asignaciones[K][telas.size()];
	vector<int> indiceAsignaciones(K, 0);

	int minIndice;
	for(int i = 0; i < telas.size(); i++) {
		calcularMinimos(tiemposTotales, minIndice);
		tiemposTotales[minIndice] += T * telas[i];
		asignaciones[minIndice][indiceAsignaciones[minIndice]++] = telas[i];
	}

	cout << "Asignaciones de las telas a los telares:\n";
	for(int i = 0; i < K; i++) {
		cout << "Telar " << i << ": ";
		for(int j = 0; j < indiceAsignaciones[i]; j++) {
			cout << asignaciones[i][j];
			if(j != indiceAsignaciones[i] - 1) cout << ", ";
			else cout << " ";
		}
		cout << "- Tiempo total de trabajo: " << tiemposTotales[i] << " unidades de tiempo\n";
	}

	int minTiempo = calcularMinTiempo(tiemposTotales);
	cout << "Tiempo minimo para terminar todas las telas: " << minTiempo << endl;
}

int main(int argc, char** argv) {
	int T = 5;
	int K = 4;
	vector<int> telas = {10, 7, 8, 12, 6, 9};
	tejerTelares(telas, T, K);
	return 0;
}
