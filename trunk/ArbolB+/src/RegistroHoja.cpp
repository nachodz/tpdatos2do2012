/*
 * RegistroHoja.cpp
 *
 *  Created on: 25/09/2012
 *      Author: francisco
 */

#include "RegistroHoja.h"

RegistroHoja::RegistroHoja(int letrasIguales, int letrasDistintas, string palabra, int posicion, int fantasma) {

	this->letrasIguales = letrasIguales;
	this->letrasDistintas = letrasDistintas;
	this->palabra = palabra;
	this->posicion = posicion;
	this->fantasma = 0;
}

RegistroHoja::~RegistroHoja() {
	// TODO Auto-generated destructor stub
}

int RegistroHoja::getLetrasIguales() {

	return (this->letrasIguales);
}

int RegistroHoja::getLetrasDistintas() {

	return (this->letrasDistintas);
}

string RegistroHoja::getPalabra() {

	return (this->palabra);
}

int RegistroHoja::getPosicion() {

	return (this->posicion);
}

int RegistroHoja::getFantasma() {

	return (this->fantasma);
}

