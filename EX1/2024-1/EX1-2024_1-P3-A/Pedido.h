/*
 * Proyecto : EX1-2024_1-P3-A
 * Archivo  : Pedido.h
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 13 de octubre de 2024, 15:31
 */

#ifndef PEDIDO_H
#define PEDIDO_H

class Pedido {
public:
	Pedido(int dimension, int cantidad, int ganancia);
	Pedido(const Pedido &orig);
	virtual ~Pedido();
    void SetGanancia(int ganancia);
    int GetGanancia() const;
    void SetCantidad(int cantidad);
    int GetCantidad() const;
    void SetDimension(int dimension);
    int GetDimension() const;
private:
	int dimension;
	int cantidad;
	int ganancia;
};

#endif /* PEDIDO_H */
