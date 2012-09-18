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
#include "RegistroNormalizado.h"

using namespace std;

class Aleatorizador {
private:

public:
	Aleatorizador();
	virtual ~Aleatorizador();
	void aleatorizarArchivo(char ruta[]);
	void sortExterno();
};

#endif /* ALEATORIZADOR_H_ */
