/*
 * Normalizador.h
 *
 *  Created on: 12/09/2012
 *      Author: francisco
 */

#ifndef NORMALIZADOR_H_
#define NORMALIZADOR_H_
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

class Normalizador {
	private:

	public:
		Normalizador();
		virtual ~Normalizador();
		void normalizarArchivo();
		void cortarPalabra(string *unaPalabra);
		void sacarAcentos(string *unaPalabra);
		void sacarMayusculas(string *unaPalabra);
		void normalizarPalabra(string *unaPalabra);
		int posicionCaracter(string unaPalabra, char L);
		void cambiarLetra(string *unaPalabra, char L, int pos);
		bool esStopword(string unaPalabra);
};

#endif /* NORMALIZADOR_H_ */
