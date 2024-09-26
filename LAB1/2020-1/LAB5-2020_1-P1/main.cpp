/*
 * Proyecto : LAB5-2020_1-P1
 * Archivo  : main.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 6 de setiembre de 2024, 18:38
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#define N 20
using namespace std;

int soluciones[N];
int indice = 0;
int cantSoluciones = 0;

void leerDatos(int &n, int &p, int proyectos[], int costos[], int predecesores[]) {
	ifstream arch("datos.txt", ios::in);
	if(!arch.is_open()) {
		cout << "ERROR: No se pudo abrir el archivo de datos\n";
		exit(1);
	}

	// Leo la cantidad de proyectos y el presupuesto
	arch >> n >> p;

	// Lleno el arreglo con los ids de proyectos
	for(int i = 0; i < n; i++)
		proyectos[i] = i;

	// Leo los costos de cada arreglo
	for(int i = 0; i < n; i++)
		arch >> costos[i];

	// Leo los predecesores de cada proyecto
	for(int i = 0; i < n; i++)
		arch >> predecesores[i];
}

void imprimirArreglos(int proyectos[], int costos[], int predecesores[], int n) {
	for(int i = 0; i < n; i++)
		cout << setw(4) << proyectos[i] << " ";
	cout << endl;

	for(int i = 0; i < n; i++)
		cout << setw(4) << costos[i] << " ";
	cout << endl;

	for(int i = 0; i < n; i++)
		cout << setw(4) << predecesores[i] << " ";
}

bool validarProyecto(int i, int n, int predecesores[]) {
	// El proyecto no tiene predecesores
	if(predecesores[i] == -1)
		return true;

	// Buscamos si el predecesor del proyecto evaluado esta en el arreglo de solucion.
	// Es decir, si estamos usando su predecesor.
	for(int k = 0; k < n; k++)
		if(predecesores[i] == soluciones[k])
			return true;

	return false;
}

bool buscarSoluciones(int proyectos[], int costos[], int predecesores[], int i, int p, int n) {
	// Ya probe todos los proyectos (me sali del limite del arreglo) o me pase
	// del presupuesto (presupuesto es menor que 0)
	if(i == n || p < 0)
		return false;

	// Si el costo del proyecto a tomar es igual al presupuesto que queda,
	// verifico si cumple con sus predecesores para contarlo en la solucion
	if(p == costos[i] && validarProyecto(i, indice, predecesores)) {
		soluciones[indice] = proyectos[i];
		cantSoluciones++;
		cout << "Solucion " << cantSoluciones << ": ";
		for(int k = 0; k <= indice; k++)
			cout << "P" << soluciones[k] << " ";
		cout << endl;
		//return true;
		return false;  // Comentar esta linea, y descomentar la linea de arriba si quiero mostrar una sola solucion
	}

	// Asumo que el proyecto me va a dar una solucion correcta
	soluciones[indice] = proyectos[i];
	indice++;
	// Le resto al presupuesto el costo del proyecto, ya que estamos asumiendo que nos dara una solucion
	if(validarProyecto(i, indice, predecesores) && buscarSoluciones(proyectos, costos, predecesores, i + 1, p - costos[i], n))
		return true;
	else {  // Backtraking
		indice--;
		return buscarSoluciones(proyectos, costos, predecesores, i + 1, p, n);
	}
}

int main(int argc, char** argv) {
	int n, p;
	int proyectos[N], costos[N], predecesores[N];

	leerDatos(n, p, proyectos, costos, predecesores);
	//imprimirArreglos(proyectos, costos, predecesores, n);

	buscarSoluciones(proyectos, costos, predecesores, 0, p, n);

	if(cantSoluciones > 0)
		cout << "Se encontraron " << cantSoluciones << " soluciones\n";
	else
		cout << "No se encontraron soluciones\n";

	return 0;
}
