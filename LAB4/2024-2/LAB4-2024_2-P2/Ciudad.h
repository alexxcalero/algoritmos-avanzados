/*
 * Proyecto : LAB4-2024_2-P2
 * Archivo  : Ciudad.h
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 9 de noviembre de 2024, 08:27
 */

#ifndef CIUDAD_H
#define CIUDAD_H

class Ciudad {
public:
	Ciudad(int id, int ganancia);
	Ciudad(const Ciudad &orig);
	virtual ~Ciudad();
    void SetGanancia(int ganancia);
    int GetGanancia() const;
    void SetId(int id);
    int GetId() const;
private:
	int id;
	int ganancia;
};

#endif /* CIUDAD_H */
