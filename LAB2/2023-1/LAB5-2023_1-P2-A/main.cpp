/*
 * Proyecto : LAB5-2023_1-P2-A
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 20 de setiembre de 2024, 14:45
 */

#include <iostream>
#include <iomanip>
using namespace std;

int calcularMayorPedido(int pedidos[], int m) {
	int max = pedidos[0];
	for(int i = 1; i < m; i++)
		if(pedidos[i] > max)
			max = pedidos[i];
	return max;
}

bool sePuedeAtender(int lotes[], int n, int pedidos[], int m) {
	int mayorPedido = calcularMayorPedido(pedidos, m);
	bool dp[n + 1][mayorPedido + 1];
	for(int i = 0; i <= n; i++) dp[i][0] = true;
	for(int j = 1; j <= mayorPedido; j++) dp[0][j] = false;

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= mayorPedido; j++) {
			dp[i][j] = dp[i - 1][j];
			if(j >= lotes[i - 1] && dp[i][j] == false)
				dp[i][j] = dp[i - 1][j - lotes[i - 1]];
		}
	}

	cout << "      ";
	for(int i = 1; i <= mayorPedido; i++)
		cout << setw(4) << i;
	cout << endl << "      ---------------------------------" << endl;

	for(int i = 1; i <= n; i++) {
		cout << setw(4) << lotes[i - 1] << " |";
		for(int j = 1; j <= mayorPedido; j++)
			if(dp[i][j] == true) cout << setw(4) << 'T';
			else cout << setw(4) << 'F';
		cout << endl;
	}
	cout << endl;

	int contador = 0;
	for(int i = 0; i < m; i++)
		// Verifico si en la matriz de solucion la casilla que corresponde al pedido
		// se encuentra en T para aumentar el contador en uno
		if(dp[n][pedidos[i]] == true)
			contador++;

	// Si el contador es igual a la cantidad de pedidos
	// significa que se pudieron entregar todos los pedidos
	if(contador == m)
		return true;
	else
		return false;
}

int main(int argc, char** argv) {
	int lotes[] = {5, 2, 8, 4};
	int n = sizeof(lotes) / sizeof(lotes[0]);
	int pedidos[] = {5, 2, 8, 4};
//	int pedidos[] = {4, 3};
	int m = sizeof(pedidos) / sizeof(pedidos[0]);
	if(sePuedeAtender(lotes, n, pedidos, m))
		cout << "Si se pueden atender los pedidos\n";
	else
		cout << "No se pueden atender los pedidos\n";
	return 0;
}
