/*
 * Proyecto : LIS
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 20 de setiembre de 2024, 00:43
 */

#include <iostream>
#include <iomanip>
using namespace std;

int lis(int arr[], int n) {
	int max = 1;
	int f[n];
	for(int i = 0; i < n; i++) {
		f[i] = 1;

		for(int j = 0; j < i; j++)
			if(arr[i] > arr[j] && f[j] + 1 > f[i])
				f[i] = f[j] + 1;

		if(f[i] > max)
			max = f[i];
	}

	cout << "Valores   :";
	for(int i = 0; i < n; i++)
		cout << setw(4) << arr[i];
	cout << "\nIncremento:";
	for(int i = 0; i < n; i++)
		cout << setw(4) << f[i];
	cout << endl;

	return max;
}

int main(int argc, char** argv) {
	int arr[] = {-7, 10, 9, 2, 10, 15, 3, 20};
	int n = sizeof(arr) / sizeof(arr[0]);
	int maxSecuencia = lis(arr, n);
	cout << "La maxima secuencia incremental que se puede formar es " << maxSecuencia << endl;
	return 0;
}
