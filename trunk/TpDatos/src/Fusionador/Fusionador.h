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

    struct Registro{
        int ID; //4 bytes
        char palabra[25];  //25 bytes
    }__attribute__((packed)); //29 bytes

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
        int inicializarBuffers(Registro** buffers); //devuelve la cantidad de buffers que no pudieron ser alocados. Se intentan alocar 11
        void destruirBuffers(Registro** buffers);
        void informar(int cant_archivos, int cant_buffers, int numEtapa);
        void abrirArchivos(string filePaths[], ifstream* archs,int num_archs);
        void cerrarArchivos(ifstream* archs, int num_archs);
        Registro minimo(Registro** buffers,unsigned short* v_pos, int num_particiones, unsigned short* pos_min);
        void cargarBuffers(Registro* buffers[], ifstream* archs, int num_particiones, int tamBuffer);
        bool finFusion(Registro* buffers[], int num_particiones, unsigned short v_pos[]);
        void fusionar_particiones(ifstream* archs, Registro** buffers, int num_particiones, int tamBuffer, string path_nuevo_arch);
        bool bufferVacio(Registro* buffer, unsigned short pos_actual);
        void cargarUnBuffer(Registro buffer[], ifstream* arch, int tamBuffer); //carga buffer y si el archivo llega al final, coloca clave invalida al final del buffer
        string IntToStr(int n);
        void actualizarPaths(string paths_viejos[], string paths_nuevos[], unsigned short cant_paths);
        void prepararPaths(string filePathsTotales[],string filePathsAUsar[], int cant, int cant_buffers);
        int merge();

};


#endif /* FUSIONADOR_H_ */
