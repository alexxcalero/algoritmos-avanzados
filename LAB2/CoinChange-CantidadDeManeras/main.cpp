/*
 * Proyecto : CoinChange-CantidadDeManeras
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 20 de setiembre de 2024, 22:10
 */

/* Link al video explicativo: https://youtu.be/L27_JpN6Z1Q */

#include <iostream>
#include <iomanip>
using namespace std;

int coinChangeNumWays(int monedas[], int n, int cantidad) {
	int dp[n + 1][cantidad + 1];
	for(int i = 0; i <= n; i++) dp[i][0] = 1;
	for(int j = 1; j <= cantidad; j++) dp[0][j] = 0;

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= cantidad; j++) {
			if(j < monedas[i - 1])
				dp[i][j] = dp[i - 1][j];
			else {
				dp[i][j] = dp[i - 1][j] + dp[i][j - monedas[i - 1]];
			}
		}
	}

	cout << "      ";
	for(int i = 1; i <= cantidad; i++)
		cout << setw(4) << i;
	cout << endl << "      ---------------------------------";
	cout << "----------------------------" << endl;

	for(int i = 1; i <= n; i++) {
		cout << setw(4) << monedas[i - 1] << " |";
		for(int j = 1; j <= cantidad; j++)
			cout << setw(4) << dp[i][j];
		cout << endl;
	}
	cout << endl;

	return dp[n][cantidad];
}

int main(int argc, char** argv) {
	int monedas[] = {2, 3, 5, 10};
	int n = sizeof(monedas) / sizeof(monedas[0]);
	int cantidad = 15;
	int cantManeras = coinChangeNumWays(monedas, n, cantidad);
	cout << "Se puede formar " << cantidad << " de " << cantManeras << " maneras\n";
	return 0;
}
