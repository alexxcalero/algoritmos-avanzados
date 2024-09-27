/*
 * Proyecto : LAB1-2024_2-P2
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 7 de septiembre de 2024, 08:14
 */

#include <iostream>
#include <iomanip>
#define MAX 10
using namespace std;

int cantSol = 0;

bool validarProductos(int prod[], int n) {
	int ceros = 0;

	for(int i = 0; i < n; i++)
		if(prod[i] == 0)
			ceros++;

	if(ceros == n)
		return true;
	else
		return false;
}

bool almacenar(int prod[], int cap[], int sol[], int n, int m, int p) {
	if(p == n && validarProductos(prod, n)) {
		cantSol++;
		cout << "Solucion " << setw(2) << cantSol << ": ";
		for(int i = 0; i < m; i++)
			cout << sol[i] << " ";
		cout << endl;
		//return true;  // Descomentar el return true para mostrar una sola solucion
	}

	bool colocado;
	int guardado;
	for(int i = 0; i < m; i++) {
		colocado = false;
		if(prod[p] + sol[i] <= cap[i] && colocado == false) {
			colocado = true;
			sol[i] += prod[p];  // Guardo el peso del producto en el arreglo de soluciones
			guardado = prod[p];  // Guardo el valor del producto por si tengo que realizar back
			prod[p] = 0;  // Chanco con cero en la posicion correspondiente en el arreglo de productos
			if(almacenar(prod, cap, sol, n, m, p + 1))
				return true;
			prod[p] = guardado;  // Vuelvo a poner el peso del producto en el arreglo
			sol[i] -= prod[p];   // Quito el producto del rack donde se puso
		}
	}

	return false;
}

int main(int argc, char** argv) {
	int n = 4, m = 5;
	int prod[] = {2, 3, 1, 4};
	int cap[] = {3, 2, 5, 1, 3};
	int sol[] = {0, 0, 0, 0, 0};

	almacenar(prod, cap, sol, n, m, 0);

	if(cantSol > 0)
		cout << "Si se almacenaron todos los productos\n";
	else
		cout << "No se pudo almacenar todos los productos\n";

	return 0;
}
