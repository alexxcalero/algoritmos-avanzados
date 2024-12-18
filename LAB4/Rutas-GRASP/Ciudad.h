/*
 * Proyecto : Rutas-GRASP
 * Archivo  : Ciudad.h
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 5 de noviembre de 2024, 22:32
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
    void SetId(int id);
    int GetId() const;
private:
	int id;
	int distancia;
};

#endif /* CIUDAD_H */
