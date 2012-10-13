/*
 * Persistidor.cpp
 *
 *  Created on: 09/10/2012
 *      Author: francisco
 */

#include "Persistidor.h"

Persistidor::Persistidor() {
	// TODO Auto-generated constructor stub

}

Persistidor::~Persistidor() {
	// TODO Auto-generated destructor stub
}

void Persistidor::persistirNodoHoja(Nodo *nodo, fstream *archivoArbol) {

	char *serial = new char[TAM_BLOQUE];
	char *nivel, *numNodo, *referencia, *espacioLibre;
	int i = 0;
	int niv = nodo->getNivel(), numeroNodo = nodo->getNumeroNodo();
	int esp = nodo->getEspacioLibre(), ref = nodo->getReferencia();

	nivel = (char*)&niv;
	numNodo = (char*)&numeroNodo;
	espacioLibre = (char*)&esp;
	referencia = (char*)&ref;

	memmove(serial, nivel, sizeof(int));
	i = i + sizeof(int);
	memmove(&serial[i], numNodo, sizeof(int));
	i = i + sizeof(int);
	memmove(&serial[i], referencia, sizeof(int));
	i = i + sizeof(int);
	memmove(&serial[i], espacioLibre, sizeof(int));
	i = i + sizeof(int);
	memmove(&serial[i], (nodo->getDatos()), TAM_BLOQUE - i);

	archivoArbol->seekp(numeroNodo * TAM_BLOQUE);
	archivoArbol->write(serial,TAM_BLOQUE);
	archivoArbol->flush();

	delete []serial;
//	delete []nivel;
//	delete []numNodo;
//	delete []referencia;
//	delete []espacioLibre;
}

void Persistidor::recuperarNodoHoja(Nodo * nodo, int numNodo, ifstream *archivoArbol) {

	char *deserial = new char[TAM_BLOQUE];
	char *nivel = new char[4], *numeroNodo = new char[4], *referencia = new char[4];
	char *espacioLibre = new char[4], *datos = new char[TAM_BLOQUE - TAM_METADATA];
	int *niv, *num, *ref, *esp;
	int i = 0;

	archivoArbol->seekg(numNodo * TAM_BLOQUE);
	archivoArbol->read(deserial,TAM_BLOQUE);

	memmove(nivel, deserial, sizeof(int));
	i = i + sizeof(int);
	memmove(numeroNodo,&deserial[i], sizeof(int));
	i = i + sizeof(int);
	memmove(referencia, &deserial[i], sizeof(int));
	i = i + sizeof(int);
	memmove(espacioLibre, &deserial[i], sizeof(int));
	i = i + sizeof(int);
	memmove(datos, &deserial[i], TAM_BLOQUE - i);

	niv = (int*)nivel;
	num = (int*)numeroNodo;
	ref = (int*)referencia;
	esp = (int*)espacioLibre;

	nodo->putDatos(datos);
	nodo->putEspacioLibre(*esp);
	nodo->putNivel(*niv);
	nodo->putNumeroNodo(*num);
	nodo->putReferencia(*ref);

	delete []deserial;
	delete []nivel;
	delete []numeroNodo;
	delete []referencia;
	delete []espacioLibre;
}





