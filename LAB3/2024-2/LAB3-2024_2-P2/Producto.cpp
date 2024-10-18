/*
 * Proyecto : LAB3-2024_2-P2
 * Archivo  : Producto.cpp
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 5 de octubre de 2024, 09:30
 */

#include "Producto.h"

Producto::Producto(int cantidad, int longitud, int altura) {
	this->cantidad = cantidad;
	this->longitud = longitud;
	this->altura = altura;
}

Producto::Producto(const Producto &orig) {
	*this = orig;
}

Producto::~Producto() {
}

void Producto::SetAltura(int altura) {
	this->altura = altura;
}

int Producto::GetAltura() const {
	return altura;
}

void Producto::SetLongitud(int longitud) {
	this->longitud = longitud;
}

int Producto::GetLongitud() const {
	return longitud;
}

void Producto::SetCantidad(int cantidad) {
	this->cantidad = cantidad;
}

int Producto::GetCantidad() const {
	return cantidad;
}
