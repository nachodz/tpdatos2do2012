/*
 * HandlerBloques.cpp
 *
 *  Created on: 27/09/2012
 *      Author: nacho
 */

#include "HandlerBloques.h"

HandlerBloques::HandlerBloques() {
	// TODO Auto-generated constructor stub

}

HandlerBloques::~HandlerBloques() {
	// TODO Auto-generated destructor stub
}

void HandlerBloques::guardarBloqueArbol(char* buffer, int nro_bloque){
	fstream ff;
	ff.open(ARCHIVOARBOLBMAS, fstream::in | fstream::out);
	if (!ff.is_open()){
		ff.open(ARCHIVOARBOLBMAS, fstream::out);
		ff.close();
		ff.open(ARCHIVOARBOLBMAS, fstream::in | fstream::out);
	}
		int offset_bloque = nro_bloque * TAM_BLOQUE;

		// Escribo libro en el archivo de bloques
		ff.seekg(offset_bloque);
		ff.write(buffer, TAM_BLOQUE);
		ff.flush();
		ff.close();
}

int HandlerBloques::getTamArchBloques() const {
	fstream arch;
	int tam;

	arch.open(ARCHIVOARBOLBMAS, fstream::in);
	if (!arch.is_open()){
		arch.open(ARCHIVOARBOLBMAS, fstream::out);
		arch.close();
		arch.open(ARCHIVOARBOLBMAS, fstream::in);
	}
	arch.seekg(0, fstream::end);
	tam = arch.tellg();
	arch.close();

	return tam;
}


void HandlerBloques::recuperarBloqueArbol(int nro_bloque, char* Buffer){
	fstream ff;
	ff.open(ARCHIVOARBOLBMAS, fstream::in);
	if (!ff.is_open()){
		ff.open(ARCHIVOARBOLBMAS, fstream::out);
		ff.close();
	}else{
		int offset_bloque = nro_bloque * TAM_BLOQUE;
		// Me posiciono en el archivo de bloques
		ff.seekg(offset_bloque);
		ff.read(Buffer, TAM_BLOQUE);
		ff.close();
	}
}

