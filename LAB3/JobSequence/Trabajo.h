/*
 * Proyecto : JobSequence
 * Archivo  : Trabajo.h
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 4 de octubre de 2024, 17:18
 */

#ifndef TRABAJO_H
#define TRABAJO_H

class Trabajo {
public:
	Trabajo(int id, int limite, int ganancia);
	Trabajo(const Trabajo &orig);
	virtual ~Trabajo();
    void SetGanancia(int ganancia);
    int GetGanancia() const;
    void SetLimite(int limite);
    int GetLimite() const;
    void SetId(int id);
    int GetId() const;
private:
	int id;
	int limite;
	int ganancia;
};

#endif /* TRABAJO_H */
