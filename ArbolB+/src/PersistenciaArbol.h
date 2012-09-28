/*
 * PersistenciaArbol.h
 *
 *  Created on: 27/09/2012
 *      Author: nacho
 */

#ifndef PERSISTENCIAARBOL_H_
#define PERSISTENCIAARBOL_H_

#include <iostream>
#include "Persistencia.h"
#include "HandlerBloques.h"

using namespace std;

class PersistenciaArbol: public Persistencia {
private:
	HandlerBloques * handlerBloque;
public:
	PersistenciaArbol();
	virtual ~PersistenciaArbol();

	bool guardarBloque (int nroBloque, Persistencia cadena);
	Persistencia leerBloque (int nroBloque);
};

#endif /* PERSISTENCIAARBOL_H_ */
