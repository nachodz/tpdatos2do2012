/*
 * HandlerBloques.h
 *
 *  Created on: 27/09/2012
 *      Author: nacho
 */

#ifndef HANDLERBLOQUES_H_
#define HANDLERBLOQUES_H_

#include "Constante.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

class HandlerBloques {

private:

public:
	HandlerBloques();
	virtual ~HandlerBloques();

	/*
	 * Guarda el bloque pasado por referencia en la posicion pasada por parametro en el archivo de
	 * bloques.
	 * Pre: -
	 * Pos: -
	 */
	void guardarBloqueArbol(char* buffer, int nro_bloque);
	/*
	 * Obtiene el tamanio del archivo de bloques.
	 * Pre: -
	 * Pos: devuelve dicho tamanio.
	 */
	int getTamArchBloques() const;
	/*
	 * Carga el bloque que se encuentra en la posicion pasada por parametro desde el archivo de
	 * bloques a memoria principal para su posterior lectura o modificacion.
	 * Pre: -
	 * Pos: Devuelve en un buffer el bloque leído para su correcta hidratación luego por la estructura
	 * que lo invocó.
	 */
	void recuperarBloqueArbol(int nro_bloque, char* buffer);
};

#endif /* HANDLERBLOQUES_H_ */

