/*
 * Proyecto : EX2-2024_2-P1
 * Archivo  : Tarea.h
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 10 de diciembre de 2024, 11:36
 */

#ifndef TAREA_H
#define TAREA_H

class Tarea {
public:
	Tarea(int id, int duracion, int inicio, int fin, int penalizacion);
	Tarea(const Tarea &orig);
	virtual ~Tarea();
	void SetPenalizacion(int penalizacion);
	int GetPenalizacion() const;
	void SetFin(int fin);
	int GetFin() const;
	void SetInicio(int inicio);
	int GetInicio() const;
	void SetDuracion(int duracion);
	int GetDuracion() const;
	void SetId(int id);
	int GetId() const;
private:
	int id;
	int duracion;
	int inicio;
	int fin;
	int penalizacion;
};

#endif /* TAREA_H */
