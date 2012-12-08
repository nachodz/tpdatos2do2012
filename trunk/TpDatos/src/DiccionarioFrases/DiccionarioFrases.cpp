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
		cout << DICC_FRASES_MOSTRAR_OK << endl;
	}
	else
		cout << "El programa no hallo memoria disponible o existe algun error con los archivos" << endl;
}

list<string> ordenarTerminosEnLista(string frase){

	Normalizador normalizador;
	char* palabra = NULL;
	list<string> listaTerminos;
	char fraseCStr[frase.length()];
	strcpy(fraseCStr, frase.c_str());

	palabra = strtok(fraseCStr," .,;:Â¿?_-<>/!	");

	while(palabra != NULL){
		string palabraStr = string(palabra);
		normalizador.normalizarPalabra(&palabraStr);
		listaTerminos.push_back(palabraStr);
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

void crearAltasyBajas(list<string> listaVieja, list<string> listaNueva, int nroDoc, Booleano *indice){

	string terminoNuevo, terminoViejo;
	//list<string> listaAltas, listaBajas;

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
				indice->alta(terminoNuevo, nroDoc);
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

void crearAltasyBajasFirmas(list<string> listaVieja, list<string> listaNueva, int nroDoc, indice *indice){

	string terminoNuevo, terminoViejo;
	//list<string> listaAltas, listaBajas;

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
				indice->agregarTerminosAlIndice(terminoNuevo,nroDoc);
				itNueva++;
				terminoNuevo = *itNueva;
			}
			else{ //terminoNuevo > terminoViejo
				//listaBajas.push_back(terminoViejo);
				indice->eliminarTerminosDelIndice(terminoViejo, nroDoc);
				itVieja++;
				terminoViejo = *itVieja;
			}
	}

	while(itNueva != listaNueva.end()){
	//si es mas grande la nueva, agrego lo que queda.
		//listaAltas.push_back(terminoNuevo);
		indice->agregarTerminosAlIndice(terminoNuevo, nroDoc);
		itNueva++;
		terminoNuevo = *itNueva;
	}

	while(itVieja != listaVieja.end()){
		//listaBajas.push_back(terminoViejo);
		indice->eliminarTerminosDelIndice(terminoViejo, nroDoc);
		itVieja++;
		terminoViejo = *itVieja;
	}

}

void DiccionarioFrases::modificacion(int numeroRegistro, string nuevaFrase, Booleano *indice){
	string viejaFrase;
	char viejaFraseCStr[TAMANIO_REGISTRO_FRASE];
	list<string> listaVieja, listaNueva, listaBajas, listaAltas;

	if (numeroRegistro == 0)
			cout << "No se puede eliminar este registro debido a que contiene metadata del archivo" << endl;
		else {
			mapaBits *mapa = new mapaBits(TAMANIO_REGISTRO_FRASES*BYTE);
			char *serial = new char[TAMANIO_REGISTRO_FRASES];
			fstream frases;
			frases.open(PATH_ARCHIVO_FRASES, ios::binary|ios::in|ios::out);

			if ((mapa)&&(serial)&&(frases)) {

				frases.read(serial,TAMANIO_REGISTRO_FRASES);
				mapa->hidratar(serial);

				if (mapa->libre(numeroRegistro))
					cout << "No se puede modificar, pues el registro esta libre" << endl;
				else {
					frases.seekg(numeroRegistro*TAMANIO_REGISTRO_FRASES, ios::beg);
					strcpy(viejaFraseCStr, viejaFrase.c_str());
					frases.read(viejaFraseCStr,TAMANIO_REGISTRO_FRASES);
					viejaFrase = viejaFraseCStr;

					listaVieja = ordenarTerminosEnLista(viejaFrase);
					listaNueva = ordenarTerminosEnLista(nuevaFrase);
					crearAltasyBajas(listaVieja, listaNueva, numeroRegistro,indice);

					frases.seekp(numeroRegistro*TAMANIO_REGISTRO_FRASES, ios::beg);
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

void DiccionarioFrases::modificacionFirmas(int numeroRegistro, string nuevaFrase, indice *indice){
	string viejaFrase;
	char viejaFraseCStr[TAMANIO_REGISTRO_FRASE];
	list<string> listaVieja, listaNueva, listaBajas, listaAltas;

	if (numeroRegistro == 0)
			cout << "No se puede eliminar este registro debido a que contiene metadata del archivo" << endl;
		else {
			mapaBits *mapa = new mapaBits(TAMANIO_REGISTRO_FRASES*BYTE);
			char *serial = new char[TAMANIO_REGISTRO_FRASES];
			fstream frases;
			frases.open(PATH_ARCHIVO_FRASES, ios::binary|ios::in|ios::out);

			if ((mapa)&&(serial)&&(frases)) {

				frases.read(serial,TAMANIO_REGISTRO_FRASES);
				mapa->hidratar(serial);

				if (mapa->libre(numeroRegistro))
					cout << "No se puede modificar, pues el registro esta libre" << endl;
				else {
					frases.seekg(numeroRegistro*TAMANIO_REGISTRO_FRASES, ios::beg);
					strcpy(viejaFraseCStr, viejaFrase.c_str());
					frases.read(viejaFraseCStr,TAMANIO_REGISTRO_FRASES);
					viejaFrase = viejaFraseCStr;

					listaVieja = ordenarTerminosEnLista(viejaFrase);
					listaNueva = ordenarTerminosEnLista(nuevaFrase);
					crearAltasyBajasFirmas(listaVieja,listaNueva,numeroRegistro,indice);

					frases.seekp(numeroRegistro*TAMANIO_REGISTRO_FRASES, ios::beg);
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
