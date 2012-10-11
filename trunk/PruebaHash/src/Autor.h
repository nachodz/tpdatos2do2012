/*
 * Autor.h
 *
 *  Created on: 07/10/2012
 *      Author: nacho
 */

#ifndef AUTOR_H_
#define AUTOR_H_

#include <string>

using namespace std;

class Autor {
private:
	string nombre;
	string apellido;
public:
	Autor();
	Autor(string apellido, string nombre);
	virtual ~Autor();

	string getNombre();
	void setNombre(string nombre);

	string getApellido();
	void setApellido(string apellido);

	int getTamanio();
	bool tieneNombre();

	string toString();

};

#endif /* AUTOR_H_ */
