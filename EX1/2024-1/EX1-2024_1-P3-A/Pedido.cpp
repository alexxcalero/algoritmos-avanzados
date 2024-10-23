/*
 * Proyecto : EX1-2024_1-P3-A
 * Archivo  : Pedido.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 13 de octubre de 2024, 15:31
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
