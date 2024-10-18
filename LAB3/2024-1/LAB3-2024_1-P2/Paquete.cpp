/*
 * Proyecto : LAB3-2024_1-P2
 * Archivo  : Paquete.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 4 de octubre de 2024, 14:29
 */

#include "Paquete.h"

Paquete::Paquete(int peso, int ganancia) {
	this->peso = peso;
	this->ganancia = ganancia;
}

Paquete::Paquete(const Paquete &orig) {
	*this = orig;
}

Paquete::~Paquete() {
}

void Paquete::SetGanancia(int ganancia) {
	this->ganancia = ganancia;
}

int Paquete::GetGanancia() const {
	return ganancia;
}

void Paquete::SetPeso(int peso) {
	this->peso = peso;
}

int Paquete::GetPeso() const {
	return peso;
}
