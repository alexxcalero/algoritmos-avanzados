/*
 * Proyecto : EX2-2024_2-P1
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 10 de diciembre de 2024, 11:35
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include <ctime>
#include "Tarea.h"
#define ALFA 0.4
#define MAX_ITERA 10000
using namespace std;

// Funcion para poder ordenar el vector auxiliar de tareas, dependiendo de que tan temprana
// es la hora final para poder completar la tarea (criterio Greedy brindado en el enunciado)
bool compara(Tarea &a, Tarea &b) {
	if(a.GetFin() < b.GetFin())  // Si los tiempos finales son diferentes
		return a.GetFin() < b.GetFin();
	else if(a.GetFin() == b.GetFin())  // Si los tiempos finales son iguales, se compara los tiempos iniciales
		return a.GetInicio() < b.GetInicio();
}

// Funcion para asignar la tarea en sus respectivo espacios de tiempos
void marcarTiempos(Tarea &tarea, int indiceParaEmpezar, vector<int> &tiempos) {
	for(int i = 0; i < tarea.GetDuracion(); i++) {
		tiempos[indiceParaEmpezar] = tarea.GetId();
		indiceParaEmpezar++;
	}
}

// Funcion para verificar si se puede programar la tarea o no
bool sePuedeAsignarLaTarea(Tarea &tarea, vector<int> &tiempos) {
	int duracion = tarea.GetDuracion();
	int ini = tarea.GetInicio() - 1;
	int fin = tarea.GetFin() - 1;
	int cantEspacios = 0;
	int indiceParaEmpezar;
	bool yaHayIndiceParaEmpezar = false;

	for(int i = ini; i <= fin; i++) {
		if(tiempos[i] == 0) {  // Ese tiempo no esta ocupado por otra tarea
			if(!yaHayIndiceParaEmpezar) {
				indiceParaEmpezar = i;  // Seteo el indice de donde puedo empezar a asignar la tarea
				yaHayIndiceParaEmpezar = true;  // Actualizo la bandera a true
			}
			cantEspacios++;  // Aumento el contador de espacios
		} else {
			yaHayIndiceParaEmpezar = false;  // coloco la bandera en false
			cantEspacios = 0;  // Reinicio el contador de espacios
		}
	}

	// Verifico si la cantidad de espacios es mayor a la duracion de la tarea
	if(cantEspacios >= duracion) {
		marcarTiempos(tarea, indiceParaEmpezar, tiempos);  // Asigno la tarea a los espacios de tiempo correspondientes
		return true;  // Retorno true
	} else
		return false;  // Retorno false
}

// Funcion que sirve para dar el rango de aleatoriedad a mi solucion GRASP
int verifica(vector<Tarea> &auxTareas, int cantTareas, int rcl) {
	int cont = 0;
	for(int i = 0; i < cantTareas; i++)
		if(auxTareas[i].GetFin() <= rcl)
			cont++;
	return cont;
}

// Funcion para poder calcular la hora mas lejana que servira para crear mi arreglo de tiempos
int calcularMayorHora(vector<Tarea> &tareas, int cantTareas) {
	int max = INT_MIN;
	for(int i = 0; i < cantTareas; i++)
		if(tareas[i].GetFin() > max)
			max = tareas[i].GetFin();
	return max;
}

void asignacionDeTareas(vector<Tarea> &tareas, int cantTareas) {
	// Calculo la hora final maxima entre todas las tareas
	int maxHora = calcularMayorHora(tareas, cantTareas);
	int menorPenalizacion = INT_MAX;  // Variable para seleccionar la mejor respuesta
	vector<Tarea> tareasProgramadas;  // Vector donde guardare las tareas programadas
	vector<Tarea> tareasNoProgramadas;  // Vector donde guardare las tareas no programadas

	for(int k = 0; k < MAX_ITERA; k++) {
		srand(time(NULL));

		vector<Tarea> auxTareas = tareas;  // Copio el vector original de tareas a uno auxiliar
		sort(auxTareas.begin(), auxTareas.end(), compara);  // Ordeno el vector auxiliar de tareas

		vector<int> tiempos(maxHora, 0);  // Creo un vector de tiempos (asignacion de las tareas)
		vector<Tarea> programadas;  // Vector temporal donde guardare las tareas programadas
		vector<Tarea> noProgramadas;  // Vector temporal donde guardare las tareas no programadas
		int penalizacion = 0;  // Incrementador de penalizacion

		// Hago el bucle mientras hayan tareas por procesar
		while(!auxTareas.empty()) {
			int beta = auxTareas[0].GetFin();  // Tarea con fin mas temprano
			int tau = auxTareas[auxTareas.size() - 1].GetFin();  // Tarea con fin mas lejano
			int rcl = round(beta + ALFA * (tau - beta));  // maxRCL
			int ind = verifica(auxTareas, cantTareas, rcl);  // Funcion que da la aleatoriedad
			int inda = rand() % ind;  // Selecciono un indice aleatorio

			// Verifico si hay espacio para poder asignar la tarea
			if(sePuedeAsignarLaTarea(auxTareas[inda], tiempos)) {
				programadas.push_back(auxTareas[inda]);  // Agrego la tarea a mi arreglo temporal de programadas
			} else {
				noProgramadas.push_back(auxTareas[inda]);  // Agrego la tarea a mi arreglo temporal de no programadas
				penalizacion += auxTareas[inda].GetPenalizacion();  // Aumento la penalizacion
			}

			// Elimino la tarea recien procesada
			auxTareas.erase(auxTareas.begin() + inda);
		}

		// Verifico si la penalizacion de esta vuelta / pasada, es menor que la menorPenalizacion
		if(penalizacion < menorPenalizacion) {
			menorPenalizacion = penalizacion;  // Actualizo la menorPenalizacion
			tareasProgramadas = programadas;  // Guardo mi vector temporal en mi vector respuesta
			tareasNoProgramadas = noProgramadas;  // Guardo mi vector temporal en mi vector respuesta
		}
	}

	cout << "Tareas programadas: ";
	for(Tarea t : tareasProgramadas)
		cout << "T" << t.GetId() << " ";

	cout << "\nTareas no programadas: ";
	for(Tarea t : tareasNoProgramadas)
		cout << "T" << t.GetId() << " ";

	cout << "\nPenalizacion total: " << menorPenalizacion << endl;
}

int main(int argc, char** argv) {
	vector<Tarea> tareas = {
		Tarea(1, 2, 1, 4, 10),
		Tarea(2, 3, 3, 6, 15),
		Tarea(3, 1, 5, 7, 8),
		Tarea(4, 2, 2, 5, 12),
		Tarea(5, 4, 6, 10, 20),
		Tarea(6, 2, 8, 11, 7),
		Tarea(7, 1, 9, 10, 6),
		Tarea(8, 3, 1, 3, 18),
		Tarea(9, 2, 4, 7, 14),
		Tarea(10, 3, 6, 9, 16)
	};

	int cantTareas = tareas.size();

	asignacionDeTareas(tareas, cantTareas);

	return 0;
}
