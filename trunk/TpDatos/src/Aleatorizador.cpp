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
		char termino[25];
	};

	srand(time(NULL));

	ifstream diccionarioNormalizado(ruta);

	char s[256];
	cout<<"Ingrese ruta destino del diccionario tabulado";
	cin>>s;

	ofstream archivoAuxiliar(s),binario("/home/francisco/binario",ios::binary);

	registro reg;

	if(diccionarioNormalizado && archivoAuxiliar && binario){

		diccionarioNormalizado>>reg.termino;

		while (!diccionarioNormalizado.eof()){

			reg.id = 100000000+rand()%(200000001);
			binario.write((char*)&reg,29);
			archivoAuxiliar<<reg.id<<"  "<<reg.termino<<endl;
			diccionarioNormalizado>>reg.termino;
		}

		diccionarioNormalizado.close();
		archivoAuxiliar.close();
		binario.close();
		cout<<"Archivo aleatorizado correctamente"<<endl;
	}
	else
		cout<<"error al aleatorizar el archivo o al buscar carpeta destino";
}


void Aleatorizador::sortExterno() {

}