
#include "NodoInterior.h"


NodoInterior::NodoInterior(int nivel) : Nodo(nivel) {
	this->hijos = new int[(ARBOLBMAS_TAM_EFECTIVO_NODO/(ARBOLBMAS_TAM_CONTROL_REGISTRO)) + 2];
}

NodoInterior::NodoInterior() : Nodo(0) {
	this->hijos = new int[(ARBOLBMAS_TAM_EFECTIVO_NODO/(ARBOLBMAS_TAM_CONTROL_REGISTRO)) + 2];
}

NodoInterior::~NodoInterior() {
	delete[] hijos;
}

Persistencia NodoInterior::Serializar() {
	Persistencia cadena;

	cadena.agregarAlFinal(&nivel,sizeof(nivel));
	cadena.agregarAlFinal(&cantidadClaves, sizeof(cantidadClaves));

	int posicion;
	for (posicion = 0; posicion < cantidadClaves; ++posicion) {
		cadena.agregarAlFinal(claves[posicion].Serializar());
		cadena.agregarAlFinal(&hijos[posicion], sizeof(int));
	}
	cadena.agregarAlFinal(&hijos[posicion], sizeof(int));

	char vacio = ARBOLBMAS_CONST_VACIO;
	int espacioLibre = ARBOLBMAS_TAM_TOTAL_NODO - cadena.getTamanio();
	for (int i = 0; i < espacioLibre; i++) {
		cadena.agregarAlFinal(&vacio, sizeof(vacio));
	}
	return cadena;
}

bool NodoInterior::Hidratar(Persistencia & cadena) {
	bool exito = true;

	if ((int)cadena.getTamanio() != (ARBOLBMAS_TAM_TOTAL_NODO)) {
		exito = false;
	} else {
		int offset = 0;
		nivel = cadena.leerEntero(offset);
		offset += sizeof(nivel);
		cantidadClaves = cadena.leerEntero(offset);
		offset += sizeof(cantidadClaves);

		int posicion;
		for (posicion = 0; posicion < cantidadClaves; ++posicion) {

			char tamanioClave;
			cadena.leer(&tamanioClave,offset,ARBOLBMAS_TAM_LONG_CLAVE);
			Persistencia cadenaClave = cadena.leer(offset, ARBOLBMAS_TAM_LONG_CLAVE + tamanioClave);
			Clave unaClave;
			unaClave.Hidratar(cadenaClave);
			claves[posicion] = unaClave;
			offset += ARBOLBMAS_TAM_LONG_CLAVE + tamanioClave;

			hijos[posicion] = cadena.leerEntero(offset);
			offset += sizeof(int);
			espacioOcupado += tamanioClave + ARBOLBMAS_TAM_CONTROL_REGISTRO;
		}
		hijos[posicion] = cadena.leerEntero(offset);
	}
	return exito;
}
