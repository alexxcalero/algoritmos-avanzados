/*
 * Proyecto : EX2-2022_1-P2-B
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 22 de octubre de 2024, 11:15
 */

#include <iostream>
#include <iomanip>
#include <climits>
using namespace std;

int calcularMaximaGanancia(int precios[], int n, int k) {
	int dp[k + 1][n];

	for(int i = 0; i < n; i++) dp[0][i] = 0;
	for(int i = 0; i <= k; i++) dp[i][0] = 0;

	for(int i = 1; i <= k; i++) {
		for(int j = 1; j < n; j++) {
			int maximo = INT_MIN;

			for(int m = 0; m < j; m++)
				maximo = max(maximo, precios[j] - precios[m] + dp[i - 1][m]);

			// seleccionar entre el maximo local y maximo de todo el recorrido
			dp[i][j] = max(maximo, dp[i][j - 1]);
		}
	}

	for(int i = 0; i <= k; i++) {
		for(int j = 0; j < n; j++)
			cout << setw(5) << dp[i][j];
		cout << endl;
	}
	cout << endl;

	return dp[k][n-1];
}

int main(int argc, char** argv) {
	int precios[]={315, 322, 385, 375, 365, 380};
	int n = sizeof(precios) / sizeof(precios[0]);
	int k = 2;
	int maxGanancia = calcularMaximaGanancia(precios, n, k);
	cout << "La ganancia maxima sera " << maxGanancia << " para $100\n";
	return 0;
}
