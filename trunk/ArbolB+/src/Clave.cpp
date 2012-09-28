/*
 * clave.cpp
 *
 *  Created on: 27/09/2012
 *      Author: francisco
 */

#include "Clave.h"

Clave::Clave(string ter, int pos, int fant) {

	this->termino = ter;
	this->posRelativa = pos;
	this->fantasma = fant;
}

Clave::~Clave() {
	// TODO Auto-generated destructor stub
}

string Clave::getTermino() {

	return (this->termino);
}

int Clave::getPosicion() {

	return (this->posRelativa);
}

int Clave::getFantasma() {

	return (this->fantasma);
}

