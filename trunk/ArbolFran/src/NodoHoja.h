/*
 * NodoHoja.h
 *
 *  Created on: 05/10/2012
 *      Author: nacho
 */

#ifndef NodoHoja_H_
#define NodoHoja_H_

#include <iostream>
#include <fstream>
#include "Constantes.h"
#include "registros.h"
#include "Nodo.h"
#include <cstring>

using namespace std;

class NodoHoja : public Nodo{

private:

	int refProxHoja;

public:

	NodoHoja(int nivel, int numNodoHoja,int refProxHoja, int espLibre, char* datos);
	virtual ~NodoHoja();

	void putReferencia(int referencia);
	int getReferencia();

	tRegistroHoja leerRegistro(int * posicion);
	void ponerRegistro(tRegistroHoja registro, int *posicion);
};




#endif /* NodoHoja_H_ */
