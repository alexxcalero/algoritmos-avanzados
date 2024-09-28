/*
 * Proyecto : LAB2-2024_1-P1
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 21 de setiembre de 2024, 01:11
 */

#include <iostream>
using namespace std;

bool sePuedeDarVuelto(int billetes[], int n, int monto) {
	int dp[n + 1][monto + 1];
	for(int i = 0; i <= n; i++) dp[i][0] = true;
	for(int j = 1; j <= monto; j++) dp[0][j] = false;

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= monto; j++) {
			dp[i][j] = dp[i - 1][j];
			if(j >= billetes[i - 1] && dp[i][j] == false)
				dp[i][j] = dp[i - 1][j - billetes[i - 1]];
		}
	}

//	for(int i = 1; i <= n; i++) {
//		for(int j = 1; j <= monto; j++) {
//			if(dp[i][j] == true) cout << "T ";
//			else cout << "F ";
//		}
//		cout << endl;
//	}

	return dp[n][monto];
}

int main(int argc, char** argv) {
	int billetes[] = {20, 20, 50, 50, 50, 100};
	int n = sizeof(billetes) / sizeof(billetes[0]);
	int monto = 270;
	if(sePuedeDarVuelto(billetes, n, monto))
		cout << "Si se puede entregar el vuelto\n";
	else
		cout << "No se puede entregar el vuelto\n";
	return 0;
}
