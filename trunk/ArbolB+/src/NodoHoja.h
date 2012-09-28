/*
 * NodoHoja.h
 *
 *  Created on: 27/09/2012
 *      Author: nacho
 */

#ifndef NODOHOJA_H_
#define NODOHOJA_H_

#include "Nodo.h"
#include "Persistencia.h"

class NodoHoja: public Nodo {
private:

	int nroHojaSiguiente;
	Persistencia* datos;

public:
	NodoHoja();
	virtual ~NodoHoja();

	bool hidratar(Persistencia & cadena);
	Persistencia serializar() ;

	//Getters y Setters
	int getNroHojaSiguiente();
	void setNroHojaSiguiente(int nroHojaSiguiente);

	Persistencia* getDatos();
	void setDatos(Persistencia* datos);
};

#endif /* NODOHOJA_H_ */
