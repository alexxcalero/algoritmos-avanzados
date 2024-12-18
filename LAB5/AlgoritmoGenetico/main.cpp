/*
 * Proyecto : AlgoritmoGenetico
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 19 de noviembre de 2024, 23:01
 */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
#include <cmath>
#define NUM_ITERACIONES 1000
#define NUM_INDIVIDUOS 10
#define TASA_SELECCION 0.3
#define PROB_CASAMIENTO 0.5
#define TASA_MUTACION 0.5
using namespace std;

vector<int> guardarPaquetes;

bool esAberracion(vector<int> &cromo, vector<int> &paquetes, int peso) {
	int total = 0;
	for(int i = 0; i < cromo.size(); i++)
		total += cromo[i] * paquetes[i];
	return total > peso;
}

void generarPoblacionInicial(vector<vector<int>> &poblacion, vector<int> &paquetes, int peso, int n) {
	int cont = 0;
	while(cont < NUM_INDIVIDUOS) {
		vector<int> vaux;
		for(int i = 0; i < n; i++)
			vaux.push_back(rand() % 2);
		if(!esAberracion(vaux, paquetes, peso)) {
			poblacion.push_back(vaux);
			cont++;
		}
	}
}

int calcularFitness(vector<int> &cromo, vector<int> &paquetes) {
	int cont = 0;
	for(int i = 0; i < cromo.size(); i++)
		cont += cromo[i] * paquetes[i];
	return cont;
}

void mostrarPoblacion(vector<vector<int>> &poblacion, vector<int> &paquetes) {
	for(int i = 0; i < poblacion.size(); i++) {
		for(int j = 0; j < poblacion[i].size(); j++) {
			cout << poblacion[i][j] << "  ";
		}
		cout <<" fo="<< calcularFitness(poblacion[i], paquetes) << endl;
	}
}

void calcularSupervivencia(vector<int> &supervivencia, vector<vector<int>> &poblacion, vector<int> &paquetes) {
	int suma = 0;

	for(int i = 0; i < poblacion.size(); i++)
		suma += calcularFitness(poblacion[i], paquetes);

	for(int i = 0; i < poblacion.size(); i++) {
		int fit = round(100 * (double)calcularFitness(poblacion[i], paquetes) / suma);
		supervivencia.push_back(fit);
	}
}

void cargarRuleta(vector<int> &supervivencia, int *ruleta) {
	int ind = 0;
	for(int i = 0; i < supervivencia.size(); i++)
		for(int j = 0; j < supervivencia[i]; j++)
			ruleta[ind++] = i;
}

void seleccion(vector<vector<int>> &padres, vector<vector<int>> &poblacion, vector<int> &paquetes, int peso, int n) {
	int ruleta[100]{-1};
	vector<int> supervivencia;
	calcularSupervivencia(supervivencia, poblacion, paquetes);
	cargarRuleta(supervivencia, ruleta);
	int nseleccionados = poblacion.size() * TASA_SELECCION;
	for(int i = 0; i < nseleccionados; i++) {
		int ind = rand() % 100;
		if(ruleta[ind] > -1)
			padres.push_back(poblacion[ruleta[ind]]);
	}
}

void generarHijo(vector<int> &padre, vector<int> &madre, vector<int> &hijo) {
	int pos = round(padre.size() * PROB_CASAMIENTO);

	for(int i = 0; i < pos; i++)
		hijo.push_back(padre[i]);

	for(int i = pos; i < madre.size(); i++)
		hijo.push_back(madre[i]);
}

void casamiento(vector<vector<int>> &padres, vector<vector<int>> &poblacion, vector<int> &paquetes, int peso) {
	for(int i = 0; i < padres.size(); i++) {
		for(int j = 0; j < padres.size(); j++) {
			if(i != j) {
				vector<int> cromo;
				generarHijo(padres[i], padres[j], cromo);
				if(!esAberracion(cromo, paquetes, peso))
					poblacion.push_back(cromo);
			}
		}
	}
}

