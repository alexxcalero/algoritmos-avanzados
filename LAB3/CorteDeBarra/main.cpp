/*
 * Proyecto : CorteDeBarra
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 5 de octubre de 2024, 00:22
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include "Pedido.h"
using namespace std;

bool compara(const Pedido &a, const Pedido &b) {
	return a.GetGanancia() > b.GetGanancia();
}

void corteDeBarra(vector<Pedido> &pedidos, vector<int> &barras) {
	sort(pedidos.begin(), pedidos.end(), compara);
	int ganancia = 0;
	for(int i = 0; i < pedidos.size(); i++) {
		int cont = 0;
		for(int j = 0; j < barras.size();) {
			if(barras[j] >= pedidos[i].GetDimension()) {
				barras[j] -= pedidos[i].GetDimension();
				cont++;
			} else {
				j++;
			}
			if(cont == pedidos[i].GetCantidad()) {
				ganancia += pedidos[i].GetGanancia();
				break;
			}
		}
	}
	cout << "Ganancia: $ " << ganancia << " k\n";
	cout << "Desperdicio de barras utilizadas:\n";
	for(int i = 0; i < barras.size(); i++) {
		cout << barras[i] << " ";
	}
}

int main(int argc, char** argv) {
	vector<Pedido> pedidos = {Pedido(10, 5, 10), Pedido(20, 10, 20), Pedido(1, 18, 15), Pedido(3, 1, 5), Pedido(1, 1, 2)};
	vector<int> barras(20, 10);
	corteDeBarra(pedidos, barras);
	return 0;
}
