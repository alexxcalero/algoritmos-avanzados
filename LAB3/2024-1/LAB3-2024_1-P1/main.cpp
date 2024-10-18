/*
 * Proyecto : LAB3-2024_1-P1
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 4 de octubre de 2024, 13:25
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include "Ciudad.h"
#define MAX 8
using namespace std;

bool compararDistancias(const Ciudad &a, const Ciudad &b) {
	return a.GetDistancia() < b.GetDistancia();
}

int calcularTiempoDeViaje(int ciudades[MAX][MAX], int ini, int fin) {
	int total = 0;
	int ciudadActual = ini;
	while(true) {
		vector<Ciudad> vecinos;
		for(int i = 0; i < MAX; i++) {
			if(ciudades[ciudadActual][i] != 0) {
				Ciudad ciudad;
				ciudad.SetIndice(i);
				ciudad.SetDistancia(ciudades[ciudadActual][i]);
				vecinos.push_back(ciudad);
			}
		}
		if(vecinos.empty()) {
			return total = -1;
		} else {
			sort(vecinos.begin(), vecinos.end(), compararDistancias);
			ciudadActual = vecinos[0].GetIndice();
			total += vecinos[0].GetDistancia();
		}
		if(ciudadActual == fin) break;
	}
	return total;
}

int main(int argc, char** argv) {
	int ciudades[MAX][MAX] = {
		{0, 4, 5, 6, 0, 0, 0, 0},
		{0, 0, 0, 0, 2, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 3},
		{0, 0, 0, 0, 0, 3, 0, 0},
		{0, 0, 0, 0, 0, 0, 10, 0},
		{0, 0, 0, 0, 0, 0, 2, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0}
	};

	int tiempoTotal = calcularTiempoDeViaje(ciudades, 0, 6);
	if(tiempoTotal != -1)
		cout << "Tiempo de viaje " << tiempoTotal << " min\n";
	else
		cout << "No se encontro una solucion\n";

	return 0;
}
