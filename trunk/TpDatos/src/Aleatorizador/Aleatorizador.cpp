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

	int i = 0, cantRegistros = 0;

	ifstream diccionarioNormalizado(PATH_ARCHIVO_NORMALIZADO);

	ofstream binario(PATH_ARCHIVO_A_ALEATORIZAR,ios::binary);

	registroNormalizado *bufferEscritura = new registroNormalizado[TAM_BUFFER_LECT_ESC], registro;

	cout<< MSJ_PROCESANDO <<endl;

	if(diccionarioNormalizado && binario){

		diccionarioNormalizado>>registro.termino;

		while (!diccionarioNormalizado.eof()) {

			while ((i < TAM_BUFFER_LECT_ESC) && (!diccionarioNormalizado.eof())) {

				registro.ID = 100000000+rand()%(200000001);
				bufferEscritura[i] = registro;
				diccionarioNormalizado>>registro.termino;
				i++;
			}

			if (i == TAM_BUFFER_LECT_ESC) {

					binario.write((char*)bufferEscritura,(sizeof(registroNormalizado) * TAM_BUFFER_LECT_ESC));
					cantRegistros = cantRegistros + TAM_BUFFER_LECT_ESC;
			}
			else
			{
					binario.write((char*)bufferEscritura,(sizeof(registroNormalizado) * i));
					cantRegistros = cantRegistros + i;
			}

			i = 0;
		}

		delete[] bufferEscritura;
		diccionarioNormalizado.close();
		binario.close();
		this->generarAchivoTabulado(cantRegistros);
		this->sortExterno();
		cout<<"Archivo aleatorizado correctamente"<<endl;
	}
	else
		cout<<"Error al aleatorizar el archivo";
}

void Aleatorizador::generarAchivoTabulado(int cantRegistros) {

	ifstream entrada(PATH_ARCHIVO_A_ALEATORIZAR, ios::binary);
	ofstream salida(PATH_ARCHIVO_TABULADO);

	int i = 0;

	registroNormalizado *bufferLectura = new registroNormalizado[TAM_BUFFER_LECT_ESC];

	salida<<"DICCIONARIO TABULADO"<<endl;
	salida<<" "<<endl;

	while(cantRegistros >= TAM_BUFFER_LECT_ESC){

		entrada.read((char*)bufferLectura,(sizeof(registroNormalizado) * TAM_BUFFER_LECT_ESC));
		cantRegistros = cantRegistros - TAM_BUFFER_LECT_ESC;

		while (i < TAM_BUFFER_LECT_ESC) {

			salida << bufferLectura[i].ID << "  " << bufferLectura[i].termino << endl;
			i++;
	 	}

		i = 0;
	}

	if (cantRegistros != 0) {

		entrada.read((char*)bufferLectura,(sizeof(registroNormalizado) * cantRegistros));

		for (int j=0; j<cantRegistros; j++) {
			salida << bufferLectura[j].ID << "  " << bufferLectura[j].termino << endl;
		}
	}

	delete[] bufferLectura;
}

void Aleatorizador::sortExterno() {
	cout<<"TODO: ordenamiento"<<endl;
}
