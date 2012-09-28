/*
 * Clave.h
 *
 *  Created on: 27/09/2012
 *      Author: nacho
 */

#ifndef CLAVE_H_
#define CLAVE_H_

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Clave {

private:

	int posRelativa, fantasma;
	string termino;

public:

	Clave (string ter, int pos,int fant);

	virtual ~Clave();

	string getTermino();

	int getPosicion();

	int getFantasma();
};

#endif /* CLAVE_H_ */

