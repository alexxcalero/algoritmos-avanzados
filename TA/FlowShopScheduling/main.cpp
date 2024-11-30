// Propuesta de solución para el problema de Flow Shop Scheduling Problem
// para la Tarea Académica del curso de Algoritmos Avanzados realizada
// por el grupo conformado por:
// 20206455 - Alex Calero Revilla
// 20210888 - Piero Perezanelli Stucchi
// 20211704 - Rodrigo Prado Valdivia
// 20212515 - Mikler Diaz Perez

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <ctime>
#include "Tarea.h"
#define ALFA 0.5
#define MAX_ITERACIONES 1000
#define MAX_TAREAS 100
#define MAX_MAQUINAS 100
using namespace std;

// Funcion para calcular el makespan utilizando Programacion Dinamica y matrices estaticas
int calcularMakespan(const vector<Tarea>& tareas, const vector<int>& orden, int numMaquinas) {
	int tiemposFinalizacion[MAX_TAREAS + 1][MAX_MAQUINAS + 1] = {0};

	for(int i = 1; i <= orden.size(); i++)
		for(int j = 1; j <= numMaquinas; j++)
			tiemposFinalizacion[i][j] = max(tiemposFinalizacion[i - 1][j], tiemposFinalizacion[i][j - 1]) + tareas[orden[i - 1]].GetTiemposProcesamiento()[j - 1];

	return tiemposFinalizacion[orden.size()][numMaquinas];
}

// Funcion para poder ordenar el arreglo de candidatos
bool compara(pair<int, int>a, pair<int, int>b) {
	return a.second > b.second;
}

// Fase de construccion de GRASP
vector<int> construirGRASP(const vector<Tarea>& tareas, int numMaquinas) {
	vector<int> candidatos, solucion;
	for (int i = 0; i < tareas.size(); i++) candidatos.push_back(i);

	while(!candidatos.empty()) {
		// Utilizamos pair, para poder guardar tanto el índice de la tarea
		// así como el makespan correspondiente a dicha tarea
		vector<pair<int, int>> makespanCandidatos;

		// Evaluar cada candidato en la solucion parcial
		for(int tarea : candidatos) {
			vector<int> solucionTemporal = solucion;
			solucionTemporal.push_back(tarea);
			int makespan = calcularMakespan(tareas, solucionTemporal, numMaquinas);
			makespanCandidatos.push_back({tarea, makespan});
		}

		// Encontrar limites del RCL
		sort(makespanCandidatos.begin(), makespanCandidatos.end(), compara);
		int beta = makespanCandidatos[0].second;  // Mejor
		int tau = makespanCandidatos[makespanCandidatos.size()-1].second;  // Peor

		// Crear RCL (Lista de Candidatos Restringida)
		vector<int> RCL;
		int inda = beta + ALFA * (tau - beta);  // Formula
		for(const auto& cm : makespanCandidatos)
			if(cm.second <= inda)
				RCL.push_back(cm.first);

		// Seleccionar aleatoriamente un elemento de la RCL
		int seleccionado = RCL[rand() % RCL.size()];
		solucion.push_back(seleccionado);
		candidatos.erase(remove(candidatos.begin(), candidatos.end(), seleccionado), candidatos.end());
	}

	return solucion;
}

// Fase de mejora (busqueda local)
vector<int> busquedaLocal(const vector<Tarea>& tareas, vector<int> secuencia, int numMaquinas) {
	bool mejora = true;
	vector<int> mejorSecuencia = secuencia;
	int mejorMakespan = calcularMakespan(tareas, secuencia, numMaquinas);

	while(mejora) {
		mejora = false;
		for(int i = 0; i < secuencia.size(); i++) {
			for(int j = i + 1; j < secuencia.size(); j++) {
				swap(secuencia[i], secuencia[j]);
				int nuevoMakespan = calcularMakespan(tareas, secuencia, numMaquinas);
				if (nuevoMakespan < mejorMakespan) {
					mejorMakespan = nuevoMakespan;
					mejorSecuencia = secuencia;
					mejora = true;
				}
				swap(secuencia[i], secuencia[j]);
			}
		}
	}

	return mejorSecuencia;
}

// Funcion general de GRASP
vector<int> GRASP(const vector<Tarea>& tareas, int numMaquinas) {
	vector<int> mejorSecuencia;
	int mejorMakespan = INT_MAX;

	for(int iter = 0; iter < MAX_ITERACIONES; iter++) {
		vector<int> secuenciaInicial = construirGRASP(tareas, numMaquinas);
		vector<int> secuenciaMejorada = busquedaLocal(tareas, secuenciaInicial, numMaquinas);
		int makespanActual = calcularMakespan(tareas, secuenciaMejorada, numMaquinas);

		if (makespanActual < mejorMakespan) {
			mejorMakespan = makespanActual;
			mejorSecuencia = secuenciaMejorada;
		}
	}

	return mejorSecuencia;
}

int main() {
	srand(time(0));  // Semilla

	int numTareas = 5, numMaquinas = 5;

	vector<Tarea> tareas = {
		Tarea(1, {2, 3, 4, 3, 3}),
		Tarea(2, {4, 2, 3, 4, 6}),
		Tarea(3, {6, 4, 1, 3, 5}),
		Tarea(4, {8, 5, 4, 8, 7}),
		Tarea(5, {10, 7, 5, 4, 3})
	};

	vector<int> mejorSecuencia = GRASP(tareas, numMaquinas);

	cout << "Mejor secuencia optima: ";
	for (const auto& tarea : mejorSecuencia)
		cout << tareas[tarea].GetId() << " ";
	cout << "\nMejor Makespan: " << calcularMakespan(tareas, mejorSecuencia, numMaquinas) << endl;

	return 0;
}
