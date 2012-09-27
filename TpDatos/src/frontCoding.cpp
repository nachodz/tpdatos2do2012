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

void frontCoding::pasarAfrontCoding(string palabras[], int numElem) {

	int i, j, coincidencias, diferencias;
	string palabra;

	for (i = 0, j = 0; i < numElem; i++,j++) {

		if (i == 0) {

			palabra = palabras[i];
			RegistroHoja registro(-1,palabra.size(),palabra,j,0);
			//Aca meteria el registro en el nodo.
		}
		else
		{
			coincidencias = (this->LetrasIguales(palabras[i-1],palabras[i]));

			if (coincidencias != 0) {

				if ((palabras[i-1].size()) >= (palabras[i].size())){

					palabra = "";
					RegistroHoja registro(coincidencias,0,palabra,j,0);
					//Aca  se mete el registro en el nodo.
				}
				else
				{
					palabra = (this->letrasDistintas(palabras[i], coincidencias));
					diferencias = palabra.size();
					RegistroHoja registro(coincidencias,diferencias,palabra,j,0);
					//Aca se mete el registro en el nodo.
				}
			}
			else
			{
				palabra = palabras[i];
				diferencias = palabra.size();
				RegistroHoja registro(coincidencias,diferencias,palabra,j,0);
				//Aca se mete el registro en el nodo.
				cout << "  " << (registro.getLetrasIguales()) << "  " << (registro.getLetrasDistintas()) << "  " << (registro.getPalabra()) << "  " << (registro.getPosicion()) << "  " << (registro.getFantasma()) << " |";
			}
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

	return aux;
}
