/*
 * Proyecto : EX1-2024_1-P3-B
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 13 de octubre de 2024, 15:47
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int buscarTelarConMenorTiempo(vector<int> &tiemposAcumulados, vector<int> &tiempoTelares, int longitudTela) {
	int minId;
	int minTiempo = INT_MAX;

	for(int i = 0; i < tiemposAcumulados.size(); i++) {
		if(tiemposAcumulados[i] + tiempoTelares[i] * longitudTela < minTiempo) {
			minTiempo = tiemposAcumulados[i] + tiempoTelares[i] * longitudTela;
			minId = i;
		}
	}

	return minId;
}

void asignarTelas(vector<int> &tiempoTelares, vector<int> &longitudTelas) {
	vector<int> tiemposAcumulados(tiempoTelares.size(), 0);
	vector<vector<int>> telasAsignadas(tiempoTelares.size());

	for(int i = 0; i < longitudTelas.size(); i++) {
		int idTelarMinTiempAcum = buscarTelarConMenorTiempo(tiemposAcumulados, tiempoTelares, longitudTelas[i]);
		tiemposAcumulados[idTelarMinTiempAcum] += tiempoTelares[idTelarMinTiempAcum] * longitudTelas[i];
		telasAsignadas[idTelarMinTiempAcum].push_back(longitudTelas[i]);
	}

	cout << "Asignaciones de telas a los telares:\n";
	for(int i = 0; i < tiempoTelares.size(); i++) {
		cout << "Telar " << i + 1 << ": ";
		for(int j = 0; j < telasAsignadas[i].size(); j++) {
			cout << telasAsignadas[i][j] << (j + 1 == telasAsignadas[i].size() ? " " : ", ");
		}
		cout << "- Tiempo total de trabajo: " << tiemposAcumulados[i] << " unidades de tiempo\n";
	}

	int tiempoMax = *max_element(tiemposAcumulados.begin(), tiemposAcumulados.end());
	cout << "Tiempo total para terminar todas las telas: " << tiempoMax << " unidades de tiempo\n";
}

int main(int argc, char** argv) {
	vector<int> tiempoTelares = {5, 4, 6};
	vector<int> longitudTelas = {10, 7, 9, 12, 6, 8};
	asignarTelas(tiempoTelares, longitudTelas);
	return 0;
}
