/*
 * NodoInterno.h
 *
 *  Created on: 27/09/2012
 *      Author: nacho
 */

#ifndef NODOINTERNO_H_
#define NODOINTERNO_H_

#include "Nodo.h"
#include "Persistencia.h"

class NodoInterno: public Nodo {
private:
	int* hijos;
public:
	NodoInterno(int nivel);
	virtual ~NodoInterno();

	bool hidratar(Persistencia & cadena);
	Persistencia serializar() ;

	//Getters y Setters
	int* getHijos();
	void setHijos(int* hijos);
};

#endif /* NODOINTERNO_H_ */
