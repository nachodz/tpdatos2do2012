/*
 * ArbolBMas.cpp
 *
 *  Created on: 27/09/2012
 *      Author: nacho
 */

#include "ArbolBMas.h"

using namespace std;

ArbolBMas::ArbolBMas() {
	this->persistidor = new PersistenciaArbol();
	this->raiz = NULL;
	this->cantidadNodos = 0;
}

ArbolBMas::~ArbolBMas() {
	delete(persistidor);
}

ArbolBMas* ArbolBMas::crear(){
	//TODO: hacer el free del arbol por fuera de crear().
	ArbolBMas* arbolBMas;

	Log::getInstancia()->informacion(LOG_LABEL_ARBOLBMAS,"Creo Arbol B+");
	arbolBMas = new ArbolBMas();
	Nodo* raiz = arbolBMas->hidratarNodo(0);
	arbolBMas->setRaiz(raiz);
	arbolBMas->persistirNodo(arbolBMas->getRaiz());

	return arbolBMas;
}

//************** Privados *****************
void ArbolBMas::persistirNodo(Nodo* unNodo) {
	this->getPersistenciaArbol()->guardarBloque(unNodo->getNumero(), unNodo->serializar());
}

Nodo* ArbolBMas::hidratarNodo(int numeroDeNodo) {

	Persistencia cadena = this->persistidor->leerBloque(numeroDeNodo);
	if (cadena.estaVacia()) {
		return NULL;
	} else {
		int nivel = cadena.leerEntero(0);
		if (nivel == 0) {
			NodoHoja *nuevoNodoHoja = crearNodoHoja();
			nuevoNodoHoja->hidratar(cadena);
			nuevoNodoHoja->numero = numeroDeNodo;
			return nuevoNodoHoja;
		} else {
			NodoInterno *nuevoNodoInterno = crearNodoInterno(nivel);
			nuevoNodoInterno->hidratar(cadena);
			nuevoNodoInterno->numero = numeroDeNodo;
			return nuevoNodoInterno;
		}
	}
}

NodoHoja* ArbolBMas::crearNodoHoja() {
	NodoHoja* unNodoHoja = new NodoHoja();
	return unNodoHoja;
}


NodoInterno* ArbolBMas::crearNodoInterno(int nivel) {
	NodoInterno* unNodoInterior = new NodoInterno(nivel);
	return unNodoInterior;
}

//***********Getters y Setters*************
Nodo* ArbolBMas::getRaiz(){
	return this->raiz;
}

void ArbolBMas::setRaiz(Nodo* raiz){
	this->raiz = raiz;
}

int ArbolBMas::getCantidadNodos(){
	return this->cantidadNodos;
}

void ArbolBMas::setCantidadNodos(int cantidadNodos){
	this->cantidadNodos = cantidadNodos;
}

PersistenciaArbol* ArbolBMas::getPersistenciaArbol(){
	return this->persistidor;
}

void ArbolBMas::setPersistenciaArbol(PersistenciaArbol* persistidor){
	this->persistidor = persistidor;
}
