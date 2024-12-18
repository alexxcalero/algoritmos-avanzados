/*
 * Proyecto : Rutas-GRASP
 * Archivo  : Ciudad.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 5 de noviembre de 2024, 22:32
 */

#include "Ciudad.h"

Ciudad::Ciudad() {
}

Ciudad::Ciudad(const Ciudad &orig) {
	*this = orig;
}

Ciudad::~Ciudad() {
}

void Ciudad::SetDistancia(int distancia) {
	this->distancia = distancia;
}

int Ciudad::GetDistancia() const {
	return distancia;
}

void Ciudad::SetId(int id) {
	this->id = id;
}

int Ciudad::GetId() const {
	return id;
}
