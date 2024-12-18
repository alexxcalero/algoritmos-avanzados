/*
 * Proyecto : EX1-2024_2-P3-B
 * Archivo  : Tarea.h
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 15 de octubre de 2024, 11:45
 */

#ifndef TAREA_H
#define TAREA_H

class Tarea {
public:
	Tarea(char id, int hora, int ganancia);
	Tarea(const Tarea &orig);
	virtual ~Tarea();
	void SetGanancia(int ganancia);
	int GetGanancia() const;
	void SetHora(int hora);
	int GetHora() const;
	void SetId(char id);
	char GetId() const;
private:
	char id;
	int hora;
	int ganancia;
};

#endif /* TAREA_H */
