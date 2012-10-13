#ifndef REGISTROS_H_
#define REGISTROS_H_


#include "Constantes.h"
#include <string.h>
#include <string>

using namespace std;

struct tClave {
	char termino[25];
	int posicion;
	unsigned short int fantasma;
}__attribute__((packed));

struct tRegistroHoja {
	short int letrasIguales;
	short int letrasDistintas;
	string termino;
	int posicion;
	unsigned short int fantasma;

};


struct tRegistroDiccionario {
	int aleatorio;
	char termino[25];
}__attribute__((packed));

//struct tRegistroNodoInterno {
//
//};
#endif
