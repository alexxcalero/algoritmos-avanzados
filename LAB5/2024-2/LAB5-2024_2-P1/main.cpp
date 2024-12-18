/*
 * Proyecto : LAB5-2024_2-P1
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 23 de noviembre de 2024, 08:07
 */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
#include <cmath>
#define NUM_ITERACIONES 1000
#define NUM_INDIVIDUOS 20  // Poblacion
#define TASA_SELECCION 0.3
#define PROB_CASAMIENTO 0.8
#define TASA_MUTACION 0.1
using namespace std;

vector<int> guardoGanancia;

bool esAberracion(vector<int> &cromo, vector<int> &ganancia, int n) {
	int seccion = n / 5;

	for(int i = 0; i < seccion; i++) {
		int sumaSecciones = 0;
		for(int j = 0; j < seccion; j++) {
			sumaSecciones += cromo[seccion * i + j];
		}
		if(sumaSecciones != 1)
			return true;  // Hay por lo menos un proyecto seleccionado cada 5
	}

	for(int i = 0; i < seccion; i++) {
		int sumaIndices = 0;
		for(int j = 0; j < seccion; j++) {
			sumaIndices += cromo[seccion * j + i];
		}
		if(sumaIndices != 1)
			return true;  // El mismo proyecto ha sido seleccionado mas de una vez
	}

	return false;  // Todo ok, por lo tanto, no es aberracion
}

void generarPoblacionInicial(vector<vector<int>> &poblacion, vector<int> &ganancia, int n) {
	int cont = 0;
	int seccion = n / 5;  // 25 / 5 = 5
	while(cont < NUM_INDIVIDUOS) {
		vector<int> vaux(25, 0);  // Creo el cromosoma inicial con ceros
		for(int i = 0; i < seccion; i++) {
			int ind = rand() % seccion;
			vaux[seccion * i + ind] = 1;  // Selecciono el proyecto
		}
		if(!esAberracion(vaux, ganancia, n)) {
			poblacion.push_back(vaux);
			cont++;
		}
	}
}

int calcularFitness(vector<int> &cromo, vector<int> &ganancia) {
	int cont = 0;

	for(int i = 0; i < cromo.size(); i++)
		cont += cromo[i] * ganancia[i];

	return cont;
}

void mostrarPoblacion(vector<vector<int>> &poblacion, vector<int> &ganancia) {
	for(int i = 0; i < poblacion.size(); i++) {
		for(int j = 0; j < poblacion[i].size(); j++) {
			cout << poblacion[i][j] << "  ";
		}
		cout << " fo=" << calcularFitness(poblacion[i], ganancia) << endl;
	}
}

void calcularSupervivencia(vector<int> &supervivencia, vector<vector<int>> &poblacion, vector<int> &ganancia) {
	int suma = 0;

	for(int i = 0; i < poblacion.size(); i++)
		suma += calcularFitness(poblacion[i], ganancia);

	for(int i = 0; i < poblacion.size(); i++) {
		int fit = round(100 * (double)calcularFitness(poblacion[i], ganancia) / suma);
		supervivencia.push_back(fit);
	}
}

void cargarRuleta(int ruleta[], vector<int> &supervivencia) {
	int ind = 0;
	for(int i = 0; i < supervivencia.size(); i++)
		for(int j = 0; j < supervivencia[i]; j++)
			ruleta[ind++] = i;
}

void seleccion(vector<vector<int>> &padres, vector<vector<int>> &poblacion, vector<int> &ganancia, int n) {
	int ruleta[100]{-1};
	vector<int> supervivencia;
	calcularSupervivencia(supervivencia, poblacion, ganancia);
	cargarRuleta(ruleta, supervivencia);
	int nseleccionados = poblacion.size() * TASA_SELECCION;
	for(int i = 0; i < nseleccionados; i++) {
		int ind = rand() % 100;
		if(ruleta[ind] > -1)
			padres.push_back(poblacion[ruleta[ind]]);
	}
}

