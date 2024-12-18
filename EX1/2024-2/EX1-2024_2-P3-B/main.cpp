/*
 * Proyecto : EX1-2024_2-P3-B
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 15 de octubre de 2024, 11:42
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Tarea.h"
using namespace std;

// Ordeno como indica el enunciado, por mayor ganancia
bool compara(const Tarea &a, const Tarea &b) {
	return a.GetGanancia() > b.GetGanancia();
}

// Calculo el mayor tiempo posible que hay para entregar una tarea
int calcularMayorHora(vector<Tarea> &tareas, int k) {
	int max = INT_MIN;
	for(int i = 0; i < k; i++) {
		if(tareas[i].GetHora() > max)
			max = tareas[i].GetHora();
	}
	return max;
}

void seleccionarTareas(vector<Tarea> &tareas, int k) {
	// Ordeno por ganancia
	sort(tareas.begin(), tareas.end(), compara);

	// Calculo cual es la maxima opcion de hora
	int maxHora = calcularMayorHora(tareas, k);

	// Creo mi arreglo solucion con el tamanho maximo de opcion de entrega (maxHora)
	char solucion[maxHora];
	for(int i = 0; i < maxHora; i++)
		solucion[i] = '-';

	int ganancia = 0;
	for(int i = 0; i < k; i++) {
		int hora = tareas[i].GetHora() - 1;  // Guardo la hora
		// Voy a recorrer el arreglo de solucion empezando por la hora maxima que tengo para entregar
		// y poco a poco voy retrocediendo
		for(int j = hora; j >= 0; j--) {
			// Verifico si en esa posicion del arreglo de solucion no hay tarea asignada
			if(solucion[j] == '-') {
				solucion[j] = tareas[i].GetId();  // Guardo la tarea
				ganancia += tareas[i].GetGanancia();  // Aumento la ganancia
				break;
			}
		}
	}

	// Imprimo la solucion
	cout << "Se consideran las tareas: ";
	for(int i = 0; i < maxHora; i++)
		// Imprimo las posiciones en la solucion que se han asignado
		if(solucion[i] != '-')
			cout << solucion[i] << (i + 1 == maxHora ? " " : ", ");
	cout << "\nCon una ganancia de: " << ganancia << endl;
}

int main(int argc, char** argv) {
	vector<Tarea> tareas = {
		Tarea('A', 2, 100),
		Tarea('B', 1, 19),
		Tarea('C', 2, 27),
		Tarea('D', 1, 25),
		Tarea('E', 3, 15),
	};
//    vector<Tarea> tareas = {
//        Tarea('A', 4, 20),
//        Tarea('B', 1, 10),
//        Tarea('C', 2, 40),
//        Tarea('D', 2, 30),
//    };
	int k = tareas.size();
	seleccionarTareas(tareas, k);
	return 0;
}
