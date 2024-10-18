/*
 * Proyecto : LAB3-2024_1-P2
 * Archivo  : Paquete.h
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 4 de octubre de 2024, 14:29
 */

#ifndef PAQUETE_H
#define PAQUETE_H

class Paquete {
public:
	Paquete(int peso, int ganacia);
	Paquete(const Paquete &orig);
	virtual ~Paquete();
    void SetGanancia(int ganancia);
    int GetGanancia() const;
    void SetPeso(int peso);
    int GetPeso() const;
private:
	int peso;
	int ganancia;
};

#endif /* PAQUETE_H */
