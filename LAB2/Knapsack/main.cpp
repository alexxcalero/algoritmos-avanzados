/*
 * Proyecto : Knapsack
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 20 de setiembre de 2024, 13:05
 */

#include <iostream>
#include <iomanip>
using namespace std;

int knapsack(int pesos[], int valores[], int n, int capacidad) {
	int dp[n + 1][capacidad + 1];
	for(int fila = 0; fila <= n; fila++)
		dp[fila][0] = 0;
	for(int columna = 0; columna <= capacidad; columna++)
		dp[0][columna] = 0;

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= capacidad; j++) {
			if(j < pesos[i - 1])
				dp[i][j] = dp[i - 1][j];
			else {
				int max = dp[i - 1][j];
				int aux = valores[i - 1] + dp[i - 1][j - pesos[i - 1]];
				if(aux > max)
					max = aux;
				dp[i][j] = max;
			}
		}
	}

	cout << "      ";
	for(int i = 1; i <= capacidad; i++)
		cout << setw(4) << i;
	cout << endl << "      ---------------------" << endl;

	for(int i = 1; i <= n; i++) {
		cout << setw(4) << pesos[i - 1] << " |";
		for(int j = 1; j <= capacidad; j++)
			cout << setw(4) << dp[i][j];
		cout << endl;
	}
	cout << endl;

	return dp[n][capacidad];
}

int main(int argc, char** argv) {
	int pesos[] = {2, 1, 3, 2};
	int valores[] = {12, 10, 20, 15};
	int n = sizeof(pesos) / sizeof(pesos[0]);
	int capacidad = 5;
	int maxGanancia = knapsack(pesos, valores, n, capacidad);
	cout << "La maxima ganancia que se puede obtener es " << maxGanancia << endl;
	return 0;
}
