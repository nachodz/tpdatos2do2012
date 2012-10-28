
#ifndef PERSISTORARBOL_H_
#define PERSISTORARBOL_H_
#include "Persistencia.h"
#include "../Handler/HandlerBloques.h"
#include <string.h>
#include <fstream>

class PersistorArbol {
private:
	HandlerBloques * handlerBloque;
	string rutaOut;
	string ruta;
	int tamanioBloque;

public:
	PersistorArbol(string ruta, int tamanioBloque);

	/*
	 * Metodo que sirve para guardar un bloque en el archivo
	 * Pre:
	 * Pos:
	 */
	bool guardarBloque (int nroBloque, Persistencia cadena);

	/*
	 * Metodo que sirve para leer un bloque del archivo
	 * Pre: El numero de bloque debe ser valido
	 * Pos: Devuelve una el bloque leido en una "CadenaBytes".
	 * 		Si el numero de bloque es invalido o no se puede realizar la lectura
	 * 		se retorna un objeto "CadenaBytes" vacio
	 */
	Persistencia leerBloque (int nroBloque);

	int getTamanioArchivo();

	int getCantidadBloques();

	string getRuta();

	virtual ~PersistorArbol();
};

#endif /* PERSISTORARBOL_H_ */
