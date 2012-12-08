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
#include <list>
#include "../Normalizador/Normalizador.h"
#include "../Booleano/Booleano.h"
#include "../IdxFirmas/indice.h"
#include <string>
#include <sstream>

using namespace std;

class DiccionarioFrases {
public:
	DiccionarioFrases();
	virtual ~DiccionarioFrases();
	int crearArchivoFrases();
	string baja (int numeroRegistro);
	//Devuelve el nro de documento, si hubo un error devuelve -1
	int alta(string frase);
	void cargaInicial(int numeroDeFrases);
	void listarEnTexto();
	void modificacion(int numeroRegistro, string nuevaFrase, Booleano *indice);
	void modificacionFirmas(int numeroRegistro, string nuevaFrase, indice *indice);
};

#endif /* DICCIONARIOFRASES_H_ */
