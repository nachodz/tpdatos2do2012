/*
 * Arbol.h
 *
 *  Created on: 07/10/2012
 *      Author: francisco
 */

#ifndef ARBOL_H_
#define ARBOL_H_

#include "NodoHoja.h"
#include "NodoInterno.h"
#include "Constantes.h"
#include "registros.h"
#include "Persistidor.h"
#include <string.h>
#include "Nodo.h"


using namespace std;

class Arbol {

private:

	Nodo *raiz;
	Nodo *actual;
	int cantNodos;
	Persistidor persistidorArbol;

public:

//	Nodo *raiz;
//	Nodo *actual;
//	int cantNodos;

	Arbol();
	virtual ~Arbol();
	void cargaInicial(int cantRegistros);
	void alta(tClave registro);
	tClave busqueda(tClave registro);
	void generarClaves(tRegistroDiccionario *buffer, tClave *claves, int cant, int *posicion);
	void buscarNodo(tClave registro);
	void buscarNodoRec(tClave registro);
	void aumentarCantNodo();
	int getCantNodo();

};

#endif
