/*
 * Proyecto : PredictAsesoriaCueva
 * Archivo  : Paquete.h
 * Autor    : Alex Calero Revilla
 * Codigo   : 20206455
 * Fecha    : 9 de diciembre de 2024, 23:50
 */

#ifndef PAQUETE_H
#define PAQUETE_H

class Paquete {
public:
	Paquete(int id, int tamanho, int inicio);
	Paquete(const Paquete &orig);
	virtual ~Paquete();
	void SetInicio(int inicio);
	int GetInicio() const;
	void SetTamanho(int tamanho);
	int GetTamanho() const;
	void SetId(int id);
	int GetId() const;
private:
	int id;
	int tamanho;
	int inicio;
};

#endif /* PAQUETE_H */
