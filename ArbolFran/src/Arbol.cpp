/*
 * Arbol.cpp
 *
 *  Created on: 07/10/2012
 *      Author: francisco
 */

#include "Arbol.h"


Arbol::Arbol() {

	fstream archivoArbol;
	archivoArbol.open(PATH_ARBOL,ios::in | ios::out | ios::trunc | ios::binary);

	this->cantNodos = 1;
	char *datos = new char[TAM_BLOQUE - TAM_METADATA];

	if(archivoArbol && datos) {

		this->raiz = new NodoHoja(0,0,0,TAM_BLOQUE - TAM_METADATA,datos);
		this->actual = this->raiz;


		(this->persistidorArbol).persistirNodoHoja(this->raiz, &archivoArbol);

		archivoArbol.close();
	}
	else {
		cout << "No puede abrirse el archivo del arbol o no hay espacio en memoria";
	}

	delete []datos;

}

Arbol::~Arbol() {
	// TODO Auto-generated destructor stub
}

void Arbol::cargaInicial(int cantRegistros) {

	ifstream archivoAcargar;
	tRegistroDiccionario *bufferLectura = new tRegistroDiccionario[TAM_BUFFER_LEC];
	tClave *claves = new tClave[TAM_BUFFER_LEC];
	int posicion = 0;

	archivoAcargar.open(PATH_ARCHIVO_A_ALEATORIZAR, ios::binary);

	if (archivoAcargar && claves && bufferLectura) {

		archivoAcargar.read((char*)bufferLectura,(sizeof(tRegistroDiccionario)*TAM_BUFFER_LEC));

		this->generarClaves(bufferLectura,claves,TAM_BUFFER_LEC, &posicion);
		cantRegistros = cantRegistros - TAM_BUFFER_LEC;

		while (cantRegistros >= TAM_BUFFER_LEC) {

			for (int i = 0; i < TAM_BUFFER_LEC; i++) {

				this->alta(claves[i]);
			}

			archivoAcargar.read((char*)bufferLectura,(sizeof(tRegistroDiccionario)*TAM_BUFFER_LEC));

			this->generarClaves(bufferLectura,claves,TAM_BUFFER_LEC, &posicion);
			cantRegistros = cantRegistros - TAM_BUFFER_LEC;

		}

		if (cantRegistros != 0) {

			archivoAcargar.read((char*)bufferLectura,(sizeof(tRegistroDiccionario)*cantRegistros));

			this->generarClaves(bufferLectura,claves,TAM_BUFFER_LEC, &posicion);

			for (int i = 0; i < cantRegistros; i++) {

				this->alta(claves[i]);
			}
		}
	}
	else {
		cout << "No se pudo abrir el archivo aleatorizado o no hay espacio en memoria";
	}

	delete []bufferLectura;
	delete []claves;
}

void Arbol::alta(tClave registro) {


}

tClave Arbol::busqueda(tClave registro) {

	tClave reg;

	return reg;
}

void Arbol::generarClaves(tRegistroDiccionario *buffer, tClave *claves, int cant, int *pos) {

	for (int i = 0; i < cant; i++) {

		tClave clave;
		clave.fantasma = 0;
		clave.posicion = *pos;
		strcpy (clave.termino, buffer[i].termino);
		claves[i] = clave;
		(*pos)++;
	}
}

void Arbol::buscarNodoRec(tClave elemento) {

}


void Arbol::buscarNodo(tClave elemento){

	this->actual = this->raiz;

	this->buscarNodoRec(elemento);

}

void Arbol::aumentarCantNodo() {
	(this->cantNodos)++;
}

int Arbol::getCantNodo() {
	return (this->cantNodos);
}
