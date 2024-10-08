/*
 * Proyecto : JobSequence
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 4 de octubre de 2024, 17:17
 */

/*
 * Explicaciones detalladas:
 * https://www.geeksforgeeks.org/job-sequencing-problem/
 * https://nishtha01.medium.com/job-scheduling-problem-using-greedy-approach-f7c9a33430e6
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include "Trabajo.h"
using namespace std;

bool compara(const Trabajo &a, const Trabajo &b) {
	return a.GetGanancia() > b.GetGanancia();
}

int calcularLimiteMaximo(const vector<Trabajo> &trabajos) {
	int max = 0;
	for(Trabajo t : trabajos)
		if(t.GetLimite() > max)
			max = t.GetLimite();
	return max;
}

int main(int argc, char** argv) {
	vector<Trabajo> trabajos = {Trabajo(0, 2, 100), Trabajo(1, 1, 19), Trabajo(2, 2, 27), Trabajo(3, 1, 25), Trabajo(4, 3, 15)};

	sort(trabajos.begin(), trabajos.end(), compara);

	//for(Trabajo t : trabajos) cout << t.GetId() << "-" << t.GetLimite() << "-" << t.GetGanancia() << " ";

	int gananciaTotal = 0;
	int limMax = calcularLimiteMaximo(trabajos);
	vector<int> limites(limMax, -1);
	vector<Trabajo> trabajosSeleccionados;

	for(int i = 0; i < trabajos.size(); i++) {
		for(int j = trabajos[i].GetLimite() - 1; j >= 0; j--) {
			if(limites[j] == -1) {
				limites[j] = trabajos[i].GetId();
				gananciaTotal += trabajos[i].GetGanancia();
				trabajosSeleccionados.push_back(trabajos[i]);
				break;
			}
		}
	}

	cout << "La ganancia maxima es " << gananciaTotal << " soles\n";
	cout << "Los trabajos que generan esta ganancia maxima son: ";
	for(Trabajo t : trabajosSeleccionados)
		cout << t.GetId() << " ";

	return 0;
}
