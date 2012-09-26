/*
 * Normalizador.cpp
 *
 *  Created on: 12/09/2012
 *      Author: francisco
 */

#include "Normalizador.h"



Normalizador::Normalizador(){
	// TODO Auto-generated constructor stub

}

Normalizador::~Normalizador(){
	// TODO Auto-generated destructor stub
}

void Normalizador::normalizarArchivo() {

	char rutaDic[] = PATH_DICCIONARIO, rutaNor[] = PATH_ARCHIVO_NORMALIZADO;

	ifstream diccionario(rutaDic);
	ofstream diccionarioNormalizado(rutaNor);

	string palabraDiccionario;

	if ((diccionario) && (diccionarioNormalizado)){

		diccionario>>palabraDiccionario;
		this->normalizarPalabra(&palabraDiccionario);

		cout << MSJ_PROCESANDO << endl;
		while (!diccionario.eof()) {

			if (!(this->esStopword(palabraDiccionario))) {

				diccionarioNormalizado<<palabraDiccionario<<endl;
			}
			diccionario>>palabraDiccionario;
			this->normalizarPalabra(&palabraDiccionario);
		}

		diccionario.close();
		diccionarioNormalizado.close();
		cout<<"Diccionario normalizado correctamente"<<endl;
	}
	else
		cout<<"error al normalizar el diccionario"<<endl;
}

void Normalizador::normalizarPalabra(string *unaPalabra){
	this->cortarPalabra(unaPalabra);
	this->sacarAcentos(unaPalabra);
	this->sacarMayusculas(unaPalabra);
}


void Normalizador::cortarPalabra(string *unaPalabra){
	int posicion;

	posicion = this->posicionCaracter(*unaPalabra,'/');
	unaPalabra->erase(posicion,unaPalabra->size());
}

void Normalizador::sacarAcentos(string *unaPalabra){
	char letra;
	int tamanioPalabra, posicion = 0;

	tamanioPalabra = ((unaPalabra->size()) - 1);
	while (posicion <= tamanioPalabra){
		letra = unaPalabra->at(posicion);
		this->cambiarLetra(unaPalabra,letra,posicion);
		posicion++;
	}
}


void Normalizador::sacarMayusculas(string *unaPalabra){
	transform(unaPalabra->begin(), unaPalabra->end(), unaPalabra->begin(), (int( * )(int))std::tolower);
}


int Normalizador::posicionCaracter(string unaPalabra, char L){
	int posicion = 0, tamanioPalabra = unaPalabra.size();
	char letraExtraida;

	letraExtraida = unaPalabra.at(posicion);
	while ((letraExtraida != L) && (posicion != (tamanioPalabra - 1))){
		posicion++;
		letraExtraida = unaPalabra.at(posicion);
	}
	return posicion;
}


void Normalizador::cambiarLetra(string *unaPalabra, char L, int pos){
	int ascii = L;
	switch(ascii){
	case(-31): case(-63): unaPalabra->operator [](pos) = 'a';
					break;
	case(-23): case(-55): unaPalabra->operator [](pos) = 'e';
					break;
	case(-19): case(-51): unaPalabra->operator [](pos) = 'i';
					break;
	case(-13): case(-45):unaPalabra->operator [](pos) = 'o';
					break;
	case(-6): case(-4): case(-38): case(-36): unaPalabra->operator [](pos) = 'u';
					break;
	default: break;
	}
}

bool Normalizador::esStopword(string unaPalabra) {

	ifstream words(PATH_STOPWORDS);

	string stopword;

	words >> stopword;

	while(!words.eof()) {

		if (stopword == unaPalabra){
			return true;
		}
		else
			words >> stopword;
	}

return false;
}





