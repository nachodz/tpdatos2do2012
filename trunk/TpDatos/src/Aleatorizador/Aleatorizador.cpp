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

void Aleatorizador::aleatorizarArchivo() {

	srand(time(NULL));

	char ruta[] = PATH_ARCHIVO_NORMALIZADO;

	ifstream diccionarioNormalizado(ruta);

	ofstream binario(PATH_ARCHIVO_A_ALEATORIZAR,ios::binary);

	registro reg;

	cout<<MSJ_PROCESANDO<<endl;
	if(diccionarioNormalizado && binario){

		diccionarioNormalizado>>reg.termino;

		while (!diccionarioNormalizado.eof()){

			reg.ID = 100000000+rand()%(200000001);
			binario.write((char*)&reg,29);
			diccionarioNormalizado>>reg.termino;
		}

		diccionarioNormalizado.close();
		binario.close();
		this->generarAchivoTabulado();
		this->sortExterno();
		cout<<"Archivo aleatorizado correctamente"<<endl;
	}
	else
		cout<<"Error al aleatorizar el archivo";
}

void Aleatorizador::generarAchivoTabulado() {

	ifstream entrada(PATH_ARCHIVO_A_ALEATORIZAR, ios::binary);
	ofstream salida(PATH_ARCHIVO_TABULADO);

	registro reg;

	salida<<"DICCIONARIO TABULADO"<<endl;
	salida<<" "<<endl;

	entrada.read((char*)&reg,29);

		while(!entrada.eof()){

			salida<<reg.ID<<"  "<<reg.termino<<endl;
			entrada.read((char*)&reg,29);
		}
}

void Aleatorizador::sortExterno() {
	cout<<"TODO: ordenamiento"<<endl;
}
