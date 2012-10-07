#ifndef REGISTRONORMALIZADO_H_
#define REGISTRONORMALIZADO_H_


#include <iostream>
#include <string>
#include <cstring>
#include <string>

using namespace std;

    struct Registro{
        int ID; //4 bytes
        char palabra[25];  //25 bytes
    }__attribute__((packed)); //29 bytes

class Fusionador{
    private:
        string filePaths[]; //array de char* con los path de los archivos
        int tamBuffer; //cant de registros que contiene el buffer
        int cant_arch; //cantidad de archivos
        int cant_buffers;

    public:
        Fusionador(string filePaths[], int tamBuffer, int cant_arch);
        int inicializarBuffers(Registro** buffers); //devuelve la cantidad de buffers que no pudieron ser alocados. Se intentan alocar 11
        void abrirArchivos(string filePaths[], ifstream* archs,int num_archs);
        void cerrarArchivos(ifstream* archs, int num_archs);
        void cargarBuffers(Registro* buffers[], ifstream* archs, int num_particiones, int tamBuffer);
        bool finFusion(Registro* buffers[], int num_particiones, unsigned short v_pos[]);
        int fusionar_particiones(ifstream* archs, Registro* buffers[], int num_particiones, int tamBuffer, string path_nuevo_arch);
        string IntToStr(int n);
        int merge();

};


#endif /* FUSIONADOR_H_ */
