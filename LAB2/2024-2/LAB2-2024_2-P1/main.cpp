/*
 * Proyecto : LAB2-2024_2-P1
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 21 de setiembre de 2024, 08:32
 */

#include <iostream>
#include <iomanip>
#include <climits>
using namespace std;

int calcularAterrizajes(int arr[], int n) {
	int f[n];  // Arreglo de solucion
	for(int i = 0; i < n; i++) f[i] = INT_MAX;  // Inicializo con un numero muy grande para no tener problema al comparar
	f[0] = 0;  // En la primera posicion tengo cero aterrizajes

	for(int i = 1; i < n; i++) {
		for(int j = 0; j < i; j++) {
			// Si el combustible me alcanza para llegar a la ciudad actual,
			// hago la asignacion verificando el minimo, en caso contrario,
			// no se va a evaluar
			if(arr[j] - (i - j) >= 0)
				f[i] = min(f[i], f[j] + 1);
		}
	}

	cout << "Ciudad     :";
	for(int i = 0; i < n; i++)
		cout << setw(4) << i + 1;

	cout << endl;

	cout << "Aterrizajes:";
	for(int i = 0; i < n; i++)
		cout << setw(4) << f[i];
	cout << endl;

	// La solucion esta en la ultima posicion del arreglo
	return f[n - 1];
}

int main(int argc, char** argv) {
	//int arr[] = {5, 2, 1, 4, 1};
	//int arr[] = {1, 2, 1, 4, 2, 3};
	int arr[] = {1, 2, 1, 4, 2, 3, 5, 2, 4, 2, 6};
	int n = sizeof(arr) / sizeof(arr[0]);
	int aterrizajes = calcularAterrizajes(arr, n);
	cout << "Se necesita " << aterrizajes << " aterrizajes para llegar a la ciudad " << n << endl;
	return 0;
}
