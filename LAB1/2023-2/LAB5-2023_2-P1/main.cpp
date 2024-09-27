/*
 * Proyecto : LAB5-2023_2-P1
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 7 de setiembre de 2024, 01:35
 */

#include <iostream>
#include <iomanip>
#define N 10
#define NO_ENCONTRADO -1
using namespace std;

int mov[][2] ={
	{1,0},
	{0,1}
};

void imprimirMatriz(int matN[N][N], int matL[N][N], int n) {
	cout << "Matriz de solucion:\n";
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++)
			cout << setw(2) << matN[i][j] << '(' << char(matL[i][j]) << ')' << ' ';
		cout << '\n';
	}
	cout << '\n';
}

bool validarPedidos(int pedN[], int pedL[], int c) {
	int cont = 0;
	for(int i = 0; i < c; i++) {
		if(pedN[i] == 0 && char(pedL[i]) == '0') {
			cont++;
		}
	}
	if(cont == c)
		return true;
	else
		return false;
}

bool validarMovimiento(int x,int y,int n,int solN[][N], int solL[][N]) {
	if(x >= 0 && y >= 0 && x < n && y < n && solN[x][y] == 0 && char(solL[x][y]) == '0')
		return true;
	else
		return false;
}

int esUnPesoBuscado(int pedN[],int pedL[],int c,int valorN,int valorL) {
	for(int i = 0; i < c; i++) {
		if(valorN == pedN[i] && valorL == pedL[i]) {
			pedN[i] = 0;
			pedL[i] = '0';
			return i;
		}
	}
	return NO_ENCONTRADO;
}

bool sePuedeDespachar(int almN[][N],int almL[][N],int pedN[],int pedL[],
					  int solN[][N],int solL[][N],int n,int c,
					  int x,int y) {
	if(x == N || y == n)
		return false;

	if(validarPedidos(pedN, pedL, c)) {
		imprimirMatriz(solN, solL, n);
		return true;
	}

	for(int i = 0; i < 2; i++) {
		int xN = x + mov[i][0];
		int yN = y + mov[i][1];
		if(validarMovimiento(xN,yN,n,solN,solL)) {
			int indice = esUnPesoBuscado(pedN,pedL,c,almN[xN][yN],almL[xN][yN]);
			if(indice != NO_ENCONTRADO) {
				solN[xN][yN] = almN[xN][yN];
				solL[xN][yN] = almL[xN][yN];
				if(sePuedeDespachar(almN,almL,pedN,pedL,solN,solL,n,c,xN,yN))
					return true;
				solN[xN][yN] = 0;
				solL[xN][yN] = '0';
				pedN[indice] = almN[xN][yN];
				pedL[indice] = almL[xN][yN];
			} else {
				if(sePuedeDespachar(almN,almL,pedN,pedL,solN,solL,n,c,x + 1,y))
					return true;
				if(sePuedeDespachar(almN,almL,pedN,pedL,solN,solL,n,c,x,y + 1))
					return true;
			}
		}
	}

	return false;
}

int main(int argc, char** argv) {
	int n = 5, c = 4;
	int pedN[c] = {5, 1, 50, 8};
	int pedL[c] = {'A', 'V', 'M', 'A'};
	int almN[N][N] = {
		{20, 10, 10, 25, 10},
		{10, 1 , 10, 5 , 15},
		{1 , 20, 50, 5 , 1 },
		{25, 10, 8 , 5 , 15},
		{10, 2 , 8 , 10, 10}
	};
	int almL[N][N] = {
		{'A', 'V', 'A', 'M', 'M'},
		{'A', 'V', 'M', 'A', 'V'},
		{'V', 'M', 'M', 'M', 'A'},
		{'V', 'A', 'A', 'A', 'V'},
		{'M', 'M', 'M', 'M', 'A'}
	};

	//imprimirMatriz(almN, almL, n);

	int solN[N][N];
	int solL[N][N];

	// Inicializo ambas matrices de solucion
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			solN[i][j] = 0;
			solL[i][j] = '0';
		}
	}
	//imprimirMatriz(solN, solL, n);

	// Verifico la posicion (0,0)
	for(int i = 0; i < c; i++) {
		if(almN[0][0] == pedN[i] && almL[0][0] == pedL[i]) {
			solN[0][0] = almN[0][0];
			solL[0][0] = almL[0][0];
			pedN[i] = 0;
			pedL[i] = '0';
			break;
		}
	}

	// Ahora hago el backtracking
	if(sePuedeDespachar(almN,almL,pedN,pedL,solN,solL,n,c,0,0))
		cout << "Se puedieron despachar los pedidos solicitados\n";
	else
		cout << "No se pudo despachar los pedidos solicitados\n";

	return 0;
}
