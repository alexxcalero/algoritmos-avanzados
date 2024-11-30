/*
 * Proyecto : FlowShopScheduling
 * Archivo  : Tarea.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 30 de noviembre de 2024, 17:53
 */

#include "Tarea.h"

Tarea::Tarea(int id, const vector<int> &tiemposProcesamiento) {
	this->id = id;
	this->tiemposProcesamiento = tiemposProcesamiento;
}

Tarea::Tarea(const Tarea &orig) {
	*this = orig;
}

Tarea::~Tarea() {
}

void Tarea::SetTiemposProcesamiento(vector<int> tiemposProcesamiento) {
	this->tiemposProcesamiento = tiemposProcesamiento;
}

vector<int> Tarea::GetTiemposProcesamiento() const {
	return tiemposProcesamiento;
}

void Tarea::SetId(int id) {
	this->id = id;
}

int Tarea::GetId() const {
	return id;
}
