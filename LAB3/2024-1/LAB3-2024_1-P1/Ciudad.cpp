/*
 * Proyecto : LAB3-2024_1-P1
 * Archivo  : Ciudad.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 4 de octubre de 2024, 13:34
 */

#include "Ciudad.h"

Ciudad::Ciudad() {
	indice = 0;
	distancia = 0;
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

void Ciudad::SetIndice(int indice) {
	this->indice = indice;
}

int Ciudad::GetIndice() const {
	return indice;
}
