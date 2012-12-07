/*
 * HandlerArchivoPorciones.h
 *
 *  Created on: 21/11/2012
 *      Author: francisco
 */

#ifndef HANDLERARCHIVOPORCIONES_H_
#define HANDLERARCHIVOPORCIONES_H_

#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include "../Comun/mapaBits.h"
#include "../Constantes.h"

using namespace std;

class HandlerArchivoPorciones {

private:
	string rutaArchivo;
	int numeroFirmas;

public:
	HandlerArchivoPorciones(string ruta);
	virtual ~HandlerArchivoPorciones();
	mapaBits* obtenerFirma(int numeroTermino);
	void guardarFirma(mapaBits firma, int numeroTermino);
	int getNumeroFirmas();
	void putNumeroFirmas(int numeroFirmas);
	void aumentarCantidadFirmas();

};

#endif /* HANDLERARCHIVOPORCIONES_H_ */
