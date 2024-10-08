/*
 * Proyecto : JobSequence
 * Archivo  : Trabajo.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 4 de octubre de 2024, 17:18
 */

#include "Trabajo.h"

Trabajo::Trabajo(int id, int limite, int ganancia) {
	this->id = id;
	this->limite = limite;
	this->ganancia = ganancia;
}

Trabajo::Trabajo(const Trabajo &orig) {
	*this = orig;
}

Trabajo::~Trabajo() {
}

void Trabajo::SetGanancia(int ganancia) {
	this->ganancia = ganancia;
}

int Trabajo::GetGanancia() const {
	return ganancia;
}

void Trabajo::SetLimite(int limite) {
	this->limite = limite;
}

int Trabajo::GetLimite() const {
	return limite;
}

void Trabajo::SetId(int id) {
	this->id = id;
}

int Trabajo::GetId() const {
	return id;
}
