/*
 * Proyecto : LAB3-2024_2-P1
 * Archivo  : Proyecto.h
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 5 de octubre de 2024, 08:17
 */

#ifndef PROYECTO_H
#define PROYECTO_H

#include <vector>
using namespace std;

class Proyecto {
public:
	Proyecto(int id, int costo, int ganancia, int beneficio, const vector<int> &predecesores);
	Proyecto(const Proyecto &orig);
	virtual ~Proyecto();
    void SetPredecesores(vector<int> predecesores);
    vector<int> GetPredecesores() const;
    void SetBeneficio(int beneficio);
    int GetBeneficio() const;
    void SetGanancia(int ganancia);
    int GetGanancia() const;
    void SetCosto(int costo);
    int GetCosto() const;
    void SetId(int id);
    int GetId() const;
private:
	int id;
	int costo;
	int ganancia;
	int beneficio;
	vector<int> predecesores;
};

#endif /* PROYECTO_H */
