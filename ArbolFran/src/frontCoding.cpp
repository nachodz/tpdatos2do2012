/*
 * frontCoding.cpp
 *
 *  Created on: 25/09/2012
 *      Author: francisco
 */

#include "frontCoding.h"

frontCoding::frontCoding() {
	// TODO Auto-generated constructor stub

}

frontCoding::~frontCoding() {
	// TODO Auto-generated destructor stub
}

/*void frontCoding::pasarAfrontCoding(tClave *claves, int numElem, tRegistroHoja *registros) {

	int i, coincidencias, diferencias;
	string palabra;

	for (i = 0; i < numElem; i++) {

		if (i == 0) {

			palabra = (claves[i]).getTermino();
			RegistroHoja registro(-1,palabra.size(),palabra,(claves[i]).getPosicion(),0);
			registros[i] = registro;
		}
		else
		{
			coincidencias = (this->LetrasIguales(claves[i-1].getTermino(), claves[i].getTermino()));

			if (coincidencias != 0) {

				palabra = (this->letrasDistintas(claves[i].getTermino(), coincidencias));
				diferencias = palabra.size();
				RegistroHoja registro(coincidencias,diferencias,palabra,(claves[i]).getPosicion(),0);
				registros[i] = registro;
			}
			else
			{
				palabra = (claves[i].getTermino());
				diferencias = palabra.size();
				RegistroHoja registro(coincidencias,diferencias,palabra,(claves[i]).getPosicion(),0);
				registros[i] = registro;
			}
		}
	}
}

void frontCoding::sacarFrontCoding(tRegistroHoja *registros, int numElem, tClave *claves) {

	int i, coincidencias;
	string palabra, cadenaAux;

	for (i = 0; i < numElem; i++) {

		if ((i == 0) || ((registros[i].getLetrasIguales()) == 0)) {

			palabra = ((registros[i]).getPalabra());
			clave unaClave(palabra,((registros[i]).getPosicion()),((registros[i]).getFantasma()));
			claves[i] = unaClave;
		}
		else
		{
			coincidencias = (registros[i].getLetrasIguales());
			palabra = (registros[i].getPalabra());
			cadenaAux = (claves[i-1].getTermino()).substr(0,coincidencias);
			palabra = cadenaAux += palabra;
			clave unaClave(palabra,((registros[i]).getPosicion()),((registros[i]).getFantasma()));
			claves[i] = unaClave;
		}
	}

}


int frontCoding::LetrasIguales(string palabra1, string palabra2) {

	unsigned int i = 0, contador = 0;


	while ((i <= palabra1.size()) && (i <= palabra2.size()) && (palabra1[i] == palabra2[i])) {

		contador++;
		i++;
	}
	return contador;
}

string frontCoding::letrasDistintas(string palabra, int coin) {

	string aux;

	aux = palabra.substr(coin,palabra.size());

	return aux;//	int LetrasIguales(string palabra1, string palabra2);
//
//	string letrasDistintas(string palabra, int coin);
 */

