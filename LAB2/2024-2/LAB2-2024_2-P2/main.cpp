/*
 * Proyecto : LAB2-2024_2-P2
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 21 de setiembre de 2024, 08:17
 */

#include <iostream>
#include <iomanip>
using namespace std;

int calcularMaximaGanancia(int precios[], int n) {
    int dp[n + 1][n + 1];
    for(int i = 0; i <= n; i++) dp[i][0] = 0;  // Inicializo la primera columna en cero
    for(int j = 0; j <= n; j++) dp[0][j] = 0;  // Inicializo la primera fila en cero

    // Voy a ir evaluando cada posicion de la matriz
    for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if(j < i)  // Si la longitud de la barra es menor a la longitud del corte
				dp[i][j] = dp[i - 1][j];  // Simplemente copiamos lo de arriba
			else {
				int max = dp[i - 1][j];  // Asumo el maximo, como la ganancia guardada hasta ese momento
				int aux = precios[i - 1] + dp[i][j - i];  // La posible nueva mayor ganancia (formula del enunciado)

				if(aux > max) max = aux;  // Verifico cual es mayor

				dp[i][j] = max;  // El maximo se guarda en la posicion actual de la matriz de solucion
			}
		}
    }

    // Imprimo la matriz de solucion
    for(int i = 0; i <= n; i++) {
		for(int j = 0; j <= n; j++)
			cout << setw(5) << dp[i][j];
		cout << endl;
    }
	cout << endl;

    // La respuesta estara en la esquina inferior derecha -> dp[n][n]
    return dp[n][n];
}

int main(int argc, char** argv) {
	int precios[] = {2, 5, 7, 8};
    int n = sizeof(precios) / sizeof(precios[0]);
    int maxGanancia = calcularMaximaGanancia(precios, n);
    cout << "La maxima ganancia que se puede obtener es " << maxGanancia << endl;
	return 0;
}
