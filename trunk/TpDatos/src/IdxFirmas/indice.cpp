/*
 * indice.cpp
 *
 *  Created on: 23/11/2012
 *      Author: francisco
 */

#include "indice.h"

indice::indice(string rutaLexico, string rutaTerminos,string rutaOcurrencias, string rutaPorciones,int tamanioFirma) {
	this->lexico = new ArbolBMas(rutaLexico);
	this->gestorArchivoTerminos = new HandlerArchivoDeTerminos(rutaTerminos);
	this->gestorArchivoDeOcurrencias = new HandlerArchivoOcurrencias(rutaOcurrencias);
	this->gestorArchivoDePorciones = new HandlerArchivoPorciones(rutaPorciones);
	this->tamanioFirma = tamanioFirma;
}

indice::~indice() {
	this->lexico->~ArbolBMas();
	delete[] this->gestorArchivoDeOcurrencias;
	delete[] this->gestorArchivoDePorciones;
	delete[] this->gestorArchivoTerminos;
}

int indice::getTamanioFirma() {
	return this->tamanioFirma;
}

void indice::cargaInicialIndice(string rutaCarga) {

	fstream frases;
	frases.open((rutaCarga).c_str(), ios::binary|ios::in|ios::out);

	if(!frases)
		cout << "No se pudo abrir el archivo de frases para la carga inicial del indice" << endl;

	else {

		interpreteFrases *interprete = new interpreteFrases(&frases);

		char* fraseConAutor = new char[TAMANIO_REGISTRO_FRASE];

		if ((!interprete)||(!fraseConAutor))
			cout << "Error al crear el interprete de frases" << endl;

		else {
			int nroRegistros = interprete->elementosAleer();
			int elementosLeidos = 0;
			frases.seekp(TAMANIO_REGISTRO_FRASE);
			fraseConAutor = interprete->leerFrase(&frases);

			while(elementosLeidos < nroRegistros) {

				string fraseCompleta(fraseConAutor);
				int cantidadElementos;
				string* vectorTerminos = interprete->parsearFrase(fraseCompleta,&cantidadElementos);

				interprete->normalizarTerminos(vectorTerminos,cantidadElementos);
				string* vectorFiltrado = interprete->filtroStopword(vectorTerminos, &cantidadElementos);

				for (int i = 0; i < cantidadElementos; i++) {
					regOcurrencia ocurrencia;
					ocurrencia.idRegistro = elementosLeidos+1;

					bool encontro;
					Elementos *elemento = this->buscarEnArbol(vectorFiltrado[i],this->lexico,&encontro);

					if(!encontro){
						this->gestorArchivoTerminos->agregarTermino(vectorFiltrado[i]);
						ocurrencia.idTermino = (this->gestorArchivoTerminos->getCantidadElementos()-1);
						Clave *clave = new Clave(vectorFiltrado[i]);

						Persistencia *termino = new Persistencia(vectorFiltrado[i]);
						Persistencia *posicion = new Persistencia(intToString(ocurrencia.idTermino));
						Persistencia *fantasma = new Persistencia("0");
						Elementos *elemento = new Elementos(clave,termino,posicion,fantasma);
						this->lexico->insertar(elemento);
					}
					else {
						string aux = elemento->getN()->toString();
						ocurrencia.idTermino = atoi(aux.c_str());
					}

					this->gestorArchivoDeOcurrencias->grabarRegistro(ocurrencia.idTermino,ocurrencia.idRegistro = elementosLeidos+1);
				}
				fraseConAutor = interprete->leerFrase(&frases);
				elementosLeidos++;
			}

			this->gestorArchivoDeOcurrencias->sort(this->gestorArchivoDeOcurrencias->getNumeroOcurrencias());
			rename(PATH_OCURRENCIAS_ORDENADO,PATH_OCURRENCIAS);
			rename(PATH_ALEATORIO,PATH_OCURRENCIAS);
			this->generarFirmas();
			delete[] fraseConAutor;
			interprete->~interpreteFrases();
			remove(PATH_OCURRENCIAS);
		}
		frases.close();
	}
}

