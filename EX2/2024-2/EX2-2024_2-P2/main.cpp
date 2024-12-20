/*
 * Proyecto : EX2-2024_2-P2
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 10 de diciembre de 2024, 12:42
 */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>
#include <ctime>
#include <cmath>
#include "Tarea.h"
#define NUM_ITERACIONES 1000
#define NUM_INDIVIDUOS 10  // Poblacion
#define TASA_SELECCION 0.8
#define PROB_CASAMIENTO 0.5
#define TASA_MUTACION 0.5
using namespace std;

vector<Tarea> guardoTareas;

// Funcion para asignar la tarea en sus respectivo espacios de tiempos
void marcarTiempos(Tarea &tarea, int indiceParaEmpezar, vector<int> &tiempos) {
	for(int i = 0; i < tarea.GetDuracion(); i++) {
		tiempos[indiceParaEmpezar] = tarea.GetId();
		indiceParaEmpezar++;
	}
}

// Funcion para poder calcular la hora mas lejana que servira para crear mi arreglo de tiempos
int calcularMayorHora(vector<Tarea> &tareas, int cantTareas) {
	int max = INT_MIN;
	for(int i = 0; i < cantTareas; i++)
		if(tareas[i].GetFin() > max)
			max = tareas[i].GetFin();
	return max;
}

bool esAberracion(vector<int> &cromo, vector<Tarea> &tareas, int cantTareas) {
	// Calculo la hora final maxima entre todas las tareas
	int maxHora = calcularMayorHora(tareas, cantTareas);
	vector<int> tiempos(maxHora, 0);

	for(int i = 0; i < cantTareas; i++) {
		if(cromo[i] == 1) {
			int duracion = tareas[i].GetDuracion();
			int ini = tareas[i].GetInicio() - 1;
			int fin = tareas[i].GetFin() - 1;
			int cantEspacios = 0;
			int indiceParaEmpezar;
			bool yaHayIndiceParaEmpezar = false;

			for(int j = ini; j <= fin; j++) {
				if(tiempos[j] == 0) {  // Ese tiempo no esta ocupado por otra tarea
					if(!yaHayIndiceParaEmpezar) {
						indiceParaEmpezar = j;  // Seteo el indice de donde puedo empezar a asignar la tarea
						yaHayIndiceParaEmpezar = true;  // Actualizo la bandera a true
					}
					cantEspacios++;  // Aumento el contador de espacios
				} else {
					yaHayIndiceParaEmpezar = false;  // coloco la bandera en false
					cantEspacios = 0;  // Reinicio el contador de espacios
				}
			}

			// Verifico si la cantidad de espacios es mayor a la duracion de la tarea
			if(cantEspacios >= duracion) {
				marcarTiempos(tareas[i], indiceParaEmpezar, tiempos);  // Asigno la tarea a los espacios de tiempo correspondientes
			}
			else  // Si alguna tarea no se pudo asignar satisfactoriamente
				return true;  // Retorno true ya que es aberracion
		}
	}

	// Todas las tareas marcadas con 1 en el cromo se pudieron asignar sin problemas
	return false;  // Retorno false, xq no es aberracion
}

void generarPoblacionInicial(vector<vector<int>> &poblacion, vector<Tarea> &tareas, int cantTareas) {
	int cont = 0;
	while(cont < NUM_INDIVIDUOS) {
		vector<int> vaux(cantTareas, 0);  // Creo el cromosoma inicial con ceros
		for(int i = 0; i < cantTareas; i++) {
			int ind = rand() % cantTareas;
			vaux[ind] = 1;  // Selecciono la tarea
		}
		if(!esAberracion(vaux, tareas, cantTareas)) {
			poblacion.push_back(vaux);
			cont++;
		}
	}
}

int calcularFitness(vector<int> &cromo, vector<Tarea> &tareas) {
	int cont = 0;
	for(int i = 0; i < cromo.size(); i++)
		if(cromo[i] == 0)
			cont += tareas[i].GetPenalizacion();
	return cont;
}

void mostrarPoblacion(vector<vector<int>> &poblacion, vector<Tarea> &tareas) {
	for(int i = 0; i < poblacion.size(); i++) {
		for(int j = 0; j < poblacion[i].size(); j++) {
			cout << poblacion[i][j] << " ";
		}
		cout << " fo=" << calcularFitness(poblacion[i], tareas) << endl;
	}
}

void calcularSupervivencia(vector<int> &supervivencia, vector<vector<int>> &poblacion, vector<Tarea> &tareas) {
	int suma = 0;

	for(int i = 0; i < poblacion.size(); i++)
		suma += calcularFitness(poblacion[i], tareas);

	for(int i = 0; i < poblacion.size(); i++) {
		int fit = round(100 * (double)calcularFitness(poblacion[i], tareas) / suma);
		supervivencia.push_back(fit);
	}
}

void cargarRuleta(int ruleta[], vector<int> &supervivencia) {
	int ind = 0;
	for(int i = 0; i < supervivencia.size(); i++)
		for(int j = 0; j < supervivencia[i]; j++)
			ruleta[ind++] = i;
}

