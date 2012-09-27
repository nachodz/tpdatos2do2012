/*
 * clave.h
 *
 *  Created on: 27/09/2012
 *      Author: francisco
 */

#ifndef CLAVE_H_
#define CLAVE_H_

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class clave {

private:

	int posRelativa, fantasma;
	string termino;

public:

	clave (string ter, int pos,int fant);

	virtual ~clave();

	string getTermino();

	int getPosicion();

	int getFantasma();
};

#endif /* CLAVE_H_ */