void indice::generarFirmas() {

	ifstream ocurrencias(PATH_OCURRENCIAS, ios::binary|ios::in);
	ofstream porciones(PATH_FIRMAS,ios::binary|ios::out);
	porciones.close();

	if ((!ocurrencias)||(!porciones))
		cout << "Error al abrir el archivo de ocurrencias o porciones para generar firma" << endl;
	else {

		int idT,idR,anterioridT;
		int idControl;
		int i = 0;
		this->gestorArchivoDeOcurrencias->leerRegistro(i,&idT,&idR,&ocurrencias);
		idControl = idT;


		while (!(this->gestorArchivoDeOcurrencias->finLectura(i))) {
			mapaBits* firma = new mapaBits(this->tamanioFirma);
			firma->inicializar();
			anterioridT = idT;

			while ((idControl == idT)&&(!this->gestorArchivoDeOcurrencias->finLectura(i))) {

				firma->asignarBit(idR);
				this->gestorArchivoDeOcurrencias->leerRegistro(i,&idT,&idR,&ocurrencias);
				i++;
			}
		    idControl = idT;
			this->gestorArchivoDePorciones->guardarFirma(*firma,anterioridT);
		}
	}
}

Elementos* indice::buscarEnArbol (string palabra, ArbolBMas* arbol,bool * result){

	 Elementos* unElemento;
	 Clave* unaClave = new Clave(palabra);
	 unElemento = arbol->buscar(unaClave);
	 *result = ((unElemento != NULL) && (unElemento->getClave()->getClave()) == (unaClave->getClave()));
	 return unElemento;
}

string indice::intToString(int n) {

	stringstream result;
	result << n;
	return result.str();
}

void indice::guardarInformacion() {
	ofstream informacion;
	informacion.open(PATH_INDICE, ios::binary|ios::out);
	int ocurrencias = this->gestorArchivoDeOcurrencias->getNumeroOcurrencias();
	int porciones = this->gestorArchivoDePorciones->getNumeroFirmas();
	int terminos = this->gestorArchivoTerminos->getCantidadElementos();
	informacion.write((char*)&ocurrencias,sizeof(int));
	informacion.write((char*)&porciones,sizeof(int));
	informacion.write((char*)&terminos,sizeof(int));
	informacion.close();
}

void indice::recuperarInformacion() {
	ifstream informacion;
	informacion.open(PATH_INDICE, ios::binary|ios::in);
	if(!informacion) {
		this->gestorArchivoDeOcurrencias->putNumeroOcurrencias(0);
		this->gestorArchivoDePorciones->putNumeroFirmas(0);
		this->gestorArchivoTerminos->putCantidadElementos(0);
	}
	else {
		int ocurrencias,porciones,terminos;
		informacion.read((char*)&ocurrencias,sizeof(int));
		this->gestorArchivoDeOcurrencias->putNumeroOcurrencias(ocurrencias);
		informacion.read((char*)&porciones,sizeof(int));
		this->gestorArchivoDePorciones->putNumeroFirmas(porciones);
		informacion.read((char*)&terminos,sizeof(int));
		this->gestorArchivoTerminos->putCantidadElementos(terminos);
		informacion.close();
	}
}

