/*
 * Proyecto : CorteDeBarra
 * Archivo  : Pedido.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 5 de octubre de 2024, 00:24
 */

#include "Pedido.h"

Pedido::Pedido(int dimension, int cantidad, int ganancia) {
	this->dimension = dimension;
	this->cantidad = cantidad;
	this->ganancia = ganancia;
}

Pedido::Pedido(const Pedido &orig) {
	*this = orig;
}

Pedido::~Pedido() {
}

void Pedido::SetGanancia(int ganancia) {
	this->ganancia = ganancia;
}

int Pedido::GetGanancia() const {
	return ganancia;
}

void Pedido::SetCantidad(int cantidad) {
	this->cantidad = cantidad;
}

int Pedido::GetCantidad() const {
	return cantidad;
}

void Pedido::SetDimension(int dimension) {
	this->dimension = dimension;
}

int Pedido::GetDimension() const {
	return dimension;
}


