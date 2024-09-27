/*
 * Proyecto : CoinChange-MinimaCantidad
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 20 de setiembre de 2024, 22:29
 */

/* Link al video explicativo: https://youtu.be/J2eoCvk59Rc */

#include <iostream>
#include <iomanip>
#include <climits>
using namespace std;

int coinChangeMinCoins(int monedas[], int n, int cantidad) {
	int dp[n + 1][cantidad + 1];
	for(int i = 0; i <= n; i++) dp[i][0] = 0;
	for(int j = 1; j <= cantidad; j++) dp[0][j] = INT_MAX;  // Lo inicializo con un numero muy grande para no tener problemas

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= cantidad; j++) {
			if(j < monedas[i - 1])
				dp[i][j] = dp[i - 1][j];
			else {
				int min = dp[i - 1][j];
				int aux = 1 + dp[i][j - monedas[i - 1]];
				if(aux < min)
					min = aux;
				dp[i][j] = min;
			}
		}
	}

	cout << "      ";
	for(int i = 1; i <= cantidad; i++)
		cout << setw(4) << i;
	cout << endl << "      -----------------------------------------" << endl;

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
	int monedas[] = {1, 5, 6, 9};
	int n = sizeof(monedas) / sizeof(monedas[0]);
	int cantidad = 10;
	int cantMonedas = coinChangeMinCoins(monedas, n, cantidad);
	cout << "Se puede formar " << cantidad << " con " << cantMonedas << " monedas\n";
	return 0;
}
