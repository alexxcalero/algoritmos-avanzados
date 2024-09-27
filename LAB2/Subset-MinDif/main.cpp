/*
 * Proyecto : Subset-MinDif
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 20 de setiembre de 2024, 02:04
 */

#include <iostream>
#include <iomanip>
using namespace std;

int hallarMinimaDiferencia(int arr[], int n) {
	int suma = 0;
	for(int i = 0; i < n; i++) suma += arr[i];

	bool dp[n + 1][suma + 1];
	for(int i = 0; i <= n; i++) dp[i][0] = true;
	for(int j = 1; j <= suma; j++) dp[0][j] = false;

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= suma; j++) {
			dp[i][j] = dp[i - 1][j];
			if(j >= arr[i - 1] && dp[i][j] == false)
				dp[i][j] = dp[i - 1][j - arr[i - 1]];
		}
	}

	cout << "      ";
	for(int i = 1; i <= suma; i++)
		cout << setw(4) << i;
	cout << endl << "      --------------------------------------------";
	cout << "-------------------------------------------------" << endl;

	for(int i = 1; i <= n; i++) {
		cout << setw(4) << arr[i - 1] << " |";
		for(int j = 1; j <= suma; j++)
			if(dp[i][j] == true) cout << setw(4) << 'T';
			else cout << setw(4) << 'F';
		cout << endl;
	}
	cout << endl;

	for(int i = suma / 2; i >= 0; i--) {
		if(dp[n][i] == true) {
			return suma - 2 * i;
		}
	}
}

int main(int argc, char** argv) {
	int arr[] = {1, 6, 11, 5};
	int n = sizeof(arr) / sizeof(arr[0]);
	int minDif = hallarMinimaDiferencia(arr, n);
	cout << "La minima diferencia entre subconjuntos con los numeros brindados es " << minDif << endl;
	return 0;
}
