/*
 * Proyecto : Subset-Suma
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 20 de setiembre de 2024, 01:39
 */

#include <iostream>
#include <iomanip>
using namespace std;

bool buscarSuma(int arr[], int n, int peso) {
	bool dp[n + 1][peso + 1];
	for(int fila = 0; fila <= n; fila++)
		dp[fila][0] = true;
	for(int col = 1; col <= peso; col++)
		dp[0][col] = false;

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= peso; j++) {
			dp[i][j] = dp[i - 1][j];
			if(j >= arr[i - 1] && dp[i - 1][j] == false) {
				dp[i][j] = dp[i - 1][j - arr[i - 1]];
			}
		}
	}

	cout << "      ";
	for(int i = 1; i <= peso; i++)
		cout << setw(4) << i;
	cout << endl << "       ----------------------------------------" << endl;

	for(int i = 1; i <= n; i++) {
		cout << setw(4) << arr[i - 1] << " |";
		for(int j = 1; j <= peso; j++) {
			if(dp[i][j] == true) cout << setw(4) << 'T';
			else cout << setw(4) << 'F';
		}
		cout << endl;
	}
	cout << endl;

	// Tiene la respuesta de si se puede formar o no la suma deseada
	return dp[n][peso];
}

int main(int argc, char** argv) {
	int arr[] = {3, 5, 7};
	int n = sizeof(arr) / sizeof(arr[0]);
	int peso = 10;
	if(buscarSuma(arr, n, peso))
		cout << "Si se pudo conseguir el peso de " << peso << endl;
	else
		cout << "No se pudo conseguir el peso de " << peso << endl;
	return 0;
}
