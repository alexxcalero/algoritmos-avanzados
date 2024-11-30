/*
 * Proyecto : FlowShopScheduling
 * Archivo  : Tarea.h
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 30 de noviembre de 2024, 17:53
 */

#ifndef TAREA_H
#define TAREA_H

#include <vector>
using namespace std;

class Tarea {
public:
	Tarea(int id, const vector<int> &tiemposProcesamiento);
	Tarea(const Tarea &orig);
	virtual ~Tarea();
    void SetTiemposProcesamiento(vector<int> tiemposProcesamiento);
    vector<int> GetTiemposProcesamiento() const;
    void SetId(int id);
    int GetId() const;
private:
	int id;
	vector<int> tiemposProcesamiento;
};

#endif /* TAREA_H */
