#ifndef FRONTCODING_H_
#define FRONTCODING_H_
#include <string>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;

class FrontCoding{
private:
	int distinto;
	int igual;
	string path;
	int offset;
	string cadena;
	/*
	 * Le aplica el front coding a la palabra que se le pase por parametro
	 * pre: -
	 * post: setea las variables offset+igual+distinto+cadena
	 */
	void aplicarFrontCoding(string primerPalabraNodo, string palabra);
	/*
	 * Se fija segun la palabra del primer nodo que offset debe usar en el front
	 * coding.
	 * pre:-
	 * post: si la palabra ya existe retorna el offset, sino la agrega a la lista
	 * 		 y retorna el offset
	 */
	void obtenerOffset(string primerPalabraNodo);
	/*
	 * Graba en la lista de palabras enteras para llevar el front codig Parcial
	 * pre: no debe estar la palabra en la lista
	 * post: graba el offset donde guardo la palabra
	 */
	void grabarAlFinal(string primerPalabraNodo);
	/*
	 * Obtiene la palabra del archivo de front coding
	 * pre: la palabra en el archivo de front coding debe existir
	 * psot: palabra retornada
	 */
	string obtenerPalabra();
public:

	FrontCoding(){
		distinto = igual = offset = 0;
		path = cadena = "";
	}
	FrontCoding(string ruta);

	virtual ~FrontCoding();
    string getCadena() const{
        return cadena;
    }

    int getDistinto() const{
        return distinto;
    }

    int getIgual() const{
        return igual;
    }

    void setCadena(string cadena){
        this->cadena = cadena;
    }

    void setDistinto(int distinto){
        this->distinto = distinto;
    }

    void setIgual(int igual){
        this->igual = igual;
    }
    /*
     * retorna la palabra pasada a front coding
     * pre: pasar la primer palabra del nodo para obtener el offset
     * post: palabra en codigo front coding
     */
    string pasarAFrontCoding(string primerPalabraNodo, string palabra);
    /*
     * Interpreta el codigo front Coding que se le pase y te duevle la palabra
     * pre: busca la palabra contra la que compara en el archivo de front coding
     * post: devuelve la palabra
     */
    string interpretarFrontCoding(string frontCoding);
    /*
     * Interpreta el codigo para obtener el tamanio correspondiente
     * pre: se le pasa una palabra que esta expresada en front coding
     * post: devuelve el tamanio correspondiente
     */
    int deducirTamanio(string fc);
};

#endif /* FRONTCODING_H_ */
