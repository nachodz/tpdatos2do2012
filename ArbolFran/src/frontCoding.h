/*
 * frontCoding.h
 *
 *  Created on: 25/09/2012
 *      Author: francisco
 */

#ifndef FRONTCODING_H_
#define FRONTCODING_H_

#include "registros.h"

using namespace std;

class frontCoding {

private:

public:

	frontCoding();

	virtual ~frontCoding();

	void pasarAfrontCoding(tClave *claves, int numElem, tRegistroHoja *registros);

	void sacarFrontCoding(tRegistroHoja *registros, int numElem, tClave *claves);

//	int LetrasIguales(string palabra1, string palabra2);
//
//	string letrasDistintas(string palabra, int coin);

};

#endif /* FRONTCODING_H_ */
