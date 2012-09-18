/*
 * Aleatorizador.cpp

 *
 *  Created on: 15/09/2012
 *      Author: francisco
 */

#include "Aleatorizador.h"

Aleatorizador::Aleatorizador() {
	// TODO Auto-generated constructor stub

}

Aleatorizador::~Aleatorizador() {
	// TODO Auto-generated destructor stub
}

void Aleatorizador::aleatorizarArchivo(char ruta[]) {
	string cadenaNormal;

	ifstream diccionarioNormalizado(ruta);
	char s[256];
	cout<<"Ingrese ruta destino del diccionario tabulado";
	cin>>s;
	ofstream archivoAuxiliar(s);
	int aleatorio,aux;
	srand(time(NULL));

	if(diccionarioNormalizado && archivoAuxiliar){

		diccionarioNormalizado>>cadenaNormal;

		while (!diccionarioNormalizado.eof()){

			aleatorio = 100000000+rand()%(200000001);
			aux = cadenaNormal.size();
			RegistroNormalizado registro(cadenaNormal,aleatorio,aux);
			archivoAuxiliar<<aleatorio<<"  "<<cadenaNormal<<endl;
			registro.guardar();
			diccionarioNormalizado>>cadenaNormal;
		}

		diccionarioNormalizado.close();
		archivoAuxiliar.close();
		cout<<"Archivo aleatorizado correctamente";
	}
	else
		cout<<"error al aleatorizar el archivo o al buscar carpeta destino";
}


void Aleatorizador::sortExterno() {

}