void seleccion(vector<vector<int>> &padres, vector<vector<int>> &poblacion, vector<Tarea> &tareas, int cantTareas) {
	int ruleta[100]{-1};
	vector<int> supervivencia;
	calcularSupervivencia(supervivencia, poblacion, tareas);
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

void casamiento(vector<vector<int>> &padres, vector<vector<int>> &poblacion, vector<Tarea> &tareas, int cantTareas) {
	for(int i = 0; i < padres.size(); i++) {
		for(int j = 0; j < padres.size(); j++) {
			if(i != j) {
				vector<int> cromo;
				generarHijo(cromo, padres[i], padres[j]);
				if(!esAberracion(cromo, tareas, cantTareas))
					poblacion.push_back(cromo);
			}
		}
	}
}

void inversion(vector<vector<int>> &poblacion, vector<vector<int>> &padres, vector<Tarea> &tareas, int cantTareas) {
	for(int i = 0; i < padres.size(); i++) {
		for(int j = 0; j < padres[i].size(); j++) {
			if(padres[i][j] == 0)
				padres[i][j] = 1;
			else
				padres[i][j] = 0;
		}
		if(!esAberracion(padres[i], tareas, cantTareas))
			poblacion.push_back(padres[i]);
	}
}

void mutacion(vector<vector<int>> &poblacion, vector<vector<int>> &padres, vector<Tarea> &tareas, int cantTareas) {
	int cont = 0;
	int nmuta = round(padres[0].size() * TASA_MUTACION);
	for(int i = 0; i < padres.size(); i++) {
		while(cont < nmuta) {
			int ind = rand() % padres[0].size();
			if(padres[i][ind] == 0) {
				padres[i][ind] = 1;
			}
			else
				padres[i][ind] = 0;
			cont++;
		}
		if(!esAberracion(padres[i], tareas, cantTareas))
			poblacion.push_back(padres[i]);
	}
}

int compacta(vector<int> &cromo) {
	int num = 0;

	for(int i = 0; i < cromo.size(); i++)
		num += pow(2,i) * cromo[i];

	return num;
}

void eliminarAberraciones(vector<vector<int>> &poblacion, vector<Tarea> &tareas) {
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
		sumA += calcularFitness(a, guardoTareas);

	for(int i = 0; i < b.size(); i++)
		sumB += calcularFitness(b, guardoTareas);

	return sumA < sumB;
}

void generarPoblacion(vector<vector<int>> &poblacion, vector<Tarea> &tareas) {
	guardoTareas = tareas;
	sort(poblacion.begin(), poblacion.end(), compara);
	if(poblacion.size() > NUM_INDIVIDUOS)
		poblacion.erase(poblacion.begin() + NUM_INDIVIDUOS, poblacion.end());
}

int mostrarMejor(vector<vector<int>> &poblacion, vector<Tarea> &tareas) {
	int mejor = 0;

	for(int i = 0; i < poblacion.size(); i++)
		if(calcularFitness(poblacion[mejor], tareas) > calcularFitness(poblacion[i], tareas))
			mejor = i;

	cout << endl << "La mejor solucion es: " << calcularFitness(poblacion[mejor], tareas) << endl;
	for(int i = 0; i < poblacion[mejor].size(); i++)
		cout << poblacion[mejor][i] << "  ";

	cout << endl;
}

void asignacionDeTareas(vector<Tarea> &tareas, int cantTareas) {
	int cont = 0;
	vector<vector<int>> poblacion;
	srand(time(NULL));
	generarPoblacionInicial(poblacion, tareas, cantTareas);
	mostrarPoblacion(poblacion, tareas);
	while(1) {
		vector<vector<int>> padres;
		seleccion(padres, poblacion, tareas, cantTareas);
		casamiento(padres, poblacion, tareas, cantTareas);
		cout << endl;
		inversion(poblacion, padres, tareas, cantTareas);
		mutacion(poblacion, padres, tareas, cantTareas);
		eliminarAberraciones(poblacion, tareas);
		generarPoblacion(poblacion, tareas);
		mostrarPoblacion(poblacion, tareas);
		mostrarMejor(poblacion, tareas);
		cont++;
		if(cont == NUM_ITERACIONES) break;
	}
}

int main(int argc, char** argv) {
	vector<Tarea> tareas = {
		Tarea(1, 2, 1, 4, 10),
		Tarea(2, 3, 3, 6, 15),
		Tarea(3, 1, 5, 7, 8),
		Tarea(4, 2, 2, 5, 12),
		Tarea(5, 4, 6, 10, 20),
		Tarea(6, 2, 8, 11, 7),
		Tarea(7, 1, 9, 10, 6),
		Tarea(8, 3, 1, 3, 18),
		Tarea(9, 2, 4, 7, 14),
		Tarea(10, 3, 6, 9, 16)
	};

	int cantTareas = tareas.size();

	asignacionDeTareas(tareas, cantTareas);

	return 0;
}
