/*
 * gestorArchivoDeTerminos.h
 *
 *  Created on: 21/11/2012
 *      Author: francisco
 */

#ifndef GESTORARCHIVODETERMINOS_H_
#define GESTORARCHIVODETERMINOS_H_

#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include "../Constantes.h"

using namespace std;


class gestorArchivoDeTerminos {

private:
	string rutaArchivo;
	int cantidadTerminos;

public:
	gestorArchivoDeTerminos(string rutaArchivo);
	virtual ~gestorArchivoDeTerminos();
	void agregarTermino(string palabra);
	int buscarPosicionTermino(string palabra);
	int getCantidadElementos();
	void putCantidadElementos(int numeroTerminos);
	void aumentarCantidadElementos();
};

#endif /* GESTORARCHIVODETERMINOS_H_ */
