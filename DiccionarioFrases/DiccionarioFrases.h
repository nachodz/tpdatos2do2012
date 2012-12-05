/*
 * DiccionarioFrases.h
 *
 *  Created on: 05/12/2012
 *      Author: ignacio
 */

#ifndef DICCIONARIOFRASES_H_
#define DICCIONARIOFRASES_H_

#include <iostream>
#include <fstream>
#include "mapaBits.h"
#include <string>
#include <sstream>


#define TAMANIO_REGISTRO_FRASES 256
#define PATH_ARCHIVO_FRASES "Frases celebres.dat"
#define PATH_FRASES "Frases_Celebres.csv"
#define CANTIDAD_DE_FRASES_A_CARGAR 60
#define INFORME_FRASES "Frases celebre.txt"

using namespace std;

class DiccionarioFrases {
public:
	DiccionarioFrases();
	virtual ~DiccionarioFrases();
	int crearArchivoFrases();
	void baja (int numeroRegistro);
	void alta(string frase);
	void cargaInicial(int numeroDeFrases);
	void listarEnTexto();

};

#endif /* DICCIONARIOFRASES_H_ */
