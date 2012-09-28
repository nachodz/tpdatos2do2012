/*
 * PersistenciaArbol.cpp
 *
 *  Created on: 27/09/2012
 *      Author: nacho
 */

#include "PersistenciaArbol.h"


PersistenciaArbol::PersistenciaArbol() {
	this->handlerBloque = new HandlerBloques();
}

PersistenciaArbol::~PersistenciaArbol() {
	// TODO Auto-generated destructor stub
}

bool PersistenciaArbol::guardarBloque (int nroBloque, Persistencia cadena){
	this->handlerBloque->guardarBloqueArbol((char*)cadena.toString().c_str(), nroBloque);
	return true;
}

Persistencia PersistenciaArbol::leerBloque (int nroBloque){
	Persistencia cadena;
	int uno = (nroBloque) * TAM_BLOQUE + TAM_BLOQUE;
	int dos = this->handlerBloque->getTamArchBloques();

	if  (uno <= dos){
		char* buffer = (char*)malloc(TAM_BLOQUE);
		this->handlerBloque->recuperarBloqueArbol(nroBloque, buffer);
		cadena.agregar(buffer,TAM_BLOQUE,0);
		free(buffer);
	}

	return cadena;
}
