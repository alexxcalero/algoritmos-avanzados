/*
 * Proyecto : LAB4-2024_2-P2
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 9 de noviembre de 2024, 08:26
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <ctime>
#include <cmath>
#include "Ciudad.h"
#define MAX_ITERACIONES 10000
#define MAX_CIUDADES 8
#define ALFA 0.4
using namespace std;

bool compara(const Ciudad &a, const Ciudad &b) {
	return a.GetGanancia() > b.GetGanancia();
}

int verifica(const vector<Ciudad> &vec, int minrcl) {
	int cont = 0;
	for(int i = 0; i < vec.size(); i++)
		if(minrcl <= vec[i].GetGanancia())
			cont++;
	return cont;
}

void realizarEntregas(int mapa[][MAX_CIUDADES], vector<Ciudad> &ciudades, int ini) {
	int mejor = INT_MIN;
	vector<Ciudad> mejorSolucion;
	for(int k = 0; k < MAX_ITERACIONES; k++) {
		srand(time(NULL));
		int total = 0;
		int ciudad = ini;
		vector<Ciudad> soluciones;
		while(1) {
			vector<Ciudad> vecinos;
			for(int i = 0; i < MAX_CIUDADES; i++) {  // Evaluo la matriz de mapa para sacar los vecinos
				if(mapa[ciudad][i] != 0)
					vecinos.push_back(ciudades[i]);
			}
			if(!vecinos.empty()) {  // Si hay vecinos, los evaluo para randomizar cual elegir
				sort(vecinos.begin(), vecinos.end(), compara);
				int beta = vecinos[0].GetGanancia();
				int tau = vecinos[vecinos.size() - 1].GetGanancia();
				int minrcl = round(beta - ALFA * (beta - tau));
				int indmin = verifica(vecinos, minrcl);
				int inda = rand() % indmin;
				ciudad = vecinos[inda].GetId();
				total += vecinos[inda].GetGanancia();
				soluciones.push_back(vecinos[inda]);
			} else {  // Si no tiene vecinos, ya no hay adonde ir y se termina el while
				break;
			}
		}
		if(total > mejor) {
			mejor = total;
			mejorSolucion.erase(mejorSolucion.begin(), mejorSolucion.end());
			mejorSolucion.insert(mejorSolucion.begin(), soluciones.begin(), soluciones.end());
		}
	}
	cout << "Ganancia = " << mejor;
	cout << "\nPuntos seleccionados = ";
	for(int i = 0; i < mejorSolucion.size(); i++)
		cout << char('A' + mejorSolucion[i].GetId()) << " ";
}

int main(int argc, char** argv) {
	int mapa[][MAX_CIUDADES] = {
		{0, 1, 1, 1, 1, 0, 0, 1},
		{0, 0, 1, 1, 0, 1, 0, 1},
		{0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}
	};
	vector<Ciudad> ciudades = {
		{0, 0}, {1, 20}, {2, 30}, {3, 40}, {4, 40}, {5, 40}, {6, 10}, {7, 50}
	};
	realizarEntregas(mapa, ciudades, 0);
	return 0;
}
