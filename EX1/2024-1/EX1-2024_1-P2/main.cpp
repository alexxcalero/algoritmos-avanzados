/*
 * Proyecto : EX1-2024_1-P2
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 13 de octubre de 2024, 14:56
 */

#include <iostream>
using namespace std;

int calcularFormas(int monedas[], int monto, int n) {
	int dp[n + 1][monto + 1];
	for(int i = 0; i <= n; i++) dp[i][0] = 1;
	for(int j = 1; j <= monto; j++) dp[0][j] = 0;

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= monto; j++) {
			if(j < monedas[i - 1]) {
				dp[i][j] = dp[i - 1][j];
			} else {
				dp[i][j] = dp[i - 1][j] + dp[i][j - monedas[i - 1]];
			}
		}
	}

	for(int i = 0; i <= n; i++) {
		for(int j = 0; j <= monto; j++)
			cout << dp[i][j] << " ";
		cout << endl;
	}
	cout << endl;

	return dp[n][monto];
}

int main(int argc, char** argv) {
	int monedas[] = {1, 2, 10, 20};
	int monto = 7;
	int n = sizeof(monedas) / sizeof(monedas[0]);
	int cantFormas = calcularFormas(monedas, monto, n);
	cout << "Para el monto de " << monto << " dinares, existen " << cantFormas << " formas\n";
	return 0;
}
