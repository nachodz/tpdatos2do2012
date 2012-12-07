/*
 * HandlerArchivoDeTerminos.cpp
 *
 *  Created on: 21/11/2012
 *      Author: francisco
 */

#include "HandlerArchivoDeTerminos.h"

HandlerArchivoDeTerminos::HandlerArchivoDeTerminos(string rutaArchivo) {
	this->cantidadTerminos = 0;
	this->rutaArchivo = rutaArchivo;
	fstream archivoTerminos;
	archivoTerminos.open((this->rutaArchivo).c_str(),ios::binary|ios::out);
	archivoTerminos.close();
}

HandlerArchivoDeTerminos::~HandlerArchivoDeTerminos() {

}

void HandlerArchivoDeTerminos::agregarTermino(string palabra) {

	ofstream archivoTerminos;
	archivoTerminos.open((this->rutaArchivo).c_str(), ios::binary|ios::out|ios::app);

	if (archivoTerminos) {

		short int tamanio = palabra.size();

		archivoTerminos.write((char*)&tamanio,sizeof(tamanio));
		archivoTerminos.write(palabra.c_str(),tamanio);
		archivoTerminos.flush();
		archivoTerminos.close();
		this->aumentarCantidadElementos();
	}
	else
		cout << "Error en la escritura del archivo de terminos" << endl;
}

int HandlerArchivoDeTerminos::buscarPosicionTermino(string palabraAbuscar) {

	    ifstream archivoTerminos;
		archivoTerminos.open((this->rutaArchivo).c_str(), ios::binary);

		if (archivoTerminos) {

			archivoTerminos.seekg(0,ios::end);
			long int nBytes = archivoTerminos.tellg();

			if (nBytes == 0)
				return -1;

			else {

				char* buffer = new char[nBytes];

				if (buffer) {

					archivoTerminos.seekg(0,ios::beg);
					archivoTerminos.read(buffer,nBytes);
					archivoTerminos.close();

					short int* size;
					int i = 0;
					char* longitud = new char[sizeof(int)];
					bool encontrado = false;
					int posicion = 0;

				    while ((nBytes > 0)&&(!encontrado)) {

						memmove(longitud,&buffer[i],sizeof(short int));
						size = (short int*)longitud;
						i = i + sizeof(short int);
						nBytes = nBytes - sizeof(short int);

						char* termino = new char[*size];
						memmove(termino,&buffer[i],*size);
						i = i + *size;
						nBytes = nBytes - *size;

						string palabra(termino);
						palabra = palabra.substr(0,*size);

						if (palabra == palabraAbuscar)
							encontrado = true;
						else
							posicion++;
				    }

					delete[] longitud;

					if (encontrado)
						return posicion; //Devuelve la posicion del termino.
					else
						return -1; //Si no encuentra el termino devuelve -1.

					delete[] buffer;
				}
				else
				cout << "No se hallo memoria RAM para cargar el archivo de terminos" << endl;
				return -2; //Si no se puede reservar memoria devuelve menos 2.
			}
		}
		else {

			cout << "Error en la lectura del archivo de terminos" << endl;
			return -1; //Devuelve menos -1 si no puedo abrir el archivo.
		}
}

int HandlerArchivoDeTerminos::getCantidadElementos() {
	return cantidadTerminos;
}

void HandlerArchivoDeTerminos::putCantidadElementos(int numeroTerminos) {
	this->cantidadTerminos = numeroTerminos;
}

void HandlerArchivoDeTerminos::aumentarCantidadElementos() {
	this->cantidadTerminos++;
}
