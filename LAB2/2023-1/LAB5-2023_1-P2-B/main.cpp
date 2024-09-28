/*
 * Proyecto : LAB5-2023_1-P2-B
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 21 de setiembre de 2024, 01:06
 */

#include <iostream>
#include <iomanip>
#include <climits>
using namespace std;

int calcularTiempoMaximo(int tiempos[], int n, int r) {
	int dp[r + 1][n + 1];

	for(int i = 0; i <= r; i++)
		for(int j = 0; j <= n; j++)
			dp[i][j] = INT_MAX;

	for(int i = 0; i <= r; i++) dp[i][0] = 0;

	for(int i = 1; i <= r; i++) {
		for(int j = 1; j <= n; j++) {
			int suma = 0;
			for(int k = j; k > 0; k--) {
				suma += tiempos[k - 1];
				dp[i][j] = min(dp[i][j], max(suma, dp[i - 1][k - 1]));
			}
		}
	}

	for(int i = 1; i <= r; i++) {
		for(int j = 1; j <= n; j++)
			cout << setw(5) << dp[i][j];
		cout << endl;
	}
	cout << endl;

	return dp[r][n];
}

int main(int argc, char** argv) {
	int tiempos[] = {10, 25, 40, 45, 60};
	int n = sizeof(tiempos) / sizeof(tiempos[0]);
	int r = 3;
	int tiempoMax = calcularTiempoMaximo(tiempos, n, r);
	cout << "El tiempo maximo si se divide la linea en " << r << " es de " << tiempoMax << " horas\n";
	return 0;
}
