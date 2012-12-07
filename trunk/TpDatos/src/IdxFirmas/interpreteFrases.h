/*
 * interpreteFrases.h
 *
 *  Created on: 22/11/2012
 *      Author: francisco
 */

#ifndef INTERPRETEFRASES_H_
#define INTERPRETEFRASES_H_

#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include "../Comun/mapaBits.h"
#include "../Normalizador/Normalizador.h"

using namespace std;

class interpreteFrases {
private:
	mapaBits *mapa;
	int lecturas;

public:
	interpreteFrases(fstream* archivoFrases);
	virtual ~interpreteFrases();
	char* leerFrase(fstream* archivoFrases);
	int getLecturas();
	void aumentarLecturas();
	string* parsearFrase(string frase, int* cantidadTerminos);
	void normalizarTerminos(string* terminos, int numTerminos);
	string* filtroStopword(string* terminos, int *numTerminos);
	int elementosAleer();
};



#endif /* INTERPRETEFRASES_H_ */
