/*
 * HandlerArchivoDeTerminos.h
 *
 *  Created on: 21/11/2012
 *      Author: francisco
 */

#ifndef HANDLERARCHIVODETERMINOS_H_
#define HANDLERARCHIVODETERMINOS_H_

#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include "../Constantes.h"

using namespace std;


class HandlerArchivoDeTerminos {

private:
	string rutaArchivo;
	int cantidadTerminos;

public:
	HandlerArchivoDeTerminos(string rutaArchivo);
	virtual ~HandlerArchivoDeTerminos();
	void agregarTermino(string palabra);
	int buscarPosicionTermino(string palabra);
	int getCantidadElementos();
	void putCantidadElementos(int numeroTerminos);
	void aumentarCantidadElementos();
};

#endif /* HANDLERARCHIVODETERMINOS_H_ */
