/*
 * Proyecto : PredictAsesoriaCueva
 * Archivo  : Paquete.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 9 de diciembre de 2024, 23:50
 */

#include "Paquete.h"

Paquete::Paquete(int id, int tamanho, int inicio) {
	this->id = id;
	this->tamanho = tamanho;
	this->inicio = inicio;
}

Paquete::Paquete(const Paquete &orig) {
	*this = orig;
}

Paquete::~Paquete() {
}

void Paquete::SetInicio(int inicio) {
	this->inicio = inicio;
}

int Paquete::GetInicio() const {
	return inicio;
}

void Paquete::SetTamanho(int tamanho) {
	this->tamanho = tamanho;
}

int Paquete::GetTamanho() const {
	return tamanho;
}

void Paquete::SetId(int id) {
	this->id = id;
}

int Paquete::GetId() const {
	return id;
}
