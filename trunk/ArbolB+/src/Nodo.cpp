/*
 * Nodo.cpp
 *
 *  Created on: 27/09/2012
 *      Author: nacho
 */

#include "Nodo.h"

Nodo::Nodo() {
	// TODO Auto-generated destructor stub
}

Nodo::Nodo(int nivel) {
	this->setNivel(nivel);
	this->setCantidadClaves(0);
	this->setEspacioOcupado(0);

	//this->claves = new Clave[(TAM_EFECTIVO_NODO/(TAM_CONTROL_REGISTRO)) + 2];

}

Nodo::~Nodo() {
	// TODO Auto-generated destructor stub
}


//*********Getters y Setters*************
int Nodo::getNumero(){
	return this->numero;
}

void Nodo::setNumero(int numero){
	this->numero = numero;
}

int Nodo::getNivel(){
	return this->nivel;
}

void Nodo::setNivel(int nivel){
	this->nivel = nivel;
}

int Nodo::getEspacioOcupado(){
	return this->espacioOcupado;
}

void Nodo::setEspacioOcupado(int espacioOcupado){
	this->espacioOcupado = espacioOcupado;
}

int Nodo::getCantidadClaves(){
	return this->cantidadClaves;
}

void Nodo::setCantidadClaves(int cantidadClaves){
	this->cantidadClaves = cantidadClaves;
}
