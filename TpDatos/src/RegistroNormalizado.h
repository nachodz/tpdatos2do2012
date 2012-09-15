/*
 * RegistroNormalizado.h
 *
 *  Created on: 15/09/2012
 *      Author: francisco
 */

#ifndef REGISTRONORMALIZADO_H_
#define REGISTRONORMALIZADO_H_

#include <string>

using namespace std;


class RegistroNormalizado {
private:
	string termino;
	int ID;
public:
	RegistroNormalizado(string termino, int ID);
	virtual ~RegistroNormalizado();
	string putTermino();
	int putID();
};

#endif /* REGISTRONORMALIZADO_H_ */
