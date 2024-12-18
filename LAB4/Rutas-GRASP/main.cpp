/*
 * Proyecto : Rutas-GRASP
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 5 de noviembre de 2024, 22:30
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <ctime>
#include <cmath>
#include "Ciudad.h"
#define MAX_ITERACIONES 1000000
#define MAX_CIUDADES 8
#define ALFA 0.6
using namespace std;

bool compara(const Ciudad &a, const Ciudad &b) {
	return a.GetDistancia() < b.GetDistancia();
}

int verifica(vector<Ciudad> &vecinos, int rcl) {
	int cont = 0;
	for(int i = 0; i < vecinos.size(); i++)
		if(rcl >= vecinos[i].GetDistancia())
			cont++;
	return cont;
}

void hallarRuta(int mapa[][MAX_CIUDADES], int ini, int fin) {
	int min = INT_MAX;
	for(int k = 0; k < MAX_ITERACIONES; k++) {
		int total = 0;
		srand(time(NULL));
		int ciudad = ini;
		while(1) {
			vector<Ciudad> vecinos;
			for(int i = 0; i < MAX_CIUDADES; i++) {
				if(mapa[ciudad][i] > 0) {
					Ciudad aux;
					aux.SetDistancia(mapa[ciudad][i]);
					aux.SetId(i);
					vecinos.push_back(aux);
				}
			}
			if(!vecinos.empty()) {
				sort(vecinos.begin(), vecinos.end(), compara);
				int beta = vecinos[0].GetDistancia();
				int tau = vecinos[vecinos.size() - 1].GetDistancia();
				int rcl = round(beta + ALFA * (tau - beta));
				int indrcl = verifica(vecinos, rcl);
				int inda = rand() % indrcl;
				ciudad = vecinos[inda].GetId();
				total += vecinos[inda].GetDistancia();
			}
			if(ciudad == fin) break;
			if(vecinos.empty()) {
				//cout << "No se encontro la ciudad fin" << endl;
				total = INT_MAX;
				break;
			}
		}
		if(total < min)
			min = total;
	}
	cout << min << endl;
}

int main(int argc, char** argv) {
	int mapa[][MAX_CIUDADES] = {
		{0, 18, 10, 15, 0, 0 , 0, 0},
		{0, 0 , 0 , 0 , 0, 15, 0, 5},
		{0, 0 , 0 , 0 , 0, 20, 0, 0},
		{0, 0 , 0 , 0 , 1, 0 , 0, 0},
		{0, 0 , 0 , 0 , 0, 0 , 1, 0},
		{0, 0 , 0 , 0 , 0, 0 , 5, 0},
		{0, 0 , 0 , 0 , 0, 0 , 0, 0},
		{0, 0 , 0 , 0 , 0, 0 , 0, 0}
	};
	hallarRuta(mapa, 0, 6);
	return 0;
}
