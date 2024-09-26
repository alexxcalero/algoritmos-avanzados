/*
 * Proyecto : Binpacking
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 5 de setiembre de 2024, 23:34
 */

#include <iostream>
using namespace std;

int soluciones[10];      // Arreglo de soluciones
int ind = 0;             // Indice del arreglo de soluciones
int cantSoluciones = 0;  // Cantidad de soluciones

bool buscarSoluciones(int paquetes[], int i, int n, int peso) {
	// Si ya pasamos por todos los paquetes (nos salimos del arreglo) o el peso
	// es negativo (escogimos paquetes que no debiamos), se retorna 0
	if(i == n || peso < 0)
		return false;

	// El peso justo es igual al paquete que vamos a tomar, significa que ya
	// completamos el peso pedido y por lo tanto encontramos una solucion
	if(peso == paquetes[i]) {
		soluciones[ind] = paquetes[i];
		cantSoluciones++;
		cout << "Solucion " << cantSoluciones << ": ";
		for(int k = 0; k <= ind; k++)
			cout << soluciones[k] << " ";
		cout << endl;
		//return true;
		return false;  // Comentar esta linea, y descomentar la linea de arriba si quiero mostrar una sola solucion
	}

	// Guardamos el paquete en el arreglo de soluciones, ya que vamos a asumir que
	// este nos dara una solucion para el problema
	soluciones[ind] = paquetes[i];
	ind++;
	// Mandamos la recursion asumiendo que el peso que vamos a tomar va a dar
	// una solucion correcta, por tal motivo restamos: peso - peso[i]
	if(buscarSoluciones(paquetes, i + 1, n, peso - paquetes[i]))
		return true;
	else {  // Realizamos el back
		ind--;  // Disminuimos en uno el indice del arreglo de soluciones
		// Ya no se considera el paquete porque no dio una respuesta correcta
		return buscarSoluciones(paquetes, i + 1, n, peso);
	}
}

int main(int argc, char** argv) {
	int paquetes[] = {17, 2, 3, 5, 12};
	int peso = 20, n = 5;
	buscarSoluciones(paquetes, 0, n, peso);
	if(cantSoluciones > 0)
		cout << "Se encontro solucion\n";
	else
		cout << "No se encontro solucion\n";
	return 0;
}
