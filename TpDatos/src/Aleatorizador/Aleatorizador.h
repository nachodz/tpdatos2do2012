/*
 * Aleatorizador.h
 *
 *  Created on: 15/09/2012
 *      Author: francisco
 */

#ifndef ALEATORIZADOR_H_
#define ALEATORIZADOR_H_

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdio.h>
#include "Constantes.h"

using namespace std;

struct registroNormalizado{
		int ID;
		char termino[25];
	}__attribute__((packed));

class Aleatorizador {
private:

public:
	Aleatorizador();
	virtual ~Aleatorizador();
	void aleatorizarArchivo();
	void generarAchivoTabulado(int cantRegistros);
	void sortExterno();
};

#endif /* ALEATORIZADOR_H_ */
