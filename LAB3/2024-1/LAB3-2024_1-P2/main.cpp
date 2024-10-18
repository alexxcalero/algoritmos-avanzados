/*
 * Proyecto : LAB3-2024_1-P2
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 4 de octubre de 2024, 14:22
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include "Paquete.h"
using namespace std;

// Estamos comparando por la condicion brindada en el enunciado:
//  - Maximizar la ganancia y minimizar el peso -> Ganancia / Peso
bool compara(const Paquete &a, const Paquete &b) {
	return (double)a.GetGanancia() / a.GetPeso() > (double)b.GetGanancia() / b.GetPeso();
}

void empacar(int peso, vector<Paquete> &paquetes) {
	int ganancia = 0;
	int sobrante = peso;
	sort(paquetes.begin(), paquetes.end(), compara);

	for(int i = 0; i < paquetes.size(); i++) {
		if(sobrante >= paquetes[i].GetPeso()) {
			sobrante -= paquetes[i].GetPeso();
			ganancia += paquetes[i].GetGanancia();
		}
	}

	cout << "Peso sobrante en el contenedor: " << sobrante << " toneladas\n";
	cout << "Ganancia de la exportacion: " << ganancia << ",000 dolares\n";
}

int main(int argc, char** argv) {
//	vector<Paquete> paquetes = {Paquete(2, 10), Paquete(3, 15), Paquete(5, 10), Paquete(12, 24), Paquete(2, 8)};
//	int peso = 16;
	vector<Paquete> paquetes = {Paquete(2, 10), Paquete(3, 15), Paquete(5, 10), Paquete(12, 24), Paquete(2, 8), Paquete(5, 5)};
	int peso = 20;
	empacar(peso, paquetes);
	return 0;
}
