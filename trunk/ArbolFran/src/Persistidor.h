/*
 * Persistidor.h
 *
 *  Created on: 09/10/2012
 *      Author: francisco
 */

#ifndef PERSISTIDOR_H_
#define PERSISTIDOR_H_

#include "Constantes.h"
#include <iostream>
#include <fstream>
#include "registros.h"
#include "Nodo.h"
#include "NodoHoja.h"
#include <cstring>

class Persistidor {

public:
	Persistidor();
	virtual ~Persistidor();
	void persistirNodoHoja(Nodo *nodo, fstream *archivoArbol);
	void recuperarNodoHoja(Nodo *nodo, int numNodo, ifstream *archivoArbol);
};

#endif /* PERSISTIDOR_H_ */
