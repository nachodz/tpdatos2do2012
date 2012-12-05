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
#include "../Comun/mapaBits.h"
#include <string>
#include <sstream>

//TODO: ver si van aca!
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
	//Devuelve el nro de documento, si hubo un error devuelve -1
	int alta(string frase);
	void cargaInicial(int numeroDeFrases);
	void listarEnTexto();

};

#endif /* DICCIONARIOFRASES_H_ */
