
#include "HandlerArchivoPorciones.h"

HandlerArchivoPorciones::HandlerArchivoPorciones(string ruta) {
	this->rutaArchivo = ruta;
	this->numeroFirmas = 0;
}

HandlerArchivoPorciones::~HandlerArchivoPorciones() {

}

mapaBits* HandlerArchivoPorciones::obtenerFirma(int numeroTermino) {

	mapaBits* firma = new mapaBits(TAM_PORCION); //Cambiar cuando este guardado el tamanio.

	ifstream archivoFirmas;
	archivoFirmas.open((this->rutaArchivo).c_str(), ios::binary|ios::in);

	archivoFirmas.seekg(0,ios::end);
	int regs = archivoFirmas.tellg()/(firma->getTamanio()/BYTE);

	if(numeroTermino < regs) {

		char* serial = new char[firma->getTamanio()/BYTE];

		if ((archivoFirmas)&&(firma)&&(serial)) {

			archivoFirmas.seekg(numeroTermino*(firma->getTamanio()/BYTE));
			archivoFirmas.read(serial,firma->getTamanio()/BYTE);
			archivoFirmas.close();
			firma->hidratar(serial);
			delete[] serial;
		}

		else
			cout << "Error al abrir el archivo de firmas para lectura o el programa no encuentra memoria" << endl;
	}
	else
		cout << "El numero de porcion buscado no existe" << endl;

	return firma;
}

void HandlerArchivoPorciones::guardarFirma(mapaBits firma, int numeroTermino) {

		fstream archivoFirmas;
		archivoFirmas.open((this->rutaArchivo).c_str(),ios::binary|ios::out|ios::in);
		char* serial = new char[firma.getTamanio()/BYTE];

		if((archivoFirmas)&&(serial)) {

			serial = firma.serializar();
			archivoFirmas.seekp(numeroTermino*(firma.getTamanio()/BYTE));
			archivoFirmas.write(serial,firma.getTamanio()/BYTE);
			archivoFirmas.flush();
			archivoFirmas.close();
			delete[] serial;
		}
		else
			cout << "Error al abrir el archivo de firmas para escritura o el programa no encuentra memoria" << endl;
}


int HandlerArchivoPorciones::getNumeroFirmas() {
	return this->numeroFirmas;
}

void HandlerArchivoPorciones::putNumeroFirmas(int numeroFirmas) {
	this->numeroFirmas = numeroFirmas;
}

void HandlerArchivoPorciones::aumentarCantidadFirmas() {
	(this->numeroFirmas)++;
}
