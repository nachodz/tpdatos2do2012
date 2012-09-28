/*
 * ArbolBMas.h
 *
 *  Created on: 27/09/2012
 *      Author: nacho
 */

#ifndef ARBOLBMAS_H_
#define ARBOLBMAS_H_

#include <iostream>
#include "Serializable.h"
#include "Constante.h"
#include "Nodo.h"
#include "NodoHoja.h"
#include "NodoInterno.h"
#include "PersistenciaArbol.h"
#include "Log.h"

using namespace std;

class ArbolBMas {

private:

	Nodo* raiz;
	int cantidadNodos;
	PersistenciaArbol* persistidor;

public:
	ArbolBMas();
	virtual ~ArbolBMas();

	//Getters y Setters
	Nodo* getRaiz();
	void setRaiz(Nodo* raiz);
	int getCantidadNodos();
	void setCantidadNodos(int cantidadNodos);
	PersistenciaArbol* getPersistenciaArbol();
	void setPersistenciaArbol(PersistenciaArbol* persistidor);

	/*
	 * Crea un arbolB+. Raiz vacia y almacenada en un archivo por persistidor
	 * No necesitamos archivo con referencias a nodos vacios xq no hay bajas
	 */
	ArbolBMas* crear();

private:

	void persistirNodo(Nodo* unNodo);
	Nodo* hidratarNodo(int numeroDeNodo);
	NodoInterno* crearNodoInterno(int nivel);
	NodoHoja* crearNodoHoja();
};

#endif /* ARBOLBMAS_H_ */