void indice::agregarTerminosAlIndice(string frase, int registro) {

	fstream frases;
	frases.open(PATH_ARCHIVO_FRASES, ios::binary|ios::in|ios::out);

	if(!frases)
		cout << "No se pudo abrir el archivo de frases para altas" << endl;

	else {

		interpreteFrases *interprete = new interpreteFrases(&frases);

		if (!interprete)
			cout << "Error al crear el interprete de frases" << endl;
		else {
			int cantidadElementos = 0;
			string* vectorTerminos = interprete->parsearFrase(frase,&cantidadElementos);
			interprete->normalizarTerminos(vectorTerminos,cantidadElementos);
			string* vectorFiltrado = interprete->filtroStopword(vectorTerminos, &cantidadElementos);

			for (int i = 0; i < cantidadElementos; i++) {
				regOcurrencia ocurrencia;
				ocurrencia.idRegistro = registro;

				bool encontro;
				Elementos *elemento = this->buscarEnArbol(vectorFiltrado[i],this->lexico,&encontro);

				if(!encontro){
					this->gestorArchivoTerminos->agregarTermino(vectorFiltrado[i]);
					ocurrencia.idTermino = (this->gestorArchivoTerminos->getCantidadElementos())-1;
					Clave *clave = new Clave(vectorFiltrado[i]);

					Persistencia *termino = new Persistencia(vectorFiltrado[i]);
					Persistencia *posicion = new Persistencia(intToString(ocurrencia.idTermino));
					Persistencia *fantasma = new Persistencia("0");
					Elementos *elemento = new Elementos(clave,termino,posicion,fantasma);
					this->lexico->insertar(elemento);
					elemento->~Elementos();
					mapaBits* firmaTermino = new mapaBits(TAM_PORCION);
					firmaTermino->inicializar();
					firmaTermino->asignarBit(ocurrencia.idRegistro);
					this->gestorArchivoDePorciones->guardarFirma(*firmaTermino,ocurrencia.idTermino);;
					//firmaTermino->~mapaBits(int registro); El destructor pincha
				}
				else {
					string aux = elemento->getN()->toString();
					ocurrencia.idTermino = atoi(aux.c_str());
					mapaBits* firmaTermino = this->gestorArchivoDePorciones->obtenerFirma(ocurrencia.idTermino);
					firmaTermino->asignarBit(ocurrencia.idRegistro);
					this->gestorArchivoDePorciones->guardarFirma(*firmaTermino,ocurrencia.idTermino);
					//firmaTermino->~mapaBits(); EL destructor pincha
				}
			}
		}
		frases.close();
	}
}

void indice::eliminarTerminosDelIndice(string frase, int registro) {

	fstream frases;
	frases.open(PATH_ARCHIVO_FRASES, ios::binary|ios::in|ios::out);

	if(!frases)
		cout << "No se pudo abrir el archivo de frases para bajas" << endl;

	else {

			interpreteFrases *interprete = new interpreteFrases(&frases);

			if (!interprete)
				cout << "Error al crear el interprete de frases" << endl;
			else {
				int cantidadElementos = 0;
				string* vectorTerminos = interprete->parsearFrase(frase,&cantidadElementos);
				interprete->normalizarTerminos(vectorTerminos,cantidadElementos);
				string* vectorFiltrado = interprete->filtroStopword(vectorTerminos, &cantidadElementos);

				for (int i = 0; i < cantidadElementos; i++) {

					bool encontro;
					Elementos *elemento = this->buscarEnArbol(vectorFiltrado[i],this->lexico,&encontro);
					string aux = elemento->getN()->toString();
					int idTermino = atoi(aux.c_str());
					mapaBits* firmaTermino = this->gestorArchivoDePorciones->obtenerFirma(idTermino);
					firmaTermino->cambiarEstadoRegistro(registro);
					this->gestorArchivoDePorciones->guardarFirma(*firmaTermino,idTermino);
				}

			}
	}
	frases.close();
}

