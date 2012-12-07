/*
 * gestorArchivoPorciones.h
 *
 *  Created on: 21/11/2012
 *      Author: francisco
 */

#ifndef GESTORARCHIVOPORCIONES_H_
#define GESTORARCHIVOPORCIONES_H_

#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include "../mapaBits.h"
#include "../Constantes.h"

using namespace std;

class gestorArchivoPorciones {

private:
	string rutaArchivo;
	int numeroFirmas;

public:
	gestorArchivoPorciones(string ruta);
	virtual ~gestorArchivoPorciones();
	mapaBits* obtenerFirma(int numeroTermino);
	void guardarFirma(mapaBits firma, int numeroTermino);
	int getNumeroFirmas();
	void putNumeroFirmas(int numeroFirmas);
	void aumentarCantidadFirmas();

};

#endif /* GESTORARCHIVOPORCIONES_H_ */
