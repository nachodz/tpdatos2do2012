
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
//#include "../Gestor/gestorArchivoOcurrencias.h"


using namespace std;

struct Ocurrencias {
	int idTermino;
	int idFrase;
}__attribute__((packed));

class Ordenador {

private:

    int tamBufOrd;

public:

    Ordenador (int tamBufLec_Esc);
	virtual ~Ordenador ();
	void intercambio (Ocurrencias *buf, int a, int b);
	int ordenar (ifstream *archIn);
	void cargaInicial (ifstream *archIn, Ocurrencias *buffer);
    void myheapsort (Ocurrencias *buffer,int tamHeap);
    void achicarMonticulo (Ocurrencias *bufferSort,int tamHeap,ofstream *salida);
    void copiarReg (Ocurrencias* regDestino,Ocurrencias* regOrigen);
    string IntToStr(int n);
    void correrBuffer (Ocurrencias* bufNuevo, Ocurrencias* bufViejo, int cantaPasar);
    void cargaBufferLectura (ifstream *archIn, Ocurrencias *buffer, int reg);
    void grabarBufferEscritura (ofstream *archIn, Ocurrencias *buffer, int reg);
    int mayor(Ocurrencias ocurrrencia1, Ocurrencias ocurrencia2);
    void ordenamientoEnRam(ifstream *archIns);


};

#endif /* ORDENADOR_H_ */
