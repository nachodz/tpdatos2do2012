/*
 * mapaBits.h
 *
 *  Created on: 17/11/2012
 *      Author: francisco
 */

#ifndef MAPABITS_H_
#define MAPABITS_H_

#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>

#define TAMANIO_BINARIO 16

using namespace std;

class mapaBits {

private:
	int tamanio;
	unsigned short int* mapa;
public:
	mapaBits(int tamanio);
	virtual ~mapaBits();
	char* serializar();
	void hidratar(char*serial);
	int getTamanio();
	unsigned short int getNumero(int posicion);
	void putNumero(int posicion, int numero);
	int* generarBinario(unsigned short int numero);
	int generarDecimal(int* binario);
	int primerRegitroLibre();
	void cambiarEstadoRegistro(int numeroRegistro);
	void mostrar();
	bool libre(int numeroRegistro);
};

#endif /* MAPABITS_H_ */
