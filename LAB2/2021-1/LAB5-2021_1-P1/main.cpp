/*
 * Proyecto : LAB5-2021_1-P1
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 20 de setiembre de 2024, 15:20
 */

#include <iostream>
#include <iomanip>
using namespace std;

int calcularGanancia(int ganancias[], int n) {
	int f[n + 2];
	f[0] = 0;
	f[1] = 0;
	f[2] = ganancias[0];
	for(int i = 3; i <= n + 1; i++) {
		int max = f[i - 1];
		int aux = ganancias[i - 2] + f[i - 3];
		if(aux > max)
			max = aux;
		f[i] = max;
	}

	cout << "Proyecto          :";
	for(int i = 2; i <= n + 1; i++)
		cout << setw(5) << i - 1;
	cout << "\nGanancia Acumulada:";
	for(int i = 2; i <= n + 1; i++)
		cout << setw(5) << f[i];
	cout << endl;

	return f[n + 1];
}

int main(int argc, char** argv) {
	int ganancias[] = {3, 6, 1, 2, 4, 5, 18, 10, 13, 7, 15, 2};
	int n = sizeof(ganancias) / sizeof(ganancias[0]);
	int maxGanancia = calcularGanancia(ganancias, n);
	cout << "La maxima ganancia que se puede formar es " << maxGanancia << ",000$\n";
	return 0;
}
