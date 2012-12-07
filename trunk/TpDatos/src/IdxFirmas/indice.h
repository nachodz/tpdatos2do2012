/*
 * indice.h
 *
 *  Created on: 23/11/2012
 *      Author: francisco
 */

#ifndef INDICE_H_
#define INDICE_H_

#include "../ArbolBMas/ArbolBMas.h"
#include "../Handler/HandlerArchivoDeTerminos.h"
#include "../Handler/HandlerArchivoOcurrencias.h"
#include "../Handler/HandlerArchivoPorciones.h"
#include "interpreteFrases.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include "../Comun/mapaBits.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include "../ArbolBMas/Elementos.h"
#include "../ArbolBMas/Clave.h"

using namespace std;

struct regOcurrencia {
	int idTermino;
	int idRegistro;
}__attribute__((packed));

class indice {

private:

	ArbolBMas* lexico;
	HandlerArchivoDeTerminos *gestorArchivoTerminos;
	HandlerArchivoOcurrencias *gestorArchivoDeOcurrencias;
	HandlerArchivoPorciones *gestorArchivoDePorciones;
	int tamanioFirma;

public:
	indice(string rutaLexico, string rutaTerminos,string rutaOcurrencias, string rutaPorciones,int tamanioFirma);
	virtual ~indice();
	int getTamanioFirma();
	void cargaInicialIndice(string rutaCarga);
	void generarFirmas();
	Elementos* buscarEnArbol (string palabra, ArbolBMas* arbol,bool * result);
	string intToString(int n);
	void guardarInformacion();
	void recuperarInformacion();
	void agregarTerminosAlIndice(string frase, int registro);
	void eliminarTerminosDelIndice(string frase, int registro);
	double buscarFrases(string frase);
	int* identificarRegistro(mapaBits* porciones, int numPorciones, int* registrosValidos);
	void mostrarFirma(string palabra);
};

#endif /* INDICE_H_ */
