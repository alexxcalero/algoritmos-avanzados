/*
 * Proyecto : LAB3-2024_2-P2
 * Archivo  : Producto.h
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 5 de octubre de 2024, 09:30
 */

#ifndef PRODUCTO_H
#define PRODUCTO_H

class Producto {
public:
	Producto(int cantidad, int longitud, int altura);
	Producto(const Producto &orig);
	virtual ~Producto();
    void SetAltura(int altura);
    int GetAltura() const;
    void SetLongitud(int longitud);
    int GetLongitud() const;
    void SetCantidad(int cantidad);
    int GetCantidad() const;
private:
	int cantidad;
	int longitud;
	int altura;
};

#endif /* PRODUCTO_H */
