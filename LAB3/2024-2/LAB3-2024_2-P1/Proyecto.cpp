/*
 * Proyecto : LAB3-2024_2-P1
 * Archivo  : Proyecto.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 5 de octubre de 2024, 08:17
 */

#include "Proyecto.h"

Proyecto::Proyecto(int id, int costo, int ganancia, int beneficio, const vector<int> &predecesores) {
	this->id = id;
	this->costo = costo;
	this->ganancia = ganancia;
	this->beneficio = beneficio;
	this->predecesores = predecesores;
}

Proyecto::Proyecto(const Proyecto &orig) {
	*this = orig;
}

Proyecto::~Proyecto() {
}

void Proyecto::SetPredecesores(vector<int> predecesores) {
	this->predecesores = predecesores;
}

vector<int> Proyecto::GetPredecesores() const {
	return predecesores;
}

void Proyecto::SetBeneficio(int beneficio) {
	this->beneficio = beneficio;
}

int Proyecto::GetBeneficio() const {
	return beneficio;
}

void Proyecto::SetGanancia(int ganancia) {
	this->ganancia = ganancia;
}

int Proyecto::GetGanancia() const {
	return ganancia;
}

void Proyecto::SetCosto(int costo) {
	this->costo = costo;
}

int Proyecto::GetCosto() const {
	return costo;
}

void Proyecto::SetId(int id) {
	this->id = id;
}

int Proyecto::GetId() const {
	return id;
}
