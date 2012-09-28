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

#define PATH "/home/nachodz/Escritorio/Workspace/Prueba/Particiones/part"
#define CANTPARTES 400



using namespace std;

struct tReg{
			int id;
			char termino[25];
}__attribute__((packed));

class Ordenador {

private:
    int tamBufOrd;
public:
	Ordenador ();
	virtual ~Ordenador ();
	void intercambio (tReg *buf, int a, int b);
	void ordenar (ifstream *archIn,int cantReg);
	void cargaInicial (ifstream *archIn, tReg *buffer);
    void myheapsort (tReg *buffer,int tamHeap);
    void achicarMonticulo (tReg *bufferSort,int tamHeap,ofstream *salida);
    void copiarReg (tReg* regDestino,tReg* regOrigen);
    string IntToStr(int n);
    void correrBuffer (tReg* bufNuevo, tReg* bufViejo, int cantaPasar);


};



#endif /* ORDENADOR_H_ */


//    void cargarBufIn (ifstream *arch, tReg *buffer);
//    void escribirRegOut (ofstream *archOut, tReg *buffer);
//    void cantBuffersIn (ifstream *arch, int *cantBuf);
//    void armarNuevoHeap (tReg *buffer);
