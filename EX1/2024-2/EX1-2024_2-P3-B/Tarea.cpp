/*
 * Proyecto : EX1-2024_2-P3-B
 * Archivo  : Tarea.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 15 de octubre de 2024, 11:45
 */

#include "Tarea.h"

Tarea::Tarea(char id, int hora, int ganancia) {
	this->id = id;
	this->hora = hora;
	this->ganancia = ganancia;
}

Tarea::Tarea(const Tarea &orig) {
	*this = orig;
}

Tarea::~Tarea() {
}

void Tarea::SetGanancia(int ganancia) {
	this->ganancia = ganancia;
}

int Tarea::GetGanancia() const {
	return ganancia;
}

void Tarea::SetHora(int hora) {
	this->hora = hora;
}

int Tarea::GetHora() const {
	return hora;
}

void Tarea::SetId(char id) {
	this->id = id;
}

char Tarea::GetId() const {
	return id;
}
