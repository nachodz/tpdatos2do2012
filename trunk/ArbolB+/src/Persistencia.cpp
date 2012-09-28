/*
 * Persistencia.cpp
 *
 *  Created on: 27/09/2012
 *      Author: nacho
 */

#include "Persistencia.h"

Persistencia::Persistencia() {
	// TODO Auto-generated destructor stub
}

Persistencia::Persistencia(string bytes) {
	this->bytes = bytes;
}

Persistencia::~Persistencia() {
	// TODO Auto-generated destructor stub
}

bool Persistencia::estaVacia() const {
	return (this->getTamanio() == 0);
}

int Persistencia::leerEntero(unsigned int inicio){
	int n = -1;
	char buffer[sizeof(int)];
	bool leido = this->leer(buffer,inicio,sizeof(int));
	if(leido) memcpy(&n,buffer,sizeof(int));
	return n;
}

unsigned int Persistencia::getTamanio() const {
	return this->bytes.length();
}

bool Persistencia::leer(char* buffer, unsigned int inicio,unsigned int tamanio)const {
	bool exito = true;
	Persistencia aux = this->leer(inicio,tamanio);
	if(aux.getTamanio()==0){
		exito = false;
	}else{
		memcpy(buffer,aux.bytes.data(),tamanio);
		exito = true;
	}
	return exito;
}

Persistencia Persistencia::leer(unsigned int inicio, unsigned int tamanio) const {
	if (inicio + tamanio > getTamanio()) {
		return Persistencia("");
	}
	return this->bytes.substr(inicio,tamanio);
}

string Persistencia::toString() const {
	return this->bytes;
}

bool Persistencia::agregar(void* valor, unsigned int tamanio, unsigned int posicion){
	bool exito = true;
		string cadena;
		char* buffer = (char*)malloc(tamanio);
		memcpy(buffer,valor,tamanio);
		cadena.append(buffer,tamanio);
		exito = agregar(cadena,posicion);
		free(buffer);
	return exito;
}

bool Persistencia::agregar(const Persistencia& bytes,unsigned int posicion) {
	bool exito = true;
	if (posicion > this->bytes.length()) {
		exito = false;
	}else{
		this->bytes.insert(posicion,bytes.toString());
	}
	return exito;
}


//************Getters y Setters***************
string Persistencia::getBytes(){
	return this->bytes;
}

void Persistencia::setBytes(const string &bytes) {
	this->bytes = bytes;
}
