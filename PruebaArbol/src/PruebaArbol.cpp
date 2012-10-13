//============================================================================
// Name        : PruebaArbol.cpp
// Author      : Nacho
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "ArbolBMas.h"
#include <iostream>

using namespace std;


int main() {
	cout << "INICIO: PRUEBA ARBOLB+ " << endl;

	ArbolBMas* arbol = new ArbolBMas(PATH_ARBOL);

	Elementos* elemento = new Elementos(new Clave("arbol"), new Persistencia("arbol"), new Persistencia("12"), new Persistencia("0"));
	arbol->insertar(elemento);
	cout << "INGRESO ELEMENTO 1 " << endl;

	Elementos* elemento2 = new Elementos(new Clave("arboleda"), new Persistencia("arboleda"), new Persistencia("123"), new Persistencia("0"));
	arbol->insertar(elemento2);
	cout << "INGRESO ELEMENTO 2 " << endl;

	Elementos* elemento3 = new Elementos(new Clave("arquero"), new Persistencia("arquero"), new Persistencia("1"), new Persistencia("0"));
	arbol->insertar(elemento3);
	cout << "INGRESO ELEMENTO 3 " << endl;

	Elementos* elemento4 = new Elementos(new Clave("arboles"), new Persistencia("arboles"), new Persistencia("23"), new Persistencia("0"));
	arbol->insertar(elemento4);
	cout << "INGRESO ELEMENTO 4 " << endl;

	Elementos* elemento5 = new Elementos(new Clave("arbitro"), new Persistencia("arbitro"), new Persistencia("3"), new Persistencia("0"));
	arbol->insertar(elemento5);
	cout << "INGRESO ELEMENTO 5 " << endl;

	Elementos* elemento6 = new Elementos(new Clave("arboleda"), new Persistencia("arbol"), new Persistencia("12"), new Persistencia("0"));
	arbol->borrar(elemento6);
	cout << "BORRO ELEMENTO 2 " << endl;

	arbol->mostrar();

	Elementos* elemento7 = new Elementos(new Clave("arbitro"), new Persistencia("arbitro"), new Persistencia("9999"), new Persistencia("0"));
	arbol->modificar(elemento7);

	cout << "FIN: PRUEBA ARBOLB+ " << endl;
	return 0;
}
