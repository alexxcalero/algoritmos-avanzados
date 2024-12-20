/*
 * Proyecto : PredictAsesoriaCueva
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 9 de diciembre de 2024, 23:49
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <ctime>
#include "Paquete.h"
#define MAX_ITERA 10
#define ALFA 0.3
#define TAMANHO 7
using namespace std;

bool compara(Paquete &a, Paquete &b) {
	return a.GetTamanho() > b.GetTamanho();
}

void asignarEspacios(vector<int> &espacios, Paquete &p) {
	int ind = p.GetInicio() - 1;
	for(int i = 0; i < p.GetTamanho(); i++) {
		espacios[ind] = p.GetId();
		ind++;
	}
}

Paquete buscarPaquete(vector<Paquete> &paquetes, int ind, int n) {
	for(int i = 0; i < n; i++)
		if(paquetes[i].GetId() == ind + 1)
			return paquetes[i];
}

void imprimirEspacios(vector<int> &mejorCromosoma, vector<Paquete> &paquetes, int n) {
	vector<int> espacios(TAMANHO, 0);

	for(int i = 0; i < n; i++) {
		if(mejorCromosoma[i] == 1) {
			Paquete p = buscarPaquete(paquetes, i, n);
			asignarEspacios(espacios, p);
		}
	}

	cout << "Espacios: ";
	for(int i = 0; i < TAMANHO; i++) {
		if(espacios[i] >= 1)
			cout << espacios[i] << " ";
		else
			cout << "0 ";
	}

	cout << endl;
}

bool hayEspacio(vector<int> &cromosoma, int n, vector<Paquete> &paquetes, Paquete paq) {
	vector<int> espacios(TAMANHO, 0);

	for(int i = 0; i < n; i++) {
		if(cromosoma[i] == 1) {
			Paquete p = buscarPaquete(paquetes, i, n);
			asignarEspacios(espacios, p);
		}
	}

	int ind = paq.GetInicio() - 1;
	for(int i = 0; i < paq.GetTamanho(); i++) {
		if(espacios[ind] >= 1)
			return false;
		else {
			espacios[ind] = paq.GetId();
			ind++;
		}
	}

	return true;
}

int verifica(vector<Paquete> &auxPaquetes, double rcl) {
	int cont = 0;
	for(int i = 0; i < auxPaquetes.size(); i++)
		if(auxPaquetes[i].GetTamanho() >= rcl)
			cont++;
	return cont;
}

void seleccionarPaquetes(vector<Paquete> &paquetes, int n) {
	vector<int> mejorCromosoma(n, 0);
	int minEspacioSobrante = TAMANHO;
	int minPaqNoEnviados = n;
	srand(time(NULL));

	for(int k = 0; k < MAX_ITERA; k++) {
		vector<int> cromosoma(n, 0);
		int espaciosSobrantes = TAMANHO;
		int paqNoEnviados = n;
		vector<Paquete> auxPaquetes = paquetes;
		sort(auxPaquetes.begin(), auxPaquetes.end(), compara);

		while(!auxPaquetes.empty()) {
			int beta = auxPaquetes[0].GetTamanho();
			int tau = auxPaquetes[auxPaquetes.size() - 1].GetTamanho();
			double rcl = beta - ALFA * (beta - tau);
			int ind = verifica(auxPaquetes, rcl);
			int inda = rand() % ind;

			if(espaciosSobrantes - auxPaquetes[inda].GetTamanho() >= 0 && hayEspacio(cromosoma, n, paquetes, auxPaquetes[inda])) {
				cromosoma[auxPaquetes[inda].GetId() - 1] = 1;
				cout << auxPaquetes[inda].GetId() << endl;
				espaciosSobrantes -= auxPaquetes[inda].GetTamanho();
				paqNoEnviados--;
			}

			auxPaquetes.erase(auxPaquetes.begin() + inda);
		}

//		if(espaciosSobrantes < minEspacioSobrante) {
//			minEspacioSobrante = espaciosSobrantes;
//			mejorCromosoma = cromosoma;
//		}

		if(paqNoEnviados < minPaqNoEnviados) {
			minPaqNoEnviados = paqNoEnviados;
			mejorCromosoma = cromosoma;
		}

		cout << "---------------" << endl;
	}

//	cout << "El espacio sobrante es: " << minEspacioSobrante << endl;
	cout << "La cantidad de paquetes no enviados es: " << minPaqNoEnviados << endl;
	imprimirEspacios(mejorCromosoma, paquetes, n);
}

int main(int argc, char** argv) {
	vector<Paquete> paquetes = {
		Paquete(1, 2, 2),
		Paquete(2, 3, 3),
		Paquete(3, 1, 6),
		Paquete(4, 3, 4)
	};
	int n = paquetes.size();
	seleccionarPaquetes(paquetes, n);
	return 0;
}
