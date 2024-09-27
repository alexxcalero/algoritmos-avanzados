/*
 * Proyecto : Fibonacci
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 19 de setiembre de 2024, 23:56
 */

#include <iostream>
#include <iomanip>
using namespace std;

long long fibonacci(int indice) {
	long long fib[indice + 1];  // Arreglo para almacenar los valores de la sucesion
	fib[0] = 0;  // Seteo la primera posicion del arreglo en cero
	fib[1] = 1;  // Seteo la segunda posicion del arreglo en uno
	for(int i = 2; i <= indice; i++)
		fib[i] = fib[i - 1] + fib[i - 2];  // Formula de Fibonacci <- Aqui se utiliza PD

	for(int i = 1; i <= indice; i++)
		cout << "Indice: " << setw(3) << i << " -> Valor: " << setw(3) << fib[i] << endl;

	return fib[indice];  // La respuesta estara en la ultima posicion del arreglo
}

int main(int argc, char** argv) {
	int indice = 12;
	long long fib = fibonacci(indice);
	cout << "El numero con indice " << indice << " en la serie de Fibonacci es " << fib << endl;
	return 0;
}
