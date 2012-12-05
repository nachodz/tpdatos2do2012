/*
 * gestorArchivoOcurrencias.h
 *
 *  Created on: 21/11/2012
 *      Author: francisco
 */

#ifndef GESTORARCHIVOOCURRENCIAS_H_
#define GESTORARCHIVOOCURRENCIAS_H_

#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include "../Ordenador/Ordenador.h"
#include "../Fusionador/Fusionador.h"
#include "../Constantes.h"

using namespace std;


struct tOcurrencia {
	int idTermino;
	int idFrase;
}__attribute__((packed));

class gestorArchivoOcurrencias { //(nroTermino,nroRegistro)

private:
	string rutaArchivo;
	int cantidadOcurrencias;

public:
	gestorArchivoOcurrencias(string ruta);
	virtual ~gestorArchivoOcurrencias();
	void leerRegistro(int numeroRegistro, int* idT, int* inR,ifstream *ocurrencias);
	void grabarRegistro(int , int);
	void sort(int carga);
	void eliminarArchivo();
	int getNumeroOcurrencias();
	void putNumeroOcurrencias(int numeroOcurrencias);
	void aumentarOcurrencias();
	bool finLectura(int registros);
	string intToStr(int n);
};

#endif /* GESTORARCHIVOOCURRENCIAS_H_ */
