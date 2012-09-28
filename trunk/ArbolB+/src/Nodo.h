/*
 * Nodo.h
 *
 *  Created on: 27/09/2012
 *      Author: nacho
 */

#ifndef NODO_H_
#define NODO_H_

#include "Serializable.h"

class Nodo : public Serializable {

public:

	int numero;
	int nivel;
	int espacioOcupado;
	int cantidadClaves;

public:
	Nodo();
	Nodo(int nivel);
	virtual ~Nodo();

	//Getters y Setters
	int getNumero();
	void setNumero(int numero);
	int getNivel();
	void setNivel(int nivel);
	int getEspacioOcupado();
	void setEspacioOcupado(int espacioOcupado);
	int getCantidadClaves();
	void setCantidadClaves(int cantidadClaves);
};

#endif /* NODO_H_ */