void indice::buscarFrases(string frase) {

	fstream frases;
	frases.open(PATH_ARCHIVO_FRASES, ios::binary|ios::in|ios::out);
	ofstream resultado;
	resultado.open(PATH_RESULTADO_BUSQUEDA);

	if((!frases)&&(!resultado))
		cout << "No se pudo abrir el archivo de frases para busquedas" << endl;

	else {

			interpreteFrases *interprete = new interpreteFrases(&frases);

			if (!interprete)
				cout << "Error al crear el interprete de frases" << endl;
			else {
				int cantidadElementos = 0;
				string* vectorTerminos = interprete->parsearFrase(frase,&cantidadElementos);
				interprete->normalizarTerminos(vectorTerminos,cantidadElementos);
				string* vectorFiltrado = interprete->filtroStopword(vectorTerminos, &cantidadElementos);

				if(cantidadElementos == 2)
					if (vectorFiltrado[0] == vectorFiltrado[1])
						cantidadElementos = 1;

				mapaBits* porciones = new mapaBits[cantidadElementos];
				resultado << "Terminos buscados: " << endl;

				for (int i = 0; i < cantidadElementos; i++) {

					resultado << vectorFiltrado[i] << " ";
					bool encontro;
					Elementos *elemento = this->buscarEnArbol(vectorFiltrado[i],this->lexico,&encontro);
					if (encontro) {
						string aux = elemento->getN()->toString();
						int idTermino = atoi(aux.c_str());
						mapaBits* firmaTermino = this->gestorArchivoDePorciones->obtenerFirma(idTermino);
						porciones[i] = *firmaTermino;//Fijarse que cuando quiero eliminar pincha el programa.
					}
					else {
						cout << "Ninguna frase contiene todos los terminos buscados" << endl;
						return;
					}
				}

				resultado << endl;
				resultado << endl;
				resultado << "Tiempo de busqueda:" << endl;

				int registros = 0;

				timeval ti,tf;
				double tiempo;
				gettimeofday(&ti, NULL);
				int* ocurrencias = this->identificarRegistro(porciones,cantidadElementos,&registros);
				gettimeofday(&tf, NULL);
				tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
				resultado << tiempo/1000 << " " << "segundos" << endl;
				char* serial = new char[TAMANIO_REGISTRO_FRASE];
				if(registros == 0) {
					cout << "Ninguna frase contiene el/los terminos buscados" << endl;
					resultado.close();
					remove(PATH_RESULTADO_BUSQUEDA);
				}
				else {

					resultado << endl;
					resultado << "Frases encontradas:" << endl;
					resultado << endl;

					for(int j = 0; j < registros; j++) {
						frases.seekg(TAMANIO_REGISTRO_FRASE * ocurrencias[j]);
						frases.read(serial,TAMANIO_REGISTRO_FRASE);
						cout << "(" << ocurrencias[j] << ")" << " " << serial << endl;
						resultado << "(" << ocurrencias[j] << ")" << " " << serial << endl;
					}
				}
				resultado.close();
				delete[] ocurrencias;
				delete[] serial;
			}
	}
	frases.close();
}

int* indice::identificarRegistro(mapaBits* porciones, int numPorciones, int* registrosValidos) {

	int* ocurrencias = new int[TAM_PORCION];
	int k = 0;
	if(!ocurrencias)
		cout << "El programa no hallo memoria" << endl;
	else {

		for (int i = 1; i <= TAM_PORCION; i++) {
			int j = 0;
			bool libre = false;
			while ((j < numPorciones)&&(!libre)) {
				libre = porciones[j].libre(i);
				j++;
			}
			if (!libre) {
				ocurrencias[k] = i;
				k++;
			}
		}
	}
	*registrosValidos = k;
	return ocurrencias;
}

void indice::mostrarFirma(string palabra) {
	bool encontro;
	Elementos *elemento = this->buscarEnArbol(palabra,this->lexico,&encontro);
	if(!encontro)
		cout << "No se puede devolver la forma del termino ya que el mismo no se encuentra indexado" << endl;
	else {
		int registro;
		string aux = elemento->getN()->toString();
		registro = atoi(aux.c_str());
		mapaBits* firma = this->gestorArchivoDePorciones->obtenerFirma(registro);
		firma->mostrar();
	}
}





