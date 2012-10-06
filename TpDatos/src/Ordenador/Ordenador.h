/*
 * Ordenador.h
 *
 *  Created on: 19/09/2012
 *      Author: nachodz
 */

#ifndef ORDENADOR_H_
#define ORDENADOR_H_

#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <memory.h>
#include <sstream>
#include "../Constantes.h"


using namespace std;

struct tReg{
			int id;
			char termino[25];
}__attribute__((packed));

class Ordenador {

private:

    int tamBufOrd, tamBufLec_Esc;

public:

    Ordenador (int tamBufLec_Esc);
	virtual ~Ordenador ();
	void intercambio (tReg *buf, int a, int b);
	void ordenar (ifstream *archIn,int cantRegistrosArchivo);
	void cargaInicial (ifstream *archIn, tReg *buffer);
    void myheapsort (tReg *buffer,int tamHeap);
    void achicarMonticulo (tReg *bufferSort,int tamHeap,ofstream *salida);
    void copiarReg (tReg* regDestino,tReg* regOrigen);
    string IntToStr(int n);
    void correrBuffer (tReg* bufNuevo, tReg* bufViejo, int cantaPasar);
    void cargaBufferLectura (ifstream *archIn, tReg *buffer, int reg);
    void grabarBufferEscritura (ofstream *archIn, tReg *buffer, int reg);


};



#endif /* ORDENADOR_H_ */


//    void cargarBufIn (ifstream *arch, tReg *buffer);
//    void escribirRegOut (ofstream *archOut, tReg *buffer);
//    void cantBuffersIn (ifstream *arch, int *cantBuf);
//    void armarNuevoHeap (tReg *buffer);
