#include "HandlerArchivoOcurrencias.h"

HandlerArchivoOcurrencias::HandlerArchivoOcurrencias(string ruta) {
        this->rutaArchivo = ruta;
        this->cantidadOcurrencias = 0;
}

HandlerArchivoOcurrencias::~HandlerArchivoOcurrencias() {

}

void HandlerArchivoOcurrencias::grabarRegistro(int idTermino, int idFrase) {

        ofstream archivoOcurrencias;

        archivoOcurrencias.open((this->rutaArchivo).c_str(),ios::binary|ios::out|ios::app);

        if (archivoOcurrencias) {

                archivoOcurrencias.write((char*)&idTermino,sizeof(int));
                archivoOcurrencias.write((char*)&idFrase,sizeof(int));
                archivoOcurrencias.flush();
                archivoOcurrencias.close();
                this->aumentarOcurrencias();
        }

        else
                cout << "El archivo de ocurrencias no se puedo abrir para escritura" << endl;

}

void HandlerArchivoOcurrencias::leerRegistro(int numeroRegistro, int* idTermino, int* idFrase, ifstream * archivoOcurrencias) {

        archivoOcurrencias->read((char*)idTermino,sizeof(int));
        archivoOcurrencias->read((char*)idFrase,sizeof(int));
}

void HandlerArchivoOcurrencias::eliminarArchivo() {
        remove((this->rutaArchivo).c_str());
}

int HandlerArchivoOcurrencias::getNumeroOcurrencias() {
        return this->cantidadOcurrencias;
}

void HandlerArchivoOcurrencias::putNumeroOcurrencias(int numeroOcurrencias) {
        this->cantidadOcurrencias = numeroOcurrencias;
}

void HandlerArchivoOcurrencias::aumentarOcurrencias() {
        this->cantidadOcurrencias++;
}

void HandlerArchivoOcurrencias::sort(int carga) {

        ifstream archivo;
        archivo.open((this->rutaArchivo).c_str(),ios::binary|ios::in);

        if (archivo) {
                Ordenador* unOrdenador = new Ordenador(carga);
                unOrdenador->ordenamientoEnRam(&archivo);
                this->eliminarArchivo();
        }

        else
                cout << "Error al abrir el archivo de particiones para el sort" << endl;

}

bool HandlerArchivoOcurrencias::finLectura(int registros) {

        if (registros == this->cantidadOcurrencias)
                return true;
        else
                return false;
}


string HandlerArchivoOcurrencias::intToStr(int n) {

        stringstream result;
        result << n;
        return result.str();
}

