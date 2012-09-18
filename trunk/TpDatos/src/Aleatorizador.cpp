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

	struct registro{
		int id;
		char termino[20];
	};

	srand(time(NULL));

	ifstream diccionarioNormalizado(ruta);

	char s[256];
	cout<<"Ingrese ruta destino del diccionario tabulado";
	cin>>s;

	ofstream archivoAuxiliar(s),binario("/home/francisco/binario",ios::binary);

	registro reg;

	if(diccionarioNormalizado && archivoAuxiliar){

		diccionarioNormalizado>>reg.termino;

		while (!diccionarioNormalizado.eof()){

			reg.id = 100000000+rand()%(200000001);
			binario.write((char*)&reg.id,4);
			binario.write((char*)&reg.termino,20);
			archivoAuxiliar<<reg.id<<"  "<<reg.termino<<endl;
			diccionarioNormalizado>>reg.termino;
		}

		diccionarioNormalizado.close();
		archivoAuxiliar.close();
		cout<<"Archivo aleatorizado correctamente"<<endl;
	}
	else
		cout<<"error al aleatorizar el archivo o al buscar carpeta destino";
}


void Aleatorizador::sortExterno() {

}
