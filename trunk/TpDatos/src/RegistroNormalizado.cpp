/*
 * RegistroNormalizado.cpp
 *
 *  Created on: 15/09/2012
 *      Author: francisco
 */

#include "RegistroNormalizado.h"


RegistroNormalizado::RegistroNormalizado(string termino, int ID, int tamanio) {
	this->tamPalabra = tamanio;
	this->termino = termino;
	this->ID = ID;
}

RegistroNormalizado::~RegistroNormalizado() {
	// TODO Auto-generated destructor stub
}

string RegistroNormalizado::getTermino() {
	return this->termino;
}

int RegistroNormalizado::getID() {
	return this->ID;
}

void RegistroNormalizado::guardar() {

}


void RegistroNormalizado::recuperar() {

}


