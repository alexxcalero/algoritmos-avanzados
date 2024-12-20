/*
 * Proyecto : EX2-2024_2-P2
 * Archivo  : Tarea.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 10 de diciembre de 2024, 11:36
 */

#include "Tarea.h"

Tarea::Tarea(int id, int duracion, int inicio, int fin, int penalizacion) {
	this->id = id;
	this->duracion = duracion;
	this->inicio = inicio;
	this->fin = fin;
	this->penalizacion = penalizacion;
}

Tarea::Tarea(const Tarea &orig) {
	*this = orig;
}

Tarea::~Tarea() {
}

void Tarea::SetPenalizacion(int penalizacion) {
	this->penalizacion = penalizacion;
}

int Tarea::GetPenalizacion() const {
	return penalizacion;
}

void Tarea::SetFin(int fin) {
	this->fin = fin;
}

int Tarea::GetFin() const {
	return fin;
}

void Tarea::SetInicio(int inicio) {
	this->inicio = inicio;
}

int Tarea::GetInicio() const {
	return inicio;
}

void Tarea::SetDuracion(int duracion) {
	this->duracion = duracion;
}

int Tarea::GetDuracion() const {
	return duracion;
}

void Tarea::SetId(int id) {
	this->id = id;
}

int Tarea::GetId() const {
	return id;
}
