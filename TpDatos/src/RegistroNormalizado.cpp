/*
 * RegistroNormalizado.cpp
 *
 *  Created on: 15/09/2012
 *      Author: francisco
 */

#include "RegistroNormalizado.h"


RegistroNormalizado::RegistroNormalizado(string termino, int ID) {
	this->termino = termino;
	this->ID = ID;
}

RegistroNormalizado::~RegistroNormalizado() {
	// TODO Auto-generated destructor stub
}

string RegistroNormalizado::putTermino() {
	return this->termino;
}

int RegistroNormalizado::putID() {
	return this->ID;
}
