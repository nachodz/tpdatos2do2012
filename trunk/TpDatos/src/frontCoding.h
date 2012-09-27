/*
 * frontCoding.h
 *
 *  Created on: 25/09/2012
 *      Author: francisco
 */

#ifndef FRONTCODING_H_
#define FRONTCODING_H_

#include "RegistroHoja.h"
#include "clave.h"

using namespace std;

class frontCoding {

private:

public:

	frontCoding();

	virtual ~frontCoding();

	void pasarAfrontCoding(clave claves[], int numElem, RegistroHoja registros[]);

	void sacarFrontCoding(RegistroHoja registros[], int numElem, clave claves[]);

	int LetrasIguales(string palabra1, string palabra2);

	string letrasDistintas(string palabra, int coin);

};

#endif /* FRONTCODING_H_ */
