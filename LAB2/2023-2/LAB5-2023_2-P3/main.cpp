/*
 * Proyecto : LAB5-2023_2-P3
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 21 de setiembre de 2024, 00:48
 */

#include <iostream>
#include <iomanip>
using namespace std;

int calcularTiempoMaximo(int tiempos[], int n, int r) {
	int dp[r + 1][n + 1];

	for(int i = 0; i <= r; i++)
		for(int j = 0; j <= n; j++)
			dp[i][j] = 9999;

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
	int tiempos[] = {55, 70, 30, 50, 20};
	int n = sizeof(tiempos) / sizeof(tiempos[0]);
	int r = 3;
	int tiempoMax = calcularTiempoMaximo(tiempos, n, r);
	cout << "El tiempo maximo que utilizarian " << r << " robots seria " << tiempoMax << " minutos\n";
	return 0;
}
