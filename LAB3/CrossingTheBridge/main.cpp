/*
 * Proyecto : CrossingTheBridge
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 4 de octubre de 2024, 16:14
 */

// Explicacion detallada: https://www.enjoymathematics.com/blog/bridge-crossing-at-night

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int crossingTheBridge(vector<int> &personas) {
	sort(personas.begin(), personas.end());  // Ordeno el vector de menor a mayor

	int tiempoTotal = 0;
	int menorTiempo = personas[0];  // Selecciono el mejor tiempo -> primera posicion del vector

	for(int i = 1; i < personas.size(); i++) {
		// Incremento el tiempoTotal con el valor de la persona[i] (la mas lenta de las dos que van juntas)
		tiempoTotal += personas[i];
		// Mientras queden al menos dos personas en cruzar, se incrementa el tiempoTotal con el menorTiempo (regresa la linterna)
		if(i < personas.size() - 1)
			tiempoTotal += menorTiempo;
	}

	return tiempoTotal;
}

int main(int argc, char** argv) {
	vector<int> personas = {10, 2, 1, 5};
	int tiempoTotal = crossingTheBridge(personas);
	cout << "El tiempo total para cruzar el puente es " << tiempoTotal << " minutos\n";
	return 0;
}
