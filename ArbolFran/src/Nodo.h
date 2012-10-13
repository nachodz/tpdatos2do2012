/*
 * Nodo.h
 *
 *  Created on: 09/10/2012
 *      Author: francisco
 */

#ifndef NODO_H_
#define NODO_H_

#include <iostream>
#include <fstream>
#include "Constantes.h"
#include "registros.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cstring>

using namespace std;

class Nodo {

protected:

	int nivel;
	int numNodo;
	int espacioLibre;
	char *datos;

public:

	Nodo();
	virtual ~Nodo();
//	virtual void agregarElemento(tClave elemento);

// GETTERS Y SETTERS

	int getNivel();
	int getNumeroNodo();
	int getEspacioLibre();
	virtual int getReferencia();
	char* getDatos();

	void putNivel(int nivel);
	void putNumeroNodo(int numero);
	void putEspacioLibre(int espLibre);
	virtual void putReferencia(int referencia);
	void putDatos(char *datos);

	bool vacio();
	void disminuirEspacio(int tamanioDato);
	bool esRaiz();

	virtual tRegistroHoja leerRegistro(int *posicionInicial);
	virtual void ponerRegistro(tRegistroHoja, int *posicionInicial);

};

#endif /* NODO_H_ */
