/*
 * Proyecto : LAB3-2024_2-P2
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 5 de octubre de 2024, 09:30
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include "Producto.h"
using namespace std;

// Mi comparacion va a comparar el tamanho del area de cada producto
bool compara(const Producto &a, const Producto &b) {
	return a.GetLongitud() * a.GetAltura() < b.GetLongitud() * b.GetAltura();
}

void fabricarLatas(vector<Producto> &productos, int L, int H) {
	sort(productos.begin(), productos.end(), compara);

	int cantLaminas = 1;
	vector<int> laminas;  // Vector de laminas utilizadas
	laminas.push_back(L * H);  // Van a contener el area disponible

	for(int i = 0; i < productos.size(); i++) {
		int areaProducto = productos[i].GetAltura() * productos[i].GetLongitud();
		int cont = 0;
		for(int j = 0; j < laminas.size();) {
			if(laminas[j] >= areaProducto) {  // Si hay area suficiente en la lamina para armar la lata
				laminas[j] -= areaProducto;  // Disminuyo el area restante
				cont++;  // Aumento el contador
			} else {  // Si ya no hay area suficiente en la lamina para armar la lata
				j++;  // Aumento el indice del vector de laminas
			}

			// Si el indice es igual a la cantidad de laminas, significa que ya no hay mas laminas,
			// por ende, agrego una nueva lamina al vector
			if(j == laminas.size()) {
				laminas.push_back(L * H);
				cantLaminas++;
			}

			// Si el contador es igual a la cantidad que se piden de una lata, breakeamos
			if(cont == productos[i].GetCantidad()) break;
		}
	}

	// Hallo la merma total
	double mermaNum = 0;
	double mermaDen = (L * H) * cantLaminas;
	for(int cant : laminas) {
		mermaNum += cant;
	}

	double merma = mermaNum / mermaDen * 100;

	cout << "La cantidad de laminas usadas es: " << cantLaminas << endl;
	cout << "El porcentaje de merma residual es: " << merma << endl;
}

int main(int argc, char** argv) {
	int L = 50, H = 50;
	vector<Producto> productos = {
		Producto(5, 2, 3),
		Producto(10, 9, 3),
		Producto(15, 14, 7),
		Producto(20, 15, 20),
		Producto(20, 22, 18)
	};
	fabricarLatas(productos, L, H);
	return 0;
}
