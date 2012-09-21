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

	char ruta[] = "normalizado.txt";

	ifstream diccionarioNormalizado(ruta);

	ofstream binario("diccionario.dat",ios::binary);

	registro reg;

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

	ifstream entrada("diccionario.dat", ios::binary);
	ofstream salida("tabulado.txt");

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
	cout<<"ordenamiento"<<endl;
}