/*
 * Proyecto : LAB3-2024_1-P1
 * Archivo  : Ciudad.h
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 4 de octubre de 2024, 13:34
 */

#ifndef CIUDAD_H
#define CIUDAD_H

class Ciudad {
public:
	Ciudad();
	Ciudad(const Ciudad &orig);
	virtual ~Ciudad();
    void SetDistancia(int distancia);
    int GetDistancia() const;
    void SetIndice(int indice);
    int GetIndice() const;
private:
	int indice;
	int distancia;
};

#endif /* CIUDAD_H */
