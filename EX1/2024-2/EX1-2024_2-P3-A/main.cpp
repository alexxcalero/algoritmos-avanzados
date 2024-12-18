/*
 * Proyecto : EX1-2024_2-P3-A
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 15 de octubre de 2024, 12:10
 */

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Esta funcion va a seleccionar el mejor conjunto para ser seleccionado.
// Esta funcion evalua cuantos elementos de un subconjunto ya han sido usados,
// por lo tanto, mientras menos usados tenga un subconjunto, sera el mejor a utilizar
int seleccionarMejorSubConjunto(vector<int> &conjunto, vector<vector<int>> &subconjuntos) {
	int minUsados = INT_MAX;
	int idMin;
	for(int i = 0; i < subconjuntos.size(); i++) {
		int usados = 0;
		for(int j = 0; j < subconjuntos[i].size(); j++) {
			bool esDif = true;
			for(int k = 0; k < conjunto.size(); k++) {
				if(conjunto[k] == subconjuntos[i][j])
					esDif = false;
			}
			if(esDif == true)
				usados++;
		}
		if(usados < minUsados) {
			minUsados = usados;
			idMin = i;
		}
	}
	return idMin;
}

void tacharDelConjunto(vector<int> &conjunto, vector<int> &subconjunto) {
	for(int i = 0; i < conjunto.size(); i++) {
		for(int j = 0; j < subconjunto.size(); j++) {
			if(conjunto[i] == subconjunto[j]) {
				conjunto[i] = -1;
				break;
			}
		}
	}
}

bool completeConjunto(vector<int> &conjunto) {
	for(int i = 0; i < conjunto.size(); i++)
		if(conjunto[i] != -1)
			return false;
	return true;
}

void seleccionarConjuntos(vector<int> &conjunto, vector<vector<int>> &subconjuntos) {
	// matriz de solucion
	vector<vector<int>> solucion(subconjuntos.size());
	int indSol = 0;  // Indice para la matriz de solucion

	// Mientras el conjunto original no haya sido completado
	while(!completeConjunto(conjunto)) {
		// En esta parte es donde escojo el mejor subconjunto a utilizar
		int idSubElegido = seleccionarMejorSubConjunto(conjunto, subconjuntos);

		// Agrego en la solucion, el subconjunto a utilizar
		solucion[indSol] = subconjuntos[idSubElegido];

		indSol++;  // Incremento el indice de la matriz de solucion

		// Tacho del conjunto original los elementos del subconjunto que he utilizado
		tacharDelConjunto(conjunto, subconjuntos[idSubElegido]);
	}

	// Imprimo la solucion, con los subconjuntos seleccionados
	for(int i = 0; i < indSol; i++) {
		cout << "{";
		for(int j = 0; j < solucion[i].size(); j++) {
			cout << solucion[i][j] << (j + 1 == solucion[i].size() ? "} " : ", ");
		}
		//cout << endl;
	}
}

int main(int argc, char** argv) {
	vector<int> conjunto = {1, 2, 3, 4, 5, 6, 7};
	vector<vector<int>> subconjuntos = {
		{1, 2, 3},
		{2, 4, 5},
		{3, 5, 6},
		{6, 7}
	};
	seleccionarConjuntos(conjunto, subconjuntos);
	return 0;
}
