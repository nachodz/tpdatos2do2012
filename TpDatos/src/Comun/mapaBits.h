
#ifndef MAPABITS_H_
#define MAPABITS_H_

#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>
#include "../Constantes.h"

using namespace std;

class mapaBits {

private:
	int tamanio;
	int longPorcion;
	unsigned short int* porcion;
public:
	mapaBits();
	mapaBits(int tamanio);
	virtual ~mapaBits();
	char* serializar();
	void hidratar(char*serial);
	int getTamanio();
	unsigned short int getNumero(int posicion);
	void putNumero(int posicion, int numero);
	int* generarBinario(unsigned short int numero);
	int generarDecimal(int* binario);
	void cambiarEstadoRegistro(int numeroRegistro);
	void mostrar();
	bool libre(int numeroRegistro);
	int getElementosOcupados();
	int primerRegitroLibre();
	void inicializar();
	void asignarBit(int bit);
};

#endif /* MAPABITS_H_ */
