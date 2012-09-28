/*
 * Persistencia.h
 *
 *  Created on: 27/09/2012
 *      Author: nacho
 */

#ifndef PERSISTENCIA_H_
#define PERSISTENCIA_H_

#include <string>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <sstream>
#include <string.h>

using namespace std;

class Persistencia {
private:

	string bytes;

public:

	Persistencia();
	Persistencia(string bytes);
	virtual ~Persistencia();

	bool estaVacia() const;
	unsigned int getTamanio() const;
	int leerEntero(unsigned int inicio);
	string toString() const;
	Persistencia leer(unsigned int inicio, unsigned int tamanio) const;
	bool leer(char* buffer, unsigned int inicio,unsigned int tamanio)const;
	bool agregar(void* valor, unsigned int tamanio, unsigned int posicion);
	bool agregar(const Persistencia& bytes,unsigned int posicion);

	//Getters y Setters
	string getBytes();
	void setBytes(const string &bytes);

};

#endif /* PERSISTENCIA_H_ */
