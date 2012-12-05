
#include <iostream>
#include "ArbolBMas/ArbolBMas.h"
#include "ArbolBMas/Clave.h"
#include "ArbolBMas/Elementos.h"
#include <fstream>
#include "Constantes.h"
#include "Gestor/gestorArchivoDeTerminos.h"
#include "Gestor/gestorArchivoPorciones.h"
#include "Gestor/gestorArchivoOcurrencias.h"
#include "mapaBits.h"
#include "interpreteFrases.h"
#include "Normalizador/Normalizador.h"
#include <stdio.h>
#include <stdlib.h>
#include <iconv.h>
#include "indice.h"


using namespace std;

struct ocurr {
	int idT;
	int idR;
};

int alta(string frase) {

	mapaBits *mapa = new mapaBits(TAMANIO_REGISTRO_FRASE * BYTE);
	char *serial = new char[TAMANIO_REGISTRO_FRASE];
	fstream frases;
	frases.open(PATH_FRASES, ios::binary|ios::in|ios::out);
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

string baja(int numeroRegistro) {

	string *frase = new string(" ");
	if (numeroRegistro == 0) {
		cout << "No se puede eliminar este registro debido a que contiene metadata del archivo" << endl;
		return *frase;
	}
	else {
		mapaBits *mapa = new mapaBits(TAMANIO_REGISTRO_FRASE * BYTE);
		char *serial = new char[TAMANIO_REGISTRO_FRASE];
		fstream frases;
		frases.open(PATH_FRASES, ios::binary|ios::in|ios::out);

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


void listarEnTexto() {

	mapaBits *mapa = new mapaBits(TAMANIO_REGISTRO_FRASE*BYTE);
	char *serial = new char[TAMANIO_REGISTRO_FRASE];
	ofstream archivoSalida;
	archivoSalida.open(PATH_FRASES_EN_TXT);
	ifstream frases;
	frases.open(PATH_FRASES, ios::binary);

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

int main() {

	bool ejecutando = true;

	indice *indiceFirmas = new indice(PATH_ARBOL,PATH_TERMINOS,PATH_OCURRENCIAS,PATH_FIRMAS,TAM_PORCION);
	indiceFirmas->recuperarInformacion();

	while(ejecutando){

		int op;

		cout << " " << endl;
		cout << "MENU PRINCIPAL" << endl;
		cout << " " << endl;
		cout << "1)Cargar inicial del indice de firmas a partir del archivo binario de frases"  << endl;
		cout << "2)Agregar frase" << endl;
		cout << "3)Borrar frase" << endl;
		cout << "4)Buscar palabras en frases" << endl;
		cout << "5)Mostrar frases en archivo de texto" << endl;
		cout << "6)Mostrar firma de un termino" << endl;
		cout << "7)Salir" << endl;
		cout << " " << endl;

		cin >> op;
		cin.ignore();

		while ((op < 1) || (op > 7)){
			cout << "La opcion ingresada es incorrecta, ingrese una opcion correcta" << endl;
			cout << " " << endl;
			cin >> op;
			cin.ignore();
		}

		switch(op){
			case 1: {
				indiceFirmas->cargaInicialIndice(PATH_FRASES);
				cout << "Carga realizada con exito" << endl;

				indiceFirmas->guardarInformacion();
				;break;
			}
			case 2: {
				cout << endl;
				cout << "Inserte frase a indexar(Los campos separados por doble tab): ";
				string frase;
				getline(cin,frase);
				int registro = alta(frase);
				if (registro != -1) {
					indiceFirmas->agregarTerminosAlIndice(frase,registro);
					cout << "Alta realizada con exito" << endl;
				}
				else
					cout << "La carga no se pudo realizar" << endl;

				indiceFirmas->guardarInformacion();
				;break;
			}
			case 3: {
				cout << endl;
				cout << "Inserte el numero de frase que desea dar de baja:" << endl;
				cout << "(Numero que aparece al final de cada frase en el archi de texto)" << endl;
				int registro;
				cin >> registro;
				cin.ignore();
				string frase = baja(registro);
				if (frase != " ") {
					indiceFirmas->eliminarTerminosDelIndice(frase,registro);
					cout << "Baja realizada con exito" << endl;
				}
				else
					cout << "La frase ya esta dada de baja o no se pudo realizar la accion" << endl;

				indiceFirmas->guardarInformacion();
				;break;
			}
			case 4: {
				string palabras, auxiliar = "campoVacio\t\t";
				cout << "Ingrese lista de terminos a buscar(Separados por espacio)" << endl;
				getline(cin,palabras);
				palabras = auxiliar + palabras;
				if (palabras == auxiliar)
					cout << "No ingrego terminos para buscar" << endl;
				else
					indiceFirmas->buscarFrases(palabras);

				indiceFirmas->guardarInformacion();
				;break;
			}
			case 5: {
				listarEnTexto();
				;break;
			}
			case 6: {
				string palabra;
				cout << "Insertar palabra a buscar" << endl;
				cin >> palabra;
				cin.ignore();
				indiceFirmas->mostrarFirma(palabra);
				;break;
			}
			case 7: ejecutando = false;break;
			default: ;break;
		}
	}
return 0;
}

