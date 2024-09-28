/*
 * Proyecto : LAB5-2023_2-P2
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 20 de setiembre de 2024, 13:36
 */

#include <iostream>
#include <iomanip>
using namespace std;

int hallarDesperdicioMinimo(int pesos[], int n, int capacidad, int &contenedor) {
	int dp[n + 1][capacidad + 1];
	for(int i = 0; i <= n; i++) dp[i][0] = 0;  // El desperdicio para la primera columna es cero
	for(int j = 1; j <= capacidad; j++) dp[0][j] = j;  // El desperdicio para la primera fila es el valor de j

	// Tengo q ir calculando el desperdicio minimo para cada casilla
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= capacidad; j++) {
			if(j < pesos[i - 1])
				dp[i][j] = dp[i - 1][j];
			else {
				int min = dp[i - 1][j];
				int aux = dp[i - 1][j - pesos[i - 1]];
				if(aux < min)
					min = aux;
				dp[i][j] = min;
			}
		}
	}

	cout << "      ";
	for(int i = 1; i <= capacidad; i++)
		cout << setw(4) << i;
	cout << endl << "      ------------------------------------------";
	cout << "---------------------------------------" << endl;

	for(int i = 1; i <= n; i++) {
		cout << setw(4) << pesos[i - 1] << " |";
		for(int j = 1; j <= capacidad; j++)
			cout << setw(4) << dp[i][j];
		cout << endl;
	}
	cout << endl;

	for(int j = capacidad; j >= 0; j--)
		// En la ultima fila de la matriz de solucion busco la primera casilla
		// que sea cero empezando desde el final, con esto obtengo el peso
		// maximo del contenedor necesario para que el desperdicio sea cero
		if(dp[n][j] == 0) {
			contenedor = j;
			break;
		}

	// Devuelvo el desperdicio minimo para el contenedor brindado
	return dp[n][capacidad];
}

int main(int argc, char** argv) {
	int pesos[] = {3, 4, 8, 10};
	int n = sizeof(pesos) / sizeof(pesos[0]);
	int capacidad = 20;
	int contenedor;
	int minDesperdicio = hallarDesperdicioMinimo(pesos, n, capacidad, contenedor);
	cout << "El desperdicio minimo de usar un contenedor de " << capacidad;
	cout << " toneladas sera " << minDesperdicio << " toneladas\n";
	cout << "El contenedor mas grande con el desperdicio igual a 0 sera de ";
	cout << contenedor << " toneladas\n";
	return 0;
}
