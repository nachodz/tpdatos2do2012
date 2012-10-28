
#ifndef ALEATORIZADOR_H_
#define ALEATORIZADOR_H_

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdio.h>
#include "../Constantes.h"
#include "Aleatorizador.h"
#include <sys/stat.h>
#include <sys/types.h>
#include "../Ordenador/Ordenador.h"
#include "../Fusionador/Fusionador.h"

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
	void sortExterno(ifstream *archivoAordenar, int cantRegistros);
private:
	string intToStr(int n);

};

#endif /* ALEATORIZADOR_H_ */
