//============================================================================
// Name        : diccionarioFrases.cpp
// Author      : Francisco
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "mapaBits.h"
#incluide "../Booleano/Booleano.h"
#include <string>
#include <sstream>
#include <string.h>
#include <list>


#define TAMANIO_REGISTRO_FRASES 256
#define PATH_ARCHIVO_FRASES "Frases celebres.dat"
#define PATH_FRASES "Frases_Celebres.csv"
#define CANTIDAD_DE_FRASES_A_CARGAR 60
#define INFORME_FRASES "Frases celebre.txt"

using namespace std;

int crearArchivoFrases() {

	ofstream frases;
	frases.open(PATH_ARCHIVO_FRASES,ios::binary);
	char* serial = new char[TAMANIO_REGISTRO_FRASES];
	mapaBits *mapa = new mapaBits(TAMANIO_REGISTRO_FRASES);

	if ((frases)&&(mapa)&&(serial)){

		mapa->cambiarEstadoRegistro(0);
		serial = mapa->serializar();
		frases.write(serial,mapa->getTamanio());
		frases.flush();
		frases.close();
		mapa->~mapaBits();
		delete[] serial;
		return 0; //No funciona el delete para el serial
	}
	else
		return 1;
}


void baja(int numeroRegistro) {

	if (numeroRegistro == 0)
		cout << "No se puede eliminar este registro debido a que contiene metadata del archivo" << endl;
	else {
		mapaBits *mapa = new mapaBits(TAMANIO_REGISTRO_FRASES);
		char *serial = new char[TAMANIO_REGISTRO_FRASES];
		fstream frases;
		frases.open(PATH_ARCHIVO_FRASES, ios::binary|ios::in|ios::out);

		if ((mapa)&&(serial)&&(frases)) {

			frases.read(serial,TAMANIO_REGISTRO_FRASES);
			mapa->hidratar(serial);

			if (mapa->libre(numeroRegistro))
				cout << "El registro ya esta libre" << endl;
			else
				mapa->cambiarEstadoRegistro(numeroRegistro);

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
}

void alta(string frase) {

	mapaBits *mapa = new mapaBits(TAMANIO_REGISTRO_FRASES);
	char *serial = new char[TAMANIO_REGISTRO_FRASES];
	fstream frases;
	frases.open(PATH_ARCHIVO_FRASES, ios::binary|ios::in|ios::out);

	if ((mapa)&&(serial)&&(frases)) {

		frases.read(serial,TAMANIO_REGISTRO_FRASES);
		mapa->hidratar(serial);
		int posicion;

		posicion = mapa->primerRegitroLibre();

		if (posicion == -1)
			cout << "El archivo esta completo";
		else
		{
			frases.seekp(posicion*TAMANIO_REGISTRO_FRASES);
			frases.write(frase.c_str(),TAMANIO_REGISTRO_FRASES);
			frases.flush();
			mapa->cambiarEstadoRegistro(posicion);
			serial = mapa->serializar();
			frases.seekp(0,ios::beg);
			frases.write(serial,TAMANIO_REGISTRO_FRASES);
			frases.flush();
		}

		frases.close();
		mapa->~mapaBits();
		delete[] serial;
	}
	else
		cout << "El programa no hallo memoria disponible o existe algun error con los archivos" << endl;
}

list<string> ordenarTerminosEnLista(string frase){
	char* palabra = NULL;
	list<string> listaTerminos;
	char fraseCStr[frase.length()];
	strcpy(fraseCStr, frase.c_str());

	palabra = strtok(fraseCStr," .,;:Â¿?_-<>/!	");

	while(palabra != NULL){
		listaTerminos.push_back(palabra);
		palabra = strtok(NULL, " .,;:Â¿?_-<>/!	");
	}

	listaTerminos.sort();
	list<string>::iterator it = listaTerminos.begin();
	while(it != listaTerminos.end()){
		cout << *it << endl;
		it++;
	}
	cout << endl;

	return listaTerminos;

}

void crearAltasyBajas(list<string> listaVieja, list<string> listaNueva, int nroDoc){
	string terminoNuevo, terminoViejo;
	//list<string> listaAltas, listaBajas;
	Booleano* indice = new Booleano();

	list<string>::iterator itVieja = listaVieja.begin();
	list<string>::iterator itNueva = listaNueva.begin();
	terminoNuevo = *itNueva;
	terminoViejo = *itVieja;

	while((itVieja != listaVieja.end()) && (itNueva != listaNueva.end())){

		if(terminoNuevo == terminoViejo){
			itNueva++;
			itVieja++;
			terminoNuevo = *itNueva;
			terminoViejo = *itVieja;
		}
		else
			if(terminoNuevo < terminoViejo){
				//listaAltas.push_back(terminoNuevo);
				indice->alta(terminoNuevo, nroDoc)
				itNueva++;
				terminoNuevo = *itNueva;
			}
			else{ //terminoNuevo > terminoViejo
				//listaBajas.push_back(terminoViejo);
				indice->baja(terminoViejo, nroDoc);
				itVieja++;
				terminoViejo = *itVieja;
			}
	}

	while(itNueva != listaNueva.end()){
	//si es mas grande la nueva, agrego lo que queda.
		//listaAltas.push_back(terminoNuevo);
		indice->alta(terminoNuevo, nroDoc);
		itNueva++;
		terminoNuevo = *itNueva;
	}

	while(itVieja != listaVieja.end()){
		//listaBajas.push_back(terminoViejo);
		indice->baja(terminoViejo, nroDoc);
		itVieja++;
		terminoViejo = *itVieja;
	}

}



void modificacion(int numeroRegistro, string nuevaFrase){

	string viejaFrase;
	char viejaFraseCStr[256];
	list<string> listaVieja, listaNueva, listaBajas, listaAltas;

	if (numeroRegistro == 0)
			cout << "No se puede eliminar este registro debido a que contiene metadata del archivo" << endl;
		else {
			mapaBits *mapa = new mapaBits(TAMANIO_REGISTRO_FRASES);
			char *serial = new char[TAMANIO_REGISTRO_FRASES];
			fstream frases;
			frases.open(PATH_ARCHIVO_FRASES, ios::binary|ios::in|ios::out);

			if ((mapa)&&(serial)&&(frases)) {

				frases.read(serial,TAMANIO_REGISTRO_FRASES);
				mapa->hidratar(serial);

				if (mapa->libre(numeroRegistro))
					cout << "No se puede modificar, pues el registro esta libre" << endl;
				else {
					frases.seekg(numeroRegistro*TAMANIO_REGISTRO_FRASES);
					strcpy(viejaFraseCStr, viejaFrase.c_str());
					frases.read(viejaFraseCStr,TAMANIO_REGISTRO_FRASES);
					viejaFrase = viejaFraseCStr;

					listaVieja = ordenarTerminosEnLista(viejaFrase);
					listaNueva = ordenarTerminosEnLista(nuevaFrase);
					crearAltasyBajas(listaVieja, listaNueva, numeroRegistro);


					frases.seekp(numeroRegistro*TAMANIO_REGISTRO_FRASES);
					frases.write(nuevaFrase.c_str(),TAMANIO_REGISTRO_FRASES);
					frases.flush();
					serial = mapa->serializar();
					frases.seekp(0,ios::beg);
					frases.write(serial,TAMANIO_REGISTRO_FRASES);
					frases.flush();
				}
			}else
				cout << "El programa no hallo memoria disponible o existe algun error con los archivos" << endl;
		}

}

void cargaInicial(int numeroDeFrases){

	mapaBits *mapa = new mapaBits(TAMANIO_REGISTRO_FRASES);
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
			frases.seekp(posicion*TAMANIO_REGISTRO_FRASES);
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

void listarEnTexto() {

	mapaBits *mapa = new mapaBits(TAMANIO_REGISTRO_FRASES);
	char *serial = new char[TAMANIO_REGISTRO_FRASES];
	ofstream archivoSalida;
	archivoSalida.open(INFORME_FRASES);
	ifstream frases;
	frases.open(PATH_ARCHIVO_FRASES, ios::binary);

	if((mapa)&&(serial)&&(archivoSalida)&&(frases)) {

		frases.read(serial,TAMANIO_REGISTRO_FRASES);
		mapa->hidratar(serial);
		char palabra[TAMANIO_REGISTRO_FRASES];
		int i = 1;

		frases.read((char*)&palabra,TAMANIO_REGISTRO_FRASES);

		while(!frases.eof()) {
			if (!mapa->libre(i)) {
				archivoSalida << palabra << endl;
			}
			frases.read((char*)&palabra,TAMANIO_REGISTRO_FRASES);
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

	while(ejecutando){

		int op;

		cout << " " << endl;
		cout << "MENU PRINCIPAL" << endl;
		cout << " " << endl;
		cout << "1)Crear y cargar archivo"  << endl;
		cout << "2)Eliminar frase" << endl;
		cout << "3)Agregar frase" << endl;
		cout << "4)Exportar frases a un archivo de texto" << endl;
		cout << "5)Salir" << endl;
		cout << " " << endl;

		cin >> op;
		cin.ignore();

		while ((op < 1) || (op > 6)){
			cout << "La opcion ingresada es incorrecta, ingrese una opcion correcta" << endl;
			cout << " " << endl;
			cin >> op;
			cin.ignore();
		}

		switch(op){
			case 1: {
				int archivoCreado = crearArchivoFrases();
				if (archivoCreado == 0)
					cout << "Archivo de frases creado correctamente" << endl;

				else
					cout << "Error al crear el archivo de frases" << endl;

				int frases;
				cout << " " << endl;
				cout << "Ingrese el numero de frases celebres a importar desde el archivo 'Frases_Celebres.csv'" << endl;
				cout << " " << endl;
				cin >> frases;
				cin.ignore();

				while(frases >= ((TAMANIO_REGISTRO_FRASES-1)*8)) {
					cout << "El numero de frase exede la capacidad total del archivo" << endl;
					cout << " " << endl;
					cin >> frases;
					cin.ignore();
				}

				cargaInicial(frases);
				cout << "Carga terminada" << endl;
				cout << " " << endl;
				;break;
			}
			case 2: {
				int registro;
				cout << "Ingrese el numero de registro de la frase a eliminar (Guiarse por el archivo de texto)" << endl;
				cout << " " << endl;
				cin >> registro;
				cin.ignore();

				while(registro >= ((TAMANIO_REGISTRO_FRASES-1)*8)) {
					cout << "El numero de frase exede la capacidad total del archivo" << endl;
					cout << " " << endl;
					cin >> registro;
					cin.ignore();
				}
				baja(registro);
				;break;
			}
			case 3: {
				string frase;
				cout << "Ingrese la frase, anteponiendo su autor, en caso de no conocerlo poner Anonimo" << endl;
				cout << " " << endl;
				getline(cin,frase);
				alta(frase);
				;break;
			}
			case 4: {
				listarEnTexto();
				cout << "Importacion de frases completa" << endl;
				cout << " " << endl;
				;break;
			}
			case 5: ejecutando = false;break;
			case 6: {
				string frase;
				char fraseCStr[256];
				cout << "ingresar frase" << endl;
				cin.getline(fraseCStr, 256);
				frase = fraseCStr;
				cout<< frase;
				modificacion(1,frase);
				;break;
			}
			default: ;break;
		}
	}
	return 0;
}


