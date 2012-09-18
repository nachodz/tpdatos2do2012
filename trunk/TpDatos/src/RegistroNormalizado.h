/*
 * RegistroNormalizado.h
 *
 *  Created on: 15/09/2012
 *      Author: francisco
 */

#ifndef REGISTRONORMALIZADO_H_
#define REGISTRONORMALIZADO_H_

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class RegistroNormalizado {

private:
	int tamPalabra;
	string termino;
	int ID;

public:
	RegistroNormalizado(string termino, int ID,int tamanio);
	virtual ~RegistroNormalizado();
	string getTermino();
	int getID();
	void guardar();
	void recuperar();
};

#endif /* REGISTRONORMALIZADO_H_ */
