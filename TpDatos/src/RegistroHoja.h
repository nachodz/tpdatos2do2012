/*
 * RegistroHoja.h
 *
 *  Created on: 25/09/2012
 *      Author: francisco
 */

#ifndef REGISTROHOJA_H_
#define REGISTROHOJA_H_

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class RegistroHoja {

private:

	int letrasIguales, letrasDistintas, posicion, fantasma;
	string palabra;

public:

	RegistroHoja(int letrasIguales, int letrasDistintas, string palabra, int posicion, int fantasma);

	virtual ~RegistroHoja();

	int getLetrasIguales();

	int getLetrasDistintas();

	string getPalabra();

	int getPosicion();

	int getFantasma();
};

#endif /* REGISTROHOJA_H_ */
