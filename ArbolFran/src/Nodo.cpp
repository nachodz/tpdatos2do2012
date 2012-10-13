/*
 * Nodo.cpp
 *
 *  Created on: 09/10/2012
 *      Author: francisco
 */

#include "Nodo.h"

Nodo::Nodo() {

}

Nodo::~Nodo() {
	// TODO Auto-generated destructor stub
}


//GETTERS Y SETTERS

int Nodo::getNivel() {

	return (this->nivel);
}

int Nodo::getNumeroNodo() {

	return (this->numNodo);
}

char* Nodo::getDatos() {
	return (this->datos);
}

int Nodo::getEspacioLibre() {
	return (this->espacioLibre);
}

int Nodo::getReferencia() {

}

void Nodo::putNumeroNodo(int numero) {
	this->numNodo = numero;
}

void Nodo::putNivel(int nivel) {
	this->nivel = nivel;
}

void Nodo::putDatos(char* datos) {
	strcpy(this->datos, datos);
}

void Nodo::putEspacioLibre(int espacio) {
	this->espacioLibre = espacio;
}

void Nodo::putReferencia(int referencia) {

}



bool Nodo::vacio() {

	if (this->espacioLibre == TAM_BLOQUE - TAM_METADATA) {
		return true;
	}
	else
	{
		return false;
	}
}

void Nodo::disminuirEspacio(int tamanio) {

	this->espacioLibre = (this->espacioLibre - tamanio);
}

bool Nodo::esRaiz() {

	if(this->numNodo == 0) {
		return true;
	}
	else
	{
		return false;
	}
}

tRegistroHoja Nodo::leerRegistro(int *posicionInicial) {

}

void Nodo::ponerRegistro(tRegistroHoja registro, int *posicionInicial) {

}
