/*
 * interpreteFrases.cpp
 *
 *  Created on: 22/11/2012
 *      Author: francisco
 */

#include "interpreteFrases.h"

interpreteFrases::interpreteFrases(fstream* archivoFrases) {

	this->mapa = new mapaBits(TAMANIO_REGISTRO_FRASE * BYTE);
	this->lecturas = 0;
	char*serial = new char[TAMANIO_REGISTRO_FRASE];

	if(!serial)
		cout << "El programa no hallo memoria disponible" << endl;
	else {
		archivoFrases->seekg(0,ios::beg);
		archivoFrases->read(serial,TAMANIO_REGISTRO_FRASE);
		(this->mapa)->hidratar(serial);
	}
	delete[] serial;
}

interpreteFrases::~interpreteFrases() {
	(this->mapa)->~mapaBits();
}

char* interpreteFrases::leerFrase(fstream* archivoFrases) {

	char*frase = new char[TAMANIO_REGISTRO_FRASE];

	if (!frase)
		cout << "El programa no encontro memoria disponible" << endl;

	else {

		int posicion = archivoFrases->tellg()/TAMANIO_REGISTRO_FRASE;

		if (!(this->mapa)->libre(posicion)) {
			archivoFrases->read(frase,TAMANIO_REGISTRO_FRASE);
			this->aumentarLecturas();
		}
	}
	return frase;
}

int interpreteFrases::getLecturas() {
	return this->lecturas;
}

void interpreteFrases::aumentarLecturas() {
	this->lecturas++;
}

string* interpreteFrases::parsearFrase(string frase, int* cantidadTerminos) {

	string auxiliar;
	char ultimo;
	string* vectorPalabras = new string[TOPE_TERMINOS_RELEVANTES];
	int posicion, posUltimoEspacio;

	posicion = frase.find_first_of('	');
	frase = frase.substr(posicion+2,frase.size());
	posicion = frase.find_first_of('	');

	if(posicion != -1) {
		frase = frase.substr(posicion+2,frase.size());
	}

	int i = 0;
	posUltimoEspacio = frase.find_last_of(' ');
	posicion = frase.find_first_of(' ');

	while (posicion != posUltimoEspacio) {

		auxiliar = frase.substr(0,posicion);

		ultimo = auxiliar[auxiliar.size()-1];

		if ((ultimo == '.')||(ultimo == ',')||(ultimo == ':')||(ultimo == ';'))
			auxiliar = auxiliar.substr(0,auxiliar.size()-1);

		vectorPalabras[i] = auxiliar;
		frase = frase.substr(posicion+1);
		posUltimoEspacio = frase.find_last_of(' ');
		posicion = frase.find_first_of(' ');
		i++;
	}

	auxiliar = frase.substr(0,posicion);
	frase = frase.substr(posicion+1);

	ultimo = auxiliar[auxiliar.size()-1];

	if ((ultimo == '.')||(ultimo == ',')||(ultimo == ':')||(ultimo == ';'))
		auxiliar = auxiliar.substr(0,auxiliar.size()-1);

	vectorPalabras[i] = auxiliar;
	i++;
	auxiliar = frase;
	ultimo = auxiliar[auxiliar.size()-1];

	if ((ultimo == '.')||(ultimo == ',')||(ultimo == ':')||(ultimo == ';'))
		auxiliar = auxiliar.substr(0,auxiliar.size()-1);

	vectorPalabras[i] = auxiliar;
	i++;
	*cantidadTerminos = i;
	return vectorPalabras;
}

void interpreteFrases::normalizarTerminos(string*terminos, int numTerminos) {

	Normalizador* unNormalizador = new Normalizador();

	for (int i = 0; i < numTerminos; i++)
		unNormalizador->normalizarPalabra(&(terminos[i]));
}

string* interpreteFrases::filtroStopword(string* terminos, int* numTerminos) {

	ifstream stopwords;
	stopwords.open(PATH_STOPWORDS);
	int cantStopwords = 0, numeroFiltrado = 0;

	if (!stopwords) {
		cout << "Error al abrir archivo de stopwords" << endl;
		return terminos;
	}
	else {

		string* arrayStopwords = new string[NUM_STOPWORDS];
		string* vectorFiltrado = new string[*numTerminos];

		if((!arrayStopwords)&&(!vectorFiltrado)) {
			cout << "No se pudo reservar memoria para stopwords" << endl;
			return terminos;
		}

		else {

			stopwords >> arrayStopwords[cantStopwords];
			cantStopwords++;

			while (!(stopwords.eof())) {
				stopwords >> arrayStopwords[cantStopwords];
				cantStopwords++;
			}
			stopwords.close();

			for(int j = 0; j < *numTerminos; j++) {
				bool encontrado = false;
				int k = 0;
				while((!encontrado) && k < cantStopwords) {
					if(terminos[j] == arrayStopwords[k])
						encontrado = true;
					k++;
				}
				if (!encontrado) {
					vectorFiltrado[numeroFiltrado] = terminos[j];
					numeroFiltrado++;
				}
			}
			delete[] arrayStopwords;
			*numTerminos = numeroFiltrado;
 			return vectorFiltrado;
		}
	}
}

int interpreteFrases::elementosAleer() {
	return ((this->mapa)->getElementosOcupados());
}
