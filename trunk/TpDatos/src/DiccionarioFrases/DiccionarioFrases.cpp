/*
 * DiccionarioFrases.cpp
 *
 *  Created on: 05/12/2012
 *      Author: ignacio
 */

#include "DiccionarioFrases.h"


DiccionarioFrases::DiccionarioFrases() {}

DiccionarioFrases::~DiccionarioFrases() {}

int DiccionarioFrases::crearArchivoFrases() {

	ofstream frases;
	frases.open(PATH_ARCHIVO_FRASES,ios::binary);
	char* serial = new char[TAMANIO_REGISTRO_FRASES];
	mapaBits *mapa = new mapaBits(TAMANIO_REGISTRO_FRASES*BYTE);

	if ((frases)&&(mapa)&&(serial)){

		mapa->cambiarEstadoRegistro(0);
		serial = mapa->serializar();
		frases.write(serial,TAMANIO_REGISTRO_FRASES);
		frases.flush();
		frases.close();
		mapa->~mapaBits();
		delete[] serial;
		return 0; //No funciona el delete para el serial
	}
	else
		return 1;
}

string DiccionarioFrases::baja(int numeroRegistro) {

	string *frase = new string(" ");
	if (numeroRegistro == 0) {
		cout << "No se puede eliminar este registro debido a que contiene metadata del archivo" << endl;
		return *frase;
	}
	else {
		mapaBits *mapa = new mapaBits(TAMANIO_REGISTRO_FRASE * BYTE);
		char *serial = new char[TAMANIO_REGISTRO_FRASE];
		fstream frases;
		frases.open(PATH_ARCHIVO_FRASES, ios::binary|ios::in|ios::out);

		if ((mapa)&&(serial)&&(frases)) {

			frases.read(serial,TAMANIO_REGISTRO_FRASE);
			mapa->hidratar(serial);

			if (mapa->libre(numeroRegistro))
				cout << "El registro ya esta libre" << endl;

			else {
				mapa->cambiarEstadoRegistro(numeroRegistro);
				frases.seekg(numeroRegistro*TAMANIO_REGISTRO_FRASE);
				frases.read(serial,TAMANIO_REGISTRO_FRASE);
				frase = new string(serial);
			}

			serial = mapa->serializar();
			frases.seekp(0,ios::beg);
			frases.write(serial,TAMANIO_REGISTRO_FRASE);
			frases.flush();
			frases.close();
			delete[] serial;
			mapa->~mapaBits();
		}
		else
			cout << "El programa no hallo memoria disponible o existe algun error con los archivos" << endl;
	}
	return *frase;
}


int DiccionarioFrases::alta(string frase) {

	mapaBits *mapa = new mapaBits(TAMANIO_REGISTRO_FRASE * BYTE);
	char *serial = new char[TAMANIO_REGISTRO_FRASE];
	fstream frases;
	frases.open(PATH_ARCHIVO_FRASES, ios::binary|ios::in|ios::out);
	int posicion = -3;

	if ((mapa)&&(serial)&&(frases)) {

		frases.read(serial,TAMANIO_REGISTRO_FRASE);
		mapa->hidratar(serial);

		posicion = mapa->primerRegitroLibre();

		if (posicion == -1) {
			cout << "El archivo esta completo" << endl;
			return posicion;
		}
		else
		{
			frases.seekp(posicion*TAMANIO_REGISTRO_FRASE);
			frases.write(frase.c_str(),TAMANIO_REGISTRO_FRASE);
			frases.flush();
			mapa->cambiarEstadoRegistro(posicion);
			serial = mapa->serializar();
			frases.seekp(0,ios::beg);
			frases.write(serial,TAMANIO_REGISTRO_FRASE);
			frases.flush();
			return posicion;
		}

		frases.close();
		mapa->~mapaBits();
		delete[] serial;
	}
	else {
		cout << "El programa no hallo memoria disponible o existe algun error con los archivos" << endl;
		return -2;
	}
	return posicion;
}

void DiccionarioFrases::cargaInicial(int numeroDeFrases){

	mapaBits *mapa = new mapaBits(TAMANIO_REGISTRO_FRASES*BYTE);
	char *serial = new char[TAMANIO_REGISTRO_FRASES];
	fstream frases;
	frases.open(PATH_ARCHIVO_FRASES, ios::binary|ios::in|ios::out);
	ifstream archivoFrases(PATH_FRASES);

	if ((mapa)&&(serial)&&(frases)&&(archivoFrases)) {

		string linea;
		int i = 1, posicion;
		frases.read(serial,TAMANIO_REGISTRO_FRASES);
		mapa->hidratar(serial);

		while ((i <= numeroDeFrases) && (posicion != -1) && (getline(archivoFrases,linea))) {

			posicion = mapa->primerRegitroLibre();
			frases.seekp(posicion*TAMANIO_REGISTRO_FRASES,ios::beg);
			frases.write(linea.c_str(),TAMANIO_REGISTRO_FRASES);
			frases.flush();
			mapa->cambiarEstadoRegistro(posicion);
			i++;
		}

		if (posicion == -1) {
			cout << "Solo se cargaron" << " " << i << " " << "frases en el archivo, debido a la capacidad" << endl;
		}

		serial = mapa->serializar();
		frases.seekp(0,ios::beg);
		frases.write(serial,TAMANIO_REGISTRO_FRASES);

		frases.flush();
		frases.close();
		delete[] serial;
		mapa->~mapaBits();
	}
	else
		cout << "El programa no hallo memoria disponible o existe algun error con los archivos" << endl;
}

void DiccionarioFrases::listarEnTexto() {

	mapaBits *mapa = new mapaBits(TAMANIO_REGISTRO_FRASE*BYTE);
	char *serial = new char[TAMANIO_REGISTRO_FRASE];
	ofstream archivoSalida;
	archivoSalida.open(PATH_FRASES_EN_TXT);
	ifstream frases;
	frases.open(PATH_ARCHIVO_FRASES, ios::binary);

	if((mapa)&&(serial)&&(archivoSalida)&&(frases)) {

		frases.read(serial,TAMANIO_REGISTRO_FRASE);
		mapa->hidratar(serial);
		char palabra[TAMANIO_REGISTRO_FRASE];
		int i = 1;

		frases.read((char*)&palabra,TAMANIO_REGISTRO_FRASE);

		while(!frases.eof()) {
			if (!mapa->libre(i)) {
				archivoSalida << palabra << "  " << "(" << i << ")" << endl;
			}
			frases.read((char*)&palabra,TAMANIO_REGISTRO_FRASE);
			i++;
		}

		archivoSalida.close();
		frases.close();
		delete[] serial;
		mapa->~mapaBits();
	}
	else
		cout << "El programa no hallo memoria disponible o existe algun error con los archivos" << endl;
}
