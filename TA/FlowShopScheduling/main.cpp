// Propuesta de solución para el problema de Flow Shop Scheduling Problem
// para la Tarea Académica del curso de Algoritmos Avanzados realizada
// por el grupo conformado por:
// 20206455 - Alex Calero Revilla
// 20210888 - Piero Perezanelli Stucchi
// 20211704 - Rodrigo Prado Valdivia
// 20212515 - Mikler Diaz Perez

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <ctime>
#include "Tarea.h"
#define MAX_ITERACIONES 1000
#define MAX_TAREAS 20
#define MAX_MAQUINAS 10
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
vector<int> construirGRASP(const vector<Tarea>& tareas, int numMaquinas, double alfa) {
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
		int inda = beta + alfa * (tau - beta);  // Formula
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
vector<int> GRASP(const vector<Tarea>& tareas, int numMaquinas, double alfa) {
	vector<int> mejorSecuencia;
	int mejorMakespan = INT_MAX;

	for(int iter = 0; iter < MAX_ITERACIONES; iter++) {
		vector<int> secuenciaInicial = construirGRASP(tareas, numMaquinas, alfa);
		vector<int> secuenciaMejorada = busquedaLocal(tareas, secuenciaInicial, numMaquinas);
		int makespanActual = calcularMakespan(tareas, secuenciaMejorada, numMaquinas);

		// Imprimimos los resultados de cada iteracion
		cout << "Iteracion " << setw(4) << setfill('0') << iter + 1 << " -> Makespan: " << makespanActual << endl;

		if (makespanActual < mejorMakespan) {
			mejorMakespan = makespanActual;
			mejorSecuencia = secuenciaMejorada;
		}
	}

	return mejorSecuencia;
}

int main() {
	srand(time(0));  // Semilla

	int numTareas = MAX_TAREAS, numMaquinas = MAX_MAQUINAS;

	vector<Tarea> tareas = {
		Tarea(1, {3, 4, 2, 5, 6, 2, 4, 3, 6, 7}),
        Tarea(2, {4, 5, 3, 6, 7, 3, 5, 4, 6, 8}),
        Tarea(3, {2, 3, 5, 6, 8, 1, 3, 4, 6, 5}),
        Tarea(4, {6, 7, 8, 5, 4, 7, 6, 5, 4, 3}),
        Tarea(5, {5, 6, 7, 8, 5, 6, 4, 3, 7, 6}),
        Tarea(6, {7, 4, 6, 5, 7, 3, 4, 2, 5, 7}),
        Tarea(7, {8, 3, 5, 4, 6, 4, 3, 5, 6, 7}),
        Tarea(8, {4, 5, 6, 7, 8, 5, 6, 4, 3, 6}),
        Tarea(9, {5, 6, 7, 5, 4, 6, 7, 5, 4, 6}),
        Tarea(10, {3, 4, 5, 6, 7, 4, 5, 3, 6, 7}),
        Tarea(11, {6, 7, 5, 8, 9, 6, 8, 7, 5, 6}),
        Tarea(12, {2, 5, 4, 3, 6, 3, 4, 5, 6, 7}),
        Tarea(13, {4, 6, 3, 5, 7, 4, 6, 5, 4, 5}),
        Tarea(14, {7, 6, 8, 5, 6, 7, 6, 5, 4, 3}),
        Tarea(15, {5, 7, 6, 5, 4, 6, 5, 4, 6, 7}),
        Tarea(16, {3, 5, 4, 6, 7, 5, 6, 3, 4, 6}),
        Tarea(17, {4, 3, 5, 6, 6, 4, 5, 4, 3, 7}),
        Tarea(18, {5, 4, 7, 6, 5, 3, 5, 6, 5, 4}),
        Tarea(19, {6, 5, 4, 7, 8, 5, 6, 4, 3, 4}),
        Tarea(20, {7, 6, 5, 6, 7, 6, 5, 4, 3, 5})
	};

	// Luego de ejecutar el proyecto FlowShopSchedulingTest, seleccionamos el mejor valor de alfa
	double alfa = 0.45;
	vector<int> mejorSecuencia = GRASP(tareas, numMaquinas, alfa);

	cout << "Mejor secuencia: ";
	for (const auto& tarea : mejorSecuencia)
		cout << tareas[tarea].GetId() << " ";
	cout << "\nMejor makespan: " << calcularMakespan(tareas, mejorSecuencia, numMaquinas) << endl;

	return 0;
}
