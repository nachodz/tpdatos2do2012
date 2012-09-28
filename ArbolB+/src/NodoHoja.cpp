/*
 * NodoHoja.cpp
 *
 *  Created on: 27/09/2012
 *      Author: nacho
 */

#include "NodoHoja.h"

NodoHoja::NodoHoja() {
	// TODO Auto-generated constructor stub

}

NodoHoja::~NodoHoja() {
	// TODO Auto-generated destructor stub
}

Persistencia NodoHoja::serializar() {
	Persistencia cadena;
/*
	cadena.agregarAlFinal(&nivel,sizeof(nivel));
	cadena.agregarAlFinal(&cantidadClaves, sizeof(cantidadClaves));
	for (int posicion = 0; posicion < cantidadClaves; ++posicion) {
		cadena.agregarAlFinal(claves[posicion].Serializar());
		int tamanioDato = datos[posicion].getTamanio();
		cadena.agregarAlFinal(&tamanioDato,sizeof(tamanioDato));
		cadena.agregarAlFinal(datos[posicion]);
		int tamanioID = Ids[posicion].getTamanio();
		cadena.agregarAlFinal(&tamanioID,sizeof(tamanioID));
		cadena.agregarAlFinal(Ids[posicion]);
	}
	cadena.agregarAlFinal(&hojaSiguiente, sizeof(hojaSiguiente));

	char vacio = CONST_VACIO;
	int espacioLibre = TAM_TOTAL_NODO - cadena.getTamanio();
	for (int i = 0; i < espacioLibre; i++) {
		cadena.agregarAlFinal(&vacio, sizeof(vacio));
	}*/
	return cadena;

}

bool NodoHoja::hidratar(Persistencia & cadena) {
	bool exito = true;

/*	if ((int)cadena.getTamanio() != (TAM_TOTAL_NODO)) {
		exito = false;
	} else {
		int offset = 0;
		nivel = cadena.leerEntero(offset);
		offset += sizeof(nivel);
		cantidadClaves = cadena.leerEntero(offset);
		offset += sizeof(cantidadClaves);

		for (int posicion = 0; posicion < cantidadClaves; ++posicion) {

			char tamanioClave;
			cadena.leer(&tamanioClave,offset,TAM_LONG_CLAVE);
			Persistencia cadenaClave = cadena.leer(offset, TAM_LONG_CLAVE + tamanioClave);
			Clave unaClave;
			unaClave.Hidratar(cadenaClave);
			claves[posicion] = unaClave;
			offset += TAM_LONG_CLAVE + tamanioClave;

			int tamanioDato = cadena.leerEntero(offset);
			offset += TAM_LONG_DATO;
			Persistencia unDato;
			unDato.agregarAlFinal(cadena.leer(offset,tamanioDato));
			datos[posicion] = unDato;
			offset += tamanioDato;

			int tamanioID = cadena.leerEntero(offset);
			offset += TAM_LONG_DATO;
			Persistencia unID;
			unID.agregarAlFinal(cadena.leer(offset,tamanioID));
			Ids[posicion] = unID;
			offset += tamanioID;

			espacioOcupado += tamanioClave + tamanioDato + tamanioID + TAM_CONTROL_REGISTRO;
		}
		hojaSiguiente = cadena.leerEntero(offset);
	}
*/
	return exito;
}


//*********Getters y Setters***************

int NodoHoja::getNroHojaSiguiente(){
	return this->nroHojaSiguiente;
}

void NodoHoja::setNroHojaSiguiente(int nroHojaSiguiente){
	this->nroHojaSiguiente = nroHojaSiguiente;
}

Persistencia* NodoHoja::getDatos(){
	return this->datos;
}

void NodoHoja::setDatos(Persistencia* datos){
	this->datos = datos;
}
