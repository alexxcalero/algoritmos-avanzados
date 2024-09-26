/*
 * Proyecto : LAB5-2020_2-P1
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 6 de setiembre de 2024, 21:13
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#define N 10
using namespace std;

int movimiento[2][2] = {
	{1, 0},  // Abajo
	{0, 1}   // Derecha
};

void leerDatos(int &n, int &c, int pedido[], int almacen[N][N], int solucion[N][N]) {
	ifstream arch("datos.txt", ios::in);
	if(!arch.is_open()) {
		cout << "ERROR: No se pudo abrir el archivo de datos\n";
		exit(1);
	}
	arch >> n >> c;

	for(int i = 0; i < c; i++)
		arch >> pedido[i];

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) {
			arch >> almacen[i][j];
			solucion[i][j] = 0;
		}
}

void imprimirArreglos(int pedido[], int almacen[N][N], int c, int n) {
	for(int i = 0; i < c; i++)
		cout << setw(4) << pedido[i] << " ";

	cout << endl << endl;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++)
			cout << setw(4) << almacen[i][j] << " ";
		cout << endl;
	}
}

bool validarPedidos(int pedido[], int cantPed) {
	int cantCeros = 0;
	for(int i = 0; i < cantPed; i++)
		if(pedido[i] == 0)
			cantCeros++;

	if(cantCeros == cantPed)
		return true;
	else
		return false;
}

bool validarMovimiento(int x, int y, int n, int solucion[N][N]) {
	if(x >= 0 && x < n && y >= 0 && y < n && solucion[x][y] == 0)
		return true;
	else
		return false;
}

int seBusca(int pedido[], int cantPed, int valor) {
	for(int i = 0; i < cantPed; i++) {
		if(pedido[i] == valor) {
			pedido[i] = 0;
			return i;
		}
	}
	return -1;
}

void imprimirMatriz(int solucion[N][N], int n) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++)
			cout << setw(4) << solucion[i][j];
		cout << endl;
	}
	cout << endl;
}

bool sePuedeDespachar(int pedido[], int almacen[N][N], int solucion[N][N], int cantPed, int n, int x, int y) {
	if(x == n || y == n)
		return false;

	if(validarPedidos(pedido, cantPed)) {
		cout << "Matriz de solucion:\n";
		imprimirMatriz(solucion, n);
		return true;
	}

	for(int i = 0; i < 2; i++) {
		int nx = x + movimiento[i][0];
		int ny = y + movimiento[i][1];
		if(validarMovimiento(nx, ny, n, solucion)) {
			int indice = seBusca(pedido, cantPed, almacen[nx][ny]);
			if(indice != -1) {
				solucion[nx][ny] = almacen[nx][ny];
				if(sePuedeDespachar(pedido, almacen, solucion, cantPed, n, nx, ny))
					return true;
				pedido[indice] = almacen[nx][ny];
				solucion[nx][ny] = 0;
			} else {
				if(sePuedeDespachar(pedido, almacen, solucion, cantPed, n, x + 1, y))
					return true;
				if(sePuedeDespachar(pedido, almacen, solucion, cantPed, n, x, y + 1))
					return true;
			}
		}
	}

	return false;
}

int main(int argc, char** argv) {
	int n, c;
	int pedido[N], almacen[N][N], solucion[N][N];

	leerDatos(n, c, pedido, almacen, solucion);
//	imprimirArreglos(pedido, almacen, c, n);

	// Verifico antes de entrar en la recursion la primera posicion del almacen
	for(int i = 0; i < c; i++) {
		if(pedido[i] == almacen[0][0]) {  // El pedido esta en el almacen
			solucion[0][0] = pedido[i];  // Marco en la matriz de solucion
			pedido[i] = 0;  // Marco con cero en el arreglo de pedidos
			break;
		}
	}

	if(sePuedeDespachar(pedido, almacen, solucion, c, n, 0, 0))
		cout << "Se despacharon los pedidos solicitados\n";
	else
		cout << "No se pudo despachar los pedidos solicitados\n";

	return 0;
}
