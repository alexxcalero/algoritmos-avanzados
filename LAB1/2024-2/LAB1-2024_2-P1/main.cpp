/*
 * Proyecto : LAB1-2024_2-P1
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 7 de septiembre de 2024, 09:25
 */

#include <iostream>
#define MAX 10
using namespace std;

int sol[MAX];
int ind = 0;
int cantSol = 0;

// Realiza la maximizacion y minimizacion que piden
bool verificar(int costoSumado, int pesoSumado, double &miniMaxi) {
	if((double)costoSumado / pesoSumado < miniMaxi) {
		miniMaxi = (double)costoSumado / pesoSumado;
		return true;
	}
	else
		return false;
}

bool lavarRopa(int peso, int cantInternos, int costo, int ropa[], double miniMaxi, int i) {
	if(i == cantInternos || peso < 0)
		return false;

	if(peso == ropa[i] && verificar(ropa[i]*costo, ropa[i], miniMaxi)) {
		sol[ind] = i;
		cantSol++;
		cout << "Solucion " << cantSol << ": ";
		for(int k = 0; k <= ind; k++)
			cout << sol[k] << " ";
		cout << endl;
		return true;
	}

	sol[ind] = i;
	ind++;
	if(verificar(ropa[i]*costo, ropa[i], miniMaxi) && lavarRopa(peso - ropa[i], cantInternos, costo, ropa, miniMaxi, i + 1))
		return true;
	else {
		ind--;
		return lavarRopa(peso, cantInternos, costo, ropa, miniMaxi, i + 1);
	}
}

int main(int argc, char** argv) {
	int p = 5;
	int q = 50;
	int interno[] = {6, 7, 4, 5, 2};
	int costo[] = {5, 6, 8, 5, 9};
	int ropa[p][MAX] = {
		{14, 11, 10, 19, 14, 11},
		{20, 11, 11, 10, 15, 17, 8},
		{15, 16, 15, 16},
		{11, 4, 19, 12, 10},
		{18, 12}
	};

	for(int i = 0; i < p; i++) {
		double miniMaxi = 9999;
		lavarRopa(q, interno[i], costo[i], ropa[i], miniMaxi, 0);
		if(cantSol > 0)
			cout << "Se pudo lavar la ropa de ciertos internos\n";
		else
			cout << "No se pudo lavar la ropa de los internos\n";
	}

	return 0;
}
