/*
 * Proyecto : Coinrow
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 20 de setiembre de 2024, 00:20
 */

#include <iostream>
#include <iomanip>
using namespace std;

int coinrow(int monedas[], int n) {
	int f[n + 1];  // Arreglo de resultados;
	f[0] = 0;  // Seteo la primera posicion del arreglo en cero
	f[1] = monedas[0];  // Seteo la segunda posicion del arreglo con el primer valor del arreglo de monedas
	for(int i = 2; i <= n; i++) {
		int max = f[i - 1];  // El maximo actual es la posicion anterior en el arreglo de solucion
		int aux = monedas[i - 1] + f[i - 2];  // El posible nuevo maximo
		if(aux > max)
			max = aux;
		f[i] = max;  // Se asigna el valor maximo en la posicion actual del arreglo
	}

	cout << "Monedas  :";
	for(int i = 1; i <= n; i++)
		cout << setw(4) << monedas[i - 1];
	cout << "\nAcumulado:";
	for(int i = 1; i <= n; i++)
		cout << setw(4) << f[i];
	cout << endl;

	return f[n];  // La respuesta (el maximo valor) se encontrara en la ultima posicion del arreglo
}

int main(int argc, char** argv) {
	int monedas[] = {5, 1, 2, 10, 6, 2};
	int n = sizeof(monedas) / sizeof(monedas[0]);
	int max = coinrow(monedas, n);
	cout << "El valor maximo que se puede formar es " << max << endl;
	return 0;
}
