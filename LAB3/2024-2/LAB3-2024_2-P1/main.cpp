/*
 * Proyecto : LAB3-2024_2-P1
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 5 de octubre de 2024, 08:14
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include "Proyecto.h"
#define MAX 12
using namespace std;

bool compara(const Proyecto &a, const Proyecto &b) {
	return (a.GetGanancia() * a.GetBeneficio()) / a.GetCosto() > (b.GetGanancia() * b.GetBeneficio()) / b.GetCosto();
}

bool estaDisponible(int id, int marcados[]) {
	return marcados[id - 1] == 1 ? true : false;
}

bool verificarPredecesores(const vector<int> &predecesores, vector<int> &seleccionados) {
	// En caso el proyecto no tenga predecesores
	if(predecesores[0] == -1)
		return true;

	// Verifico que todos los predecesores de un proyecto
	// hayan sido previamente seleccionados
	int cont = 0;
	for(int i = 0; i < predecesores.size(); i++) {
		for(int j = 0; j < seleccionados.size(); j++) {
			if(predecesores[i] == seleccionados[j]) {
				cont++;
				break;
			}
		}
	}

	// Verifico la cantidad de predecesores que han sido seleccionados
	if(cont == predecesores.size())
		return true;
	else
		return false;
}

void seleccionarProyectos(vector<Proyecto> &proyectos, int p) {
	sort(proyectos.begin(), proyectos.end(), compara);

	int ganancia = 0;
	int costoParcial = 0;
	int marcados[proyectos.size()];
	for(int i = 0; i < proyectos.size(); i++) marcados[i] = 1;
	vector<int> seleccionados;

	while(true) {
		int excedio = false;
		for(int i = 0; i < proyectos.size(); i++) {
			// Primero verifico si el proyecto todavia no ha sido seleccionado
			if(estaDisponible(proyectos[i].GetId(), marcados)) {
				// Ahora verifico si considerando el proyecto se sobrepasa el presupuesto
				if(costoParcial + proyectos[i].GetCosto() > p) {
					excedio = true;
					break;
				}
				// Si no se excedio el presupuesto, verifico si se han incluido los predecesores
				if(verificarPredecesores(proyectos[i].GetPredecesores(), seleccionados)) {
					costoParcial += proyectos[i].GetCosto();
					seleccionados.push_back(proyectos[i].GetId());
					marcados[proyectos[i].GetId() - 1] = 0;
					ganancia += proyectos[i].GetGanancia();
					break;
				}
			}
		}
		// Si se excedio el presupuesto salgo del bucle
		if(excedio == true) break;
	}

	cout << "Proyectos seleccionados: ";
	for(int id : seleccionados) cout << id << " ";
	cout << "\nGanancia: " << ganancia << endl;
}

int main(int argc, char** argv) {
	int p = 250;
	vector<Proyecto> proyectos = {
		Proyecto(1, 80, 150, 2, {-1}),
		Proyecto(2, 20, 80, 5, {4}),
		Proyecto(3, 100, 300, 1, {1, 2}),
		Proyecto(4, 100, 150, 4, {-1}),
		Proyecto(5, 50, 80, 2, {-1}),
		Proyecto(6, 10, 50, 1, {2}),
		Proyecto(7, 50, 120, 2, {6}),
		Proyecto(8, 50, 150, 4, {6})
	};
	seleccionarProyectos(proyectos, p);
	return 0;
}