void generarHijo(vector<int> &hijo, vector<int> &padre, vector<int> &madre) {
	int pos = round(padre.size() * PROB_CASAMIENTO);

	for(int i = 0; i < pos; i++)
		hijo.push_back(padre[i]);

	for(int i = pos; i < madre.size(); i++)
		hijo.push_back(madre[i]);
}

void casamiento(vector<vector<int>> &padres, vector<vector<int>> &poblacion, vector<int> &ganancia, int n) {
	for(int i = 0; i < padres.size(); i++) {
		for(int j = 0; j < padres.size(); j++) {
			if(i != j) {
				vector<int> cromo;
				generarHijo(cromo, padres[i], padres[j]);
				if(!esAberracion(cromo, ganancia, n))
					poblacion.push_back(cromo);
			}
		}
	}
}

void inversion(vector<vector<int>> &poblacion, vector<vector<int>> &padres, vector<int> &ganancia, int n) {
	for(int i = 0; i < padres.size(); i++) {
		for(int j = 0; j < padres[i].size(); j++) {
			if(padres[i][j] == 0)
				padres[i][j] = 1;
			else
				padres[i][j] = 0;
		}
		if(!esAberracion(padres[i], ganancia, n))
			poblacion.push_back(padres[i]);
	}
}

void mutacion(vector<vector<int>> &poblacion, vector<vector<int>> &padres, vector<int> &ganancia, int n) {
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
		if(!esAberracion(padres[i], ganancia, n))
			poblacion.push_back(padres[i]);
	}
}

int compacta(vector<int> &cromo) {
	int num = 0;

	for(int i = 0; i < cromo.size(); i++)
		num += pow(2,i) * cromo[i];

	return num;
}

void eliminarAberraciones(vector<vector<int>> &poblacion, vector<int> &ganancia) {
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
		sumA += calcularFitness(a, guardoGanancia);

	for(int i = 0; i < b.size(); i++)
		sumB += calcularFitness(b, guardoGanancia);

	return sumA > sumB;
}

void generarPoblacion(vector<vector<int>> &poblacion,vector<int> &ganancia) {
	guardoGanancia = ganancia;
	sort(poblacion.begin(), poblacion.end(), compara);
	if(poblacion.size() > NUM_INDIVIDUOS)
		poblacion.erase(poblacion.begin() + NUM_INDIVIDUOS, poblacion.end());
}

int mostrarMejor(vector<vector<int>> &poblacion, vector<int> &ganancia) {
	int mejor = 0;

	for(int i = 0; i < poblacion.size(); i++)
		if(calcularFitness(poblacion[mejor], ganancia) < calcularFitness(poblacion[i], ganancia))
			mejor = i;

	cout << endl << "La mejor solucion es: " << calcularFitness(poblacion[mejor], ganancia) << endl;
	for(int i = 0; i < poblacion[mejor].size(); i++)
		cout << poblacion[mejor][i] << "  ";

	cout << endl;
	//return peso-calculafitness(poblacion[mejor],paq);
}

void calcularGananciaAG(vector<int> &ganancia, int n) {
	int cont = 0;
	vector<vector<int>> poblacion;
	srand(time(NULL));
	generarPoblacionInicial(poblacion, ganancia, n);
	mostrarPoblacion(poblacion, ganancia);
	while(1) {
		vector<vector<int>> padres;
		seleccion(padres, poblacion, ganancia, n);
		casamiento(padres, poblacion, ganancia, n);
		cout << endl;
		inversion(poblacion, padres, ganancia, n);
		mutacion(poblacion, padres, ganancia, n);
		eliminarAberraciones(poblacion, ganancia);
		generarPoblacion(poblacion, ganancia);
		mostrarPoblacion(poblacion, ganancia);
		mostrarMejor(poblacion, ganancia);
		cont++;
		if(cont == NUM_ITERACIONES) break;
	}
}

int main(int argc, char** argv) {
	vector<int> ganancia = {9, 2, 7, 8, 6, 6, 4, 3, 7, 8, 5, 8, 1, 8, 3, 7, 6, 9, 4, 2, 8, 6, 7, 5, 9};
	int n = ganancia.size();
	calcularGananciaAG(ganancia, n);
	return 0;
}
