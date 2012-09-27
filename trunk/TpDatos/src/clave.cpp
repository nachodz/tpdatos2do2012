/*
 * clave.cpp
 *
 *  Created on: 27/09/2012
 *      Author: francisco
 */

#include "clave.h"

clave::clave(string ter, int pos, int fant) {

	this->termino = ter;
	this->posRelativa = pos;
	this->fantasma = fant;
}

clave::~clave() {
	// TODO Auto-generated destructor stub
}

string clave::getTermino() {

	return (this->termino);
}

int clave::getPosicion() {

	return (this->posRelativa);
}

int clave::getFantasma() {

	return (this->fantasma);
}