void inversion(vector<vector<int>> &poblacion, vector<vector<int>> &padres, vector<int> &paquetes, int peso) {
	for(int i = 0; i < padres.size(); i++) {
		for(int j = 0; j < padres[i].size(); j++) {
			if(padres[i][j] == 0)
				padres[i][j] = 1;
			else
				padres[i][j] = 0;
		}
		if(!esAberracion(padres[i], paquetes, peso))
			poblacion.push_back(padres[i]);
	}
}

void mutacion(vector<vector<int>> &poblacion, vector<vector<int>> &padres, vector<int> &paquetes, int peso) {
	int cont = 0;
	int nmuta = round(padres[0].size() * TASA_MUTACION);
	for(int i = 0; i < padres.size(); i++) {
		while(cont < nmuta) {
			int ind = rand() % padres[0].size();
			if(padres[i][ind] == 0)
				padres[i][ind] = 1;
			else
				padres[i][ind] = 0;
			cont++;
		}
		if(!esAberracion(padres[i], paquetes, peso))
			poblacion.push_back(padres[i]);
	}
}

int compacta(vector<int> &cromo) {
	int num = 0;
	for(int i = 0; i < cromo.size(); i++)
		num += pow(2, i) * cromo[i];
	return num;
}

void eliminarAberraciones(vector<vector<int>> &poblacion, vector<int> &paq) {
	map<int, vector<int>> municos;

	for(int i = 0; i < poblacion.size(); i++) {
		int num = compacta(poblacion[i]);
		municos[num] = poblacion[i];
	}

	poblacion.clear();
	for(map<int, vector<int>>::iterator it = municos.begin(); it != municos.end(); it++) {
		poblacion.push_back(it->second);
	}
}

bool compara(vector<int> &a, vector<int> &b) {
	int sumA = 0, sumB = 0;

	for(int i = 0; i < a.size(); i++)
		sumA += calcularFitness(a, guardarPaquetes);

	for(int i = 0; i < b.size(); i++)
		sumB += calcularFitness(b, guardarPaquetes);

	return sumA > sumB;
}

void generarPoblacion(vector<vector<int>> &poblacion, vector<int> &paquetes, int peso) {
	guardarPaquetes = paquetes;
	sort(poblacion.begin(), poblacion.end(), compara);
	if(poblacion.size() > NUM_INDIVIDUOS)
		poblacion.erase(poblacion.begin() + NUM_INDIVIDUOS, poblacion.end());
}

int mostrarMejor(vector<vector<int>> &poblacion, vector<int> &paquetes, int peso) {
	int mejor = 0;

	for(int i = 0; i < poblacion.size(); i++)
		if(calcularFitness(poblacion[mejor], paquetes) < calcularFitness(poblacion[i], paquetes))
			mejor = i;

	cout << endl << "La mejor solucion es: " << calcularFitness(poblacion[mejor], paquetes) << endl;
	for(int i = 0; i < poblacion[mejor].size(); i++) {
		cout << poblacion[mejor][i] << "  ";
	}

	cout << endl;
	return peso - calcularFitness(poblacion[mejor], paquetes);
}

void mochilaGenetica(vector<int> &paquetes, int peso, int n) {
	int cont = 0;
	vector<vector<int>> poblacion;
	srand(time(NULL));
	generarPoblacionInicial(poblacion, paquetes, peso, n);
	mostrarPoblacion(poblacion, paquetes);
	while(1){
		vector<vector<int>> padres;
		seleccion(padres, poblacion, paquetes, peso, n);
		casamiento(padres, poblacion, paquetes, peso);
		cout << endl;
		inversion(poblacion, padres, paquetes, peso);
		mutacion(poblacion, padres, paquetes, peso);
		eliminarAberraciones(poblacion, paquetes);
		generarPoblacion(poblacion, paquetes, peso);
		mostrarPoblacion(poblacion, paquetes);
		mostrarMejor(poblacion, paquetes, peso);
		cont++;
		if(cont == NUM_ITERACIONES) break;
	}
}

int main(int argc, char** argv) {
	vector<int> paquetes = {1, 2, 4, 12, 1, 3, 5, 10, 7};
	int peso = 35;
	int n = paquetes.size();
	mochilaGenetica(paquetes, peso, n);
	return 0;
}
