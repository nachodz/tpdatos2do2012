/*
 * NodoHoja.cpp
 *
 *  Created on: 05/10/2012
 *      Author: nacho
 */

#include "NodoHoja.h"
#include "Constantes.h"

//CONTRUCTOR Y DESTRUCTOR

NodoHoja::NodoHoja(int nivel, int numNodoHoja,int refProxHoja, int espLibre, char* datos){

	this->nivel = nivel;
	this->numNodo = numNodoHoja;
	this->refProxHoja = refProxHoja;
	this->espacioLibre = espLibre;
	this->datos = datos;
}


NodoHoja::~NodoHoja() {

}


void NodoHoja::putReferencia(int referencia) {
	this->refProxHoja = referencia;
}

int NodoHoja::getReferencia() {
	return this->refProxHoja;
}

tRegistroHoja NodoHoja::leerRegistro(int *posicionInicial) {

	int *letrasIguales, *longitud, *posicion;
	unsigned short int *fantasma;
	char *iguales = new char[4], *distintas = new char[4], *pos = new char[4], *ghost = new char[2];
	char *palabra = new char[25];
	tRegistroHoja unRegistro;

	memmove(iguales,&(this->datos[*posicionInicial]),sizeof(int));
	*posicionInicial = *posicionInicial + sizeof(int);
	letrasIguales = (int*)iguales;
	unRegistro.letrasIguales = *letrasIguales;

	memmove(distintas,&(this->datos[*posicionInicial]),sizeof(int));
	*posicionInicial = *posicionInicial + sizeof(int);
	longitud = (int*)distintas;
	unRegistro.letrasDistintas = *longitud;

	memmove(palabra,&(this->datos[*posicionInicial]),*longitud);
	*posicionInicial = *posicionInicial + *longitud;
	unRegistro.termino = (string)palabra;

	memmove(pos,&(this->datos[*posicionInicial]),sizeof(int));
	*posicionInicial = *posicionInicial + sizeof(int);
	posicion = (int*)pos;
	unRegistro.posicion = *posicion;

	memmove(ghost,&(this->datos[*posicionInicial]),sizeof(unsigned short int));
	*posicionInicial = *posicionInicial + sizeof(unsigned short int);
	fantasma = (unsigned short int*)ghost;
	unRegistro.fantasma = *fantasma;

	delete []iguales;
	delete []distintas;
	delete []pos;
	delete []ghost;
	delete []palabra;

	return unRegistro;
}

void NodoHoja::ponerRegistro(tRegistroHoja registro, int *posicionInicial) {

	char *iguales, *distintas, *posicion, *fantasma;
	int espacio = 0;
	iguales = (char*)&registro.letrasIguales;
	distintas = (char*)&registro.letrasDistintas;
	posicion = (char*)&registro.posicion;
	fantasma = (char*)&registro.fantasma;

	memmove(&(this->datos[*posicionInicial]),iguales,sizeof(int));
	*posicionInicial = *posicionInicial + sizeof(int);
	espacio = espacio + sizeof(int);

	memmove(&(this->datos[*posicionInicial]),distintas,sizeof(int));
	*posicionInicial = *posicionInicial + sizeof(int);
	espacio = espacio + sizeof(int);

	memmove(&(this->datos[*posicionInicial]),(registro.termino).c_str(),(registro.letrasDistintas));
	*posicionInicial = *posicionInicial + (registro.letrasDistintas);
	espacio = espacio + registro.letrasDistintas;

	memmove(&(this->datos[*posicionInicial]),posicion,sizeof(int));
	*posicionInicial = *posicionInicial + sizeof(int);
	espacio = espacio + sizeof(int);

	memmove(&(this->datos[*posicionInicial]),fantasma,sizeof(unsigned short int));
	*posicionInicial = *posicionInicial + sizeof(unsigned short int);
	espacio = espacio + sizeof(unsigned short int);

	this->disminuirEspacio(espacio);
}
