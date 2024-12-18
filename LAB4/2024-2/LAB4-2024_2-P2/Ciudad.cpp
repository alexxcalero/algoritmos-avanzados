/*
 * Proyecto : LAB4-2024_2-P2
 * Archivo  : Ciudad.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 9 de noviembre de 2024, 08:27
 */

#include "Ciudad.h"

Ciudad::Ciudad(int id, int ganancia) {
	this->id = id;
	this->ganancia = ganancia;
}

Ciudad::Ciudad(const Ciudad &orig) {
	*this = orig;
}

Ciudad::~Ciudad() {
}

void Ciudad::SetGanancia(int ganancia) {
	this->ganancia = ganancia;
}

int Ciudad::GetGanancia() const {
	return ganancia;
}

void Ciudad::SetId(int id) {
	this->id = id;
}

int Ciudad::GetId() const {
	return id;
}
