/*
 * OrdenadorTP1.h
 *
 *  Created on: 05/12/2012
 *      Author: nacho
 */

#ifndef ORDENADORTP1_H_
#define ORDENADORTP1_H_

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

class OrdenadorTP1 {

private:

    int tamBufOrd, tamBufLec_Esc;

public:

    OrdenadorTP1 (int tamBufLec_Esc);
	virtual ~OrdenadorTP1 ();
	void intercambio (tReg *buf, int a, int b);
	int ordenar (ifstream *archIn,int cantRegistrosArchivo);
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
