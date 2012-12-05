#ifndef REGISTRONORMALIZADO_H_
#define REGISTRONORMALIZADO_H_


#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
#include <string>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <stdio.h>
#include "../Constantes.h"


using namespace std;

struct Ocurrencia {
	int idTermino;
	int idFrase;

}__attribute__((packed));

class Fusionador{
    private:
        string* filePaths; //array de char* con los path de los archivos
        int tamBuffer; //cant de registros que contiene el buffer
        int cant_arch; //cantidad de archivos
        int cant_buffers;
        int numEtapas;
        string ultimoPath;
        int cantRegs;

    public:
        Fusionador(string filePaths[], int tamBuffer, int cant_arch);
        void destruir();
        int inicializarBuffers(Ocurrencia** buffers); //devuelve la cantidad de buffers que no pudieron ser alocados. Se intentan alocar 11
        void destruirBuffers(Ocurrencia** buffers);
        void informar(int cant_archivos, int cant_buffers, int numEtapa);
        int getCantRegs();
        void abrirArchivos(string filePaths[], ifstream* archs,int num_archs);
        void cerrarArchivos(ifstream* archs, int num_archs);
        Ocurrencia minimo(Ocurrencia** buffers,unsigned short* v_pos, int num_particiones, unsigned short* pos_min);
        void cargarBuffers(Ocurrencia* buffers[], ifstream* archs, int num_particiones, int tamBuffer);
        bool finFusion(Ocurrencia* buffers[], int num_particiones, unsigned short v_pos[]);
        void fusionar_particiones(ifstream* archs, Ocurrencia** buffers, int num_particiones, int tamBuffer, string path_nuevo_arch);
        bool bufferVacio(Ocurrencia* buffer, unsigned short pos_actual);
        void cargarUnBuffer(Ocurrencia buffer[], ifstream* arch, int tamBuffer); //carga buffer y si el archivo llega al final, coloca clave invalida al final del buffer
        string IntToStr(int n);
        void actualizarPaths(string paths_viejos[], string paths_nuevos[], unsigned short cant_paths);
        void prepararPaths(string filePathsTotales[],string filePathsAUsar[], int cant, int cant_buffers);
        int merge();
        int mayor(Ocurrencia ocurrrencia1, Ocurrencia ocurrencia2);

};


#endif /* FUSIONADOR_H_ */
