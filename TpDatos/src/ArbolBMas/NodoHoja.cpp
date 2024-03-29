
#include "NodoHoja.h"

NodoHoja::NodoHoja() : Nodo(0) {
	hojaSiguiente = 0;
	this->datos = new Persistencia[(ARBOLBMAS_TAM_EFECTIVO_NODO/(ARBOLBMAS_TAM_CONTROL_REGISTRO)) + 2];
	this->ns = new Persistencia[(ARBOLBMAS_TAM_EFECTIVO_NODO/(ARBOLBMAS_TAM_CONTROL_REGISTRO)) + 2];
	this->enterosFantasmas = new Persistencia[(ARBOLBMAS_TAM_EFECTIVO_NODO/(ARBOLBMAS_TAM_CONTROL_REGISTRO)) + 2];
}

NodoHoja::~NodoHoja() {
	delete[] datos;
	delete[] ns;
	delete[] enterosFantasmas;
}

Persistencia NodoHoja::Serializar() {
	Persistencia cadena;

	cadena.agregarAlFinal(&nivel,sizeof(nivel));
	cadena.agregarAlFinal(&cantidadClaves, sizeof(cantidadClaves));
	for (int posicion = 0; posicion < cantidadClaves; ++posicion) {

		int tamanioDato = datos[posicion].getTamanio();
		cadena.agregarAlFinal(&tamanioDato,sizeof(tamanioDato));
		cadena.agregarAlFinal(datos[posicion]);
		int tamanioN = ns[posicion].getTamanio();
		cadena.agregarAlFinal(&tamanioN,sizeof(tamanioN));
		cadena.agregarAlFinal(ns[posicion]);
		int tamanioEnterosFantasmas = enterosFantasmas[posicion].getTamanio();
		cadena.agregarAlFinal(&tamanioEnterosFantasmas,sizeof(tamanioEnterosFantasmas));
		cadena.agregarAlFinal(enterosFantasmas[posicion]);
	}
	cadena.agregarAlFinal(&hojaSiguiente, sizeof(hojaSiguiente));

	char vacio = ARBOLBMAS_CONST_VACIO;
	int espacioLibre = ARBOLBMAS_TAM_TOTAL_NODO - cadena.getTamanio();
	for (int i = 0; i < espacioLibre; i++) {
		cadena.agregarAlFinal(&vacio, sizeof(vacio));
	}
	return cadena;
}

bool NodoHoja::Hidratar(Persistencia & cadena) {
	bool exito = true;

	if ((int)cadena.getTamanio() != (ARBOLBMAS_TAM_TOTAL_NODO)) {
		exito = false;
	} else {
		int offset = 0;
		nivel = cadena.leerEntero(offset);
		offset += sizeof(nivel);
		cantidadClaves = cadena.leerEntero(offset);
		offset += sizeof(cantidadClaves);

		for (int posicion = 0; posicion < cantidadClaves; ++posicion) {

			int tamanioDato = cadena.leerEntero(offset);
			offset += ARBOLBMAS_TAM_LONG_DATO;
			Persistencia unDato;
			unDato.agregarAlFinal(cadena.leer(offset,tamanioDato));
			datos[posicion] = unDato;
			offset += tamanioDato;

			Persistencia cadenaClave = Persistencia(datos[posicion]);
			Persistencia claveString = cadenaClave.datosSinFrontCoding(PATH_ARBOL);
			Clave* unaClave = new Clave(claveString.toString());

			claves[posicion] = *unaClave;
			delete(unaClave);

			int tamanioN = cadena.leerEntero(offset);
			offset += sizeof(int);
			Persistencia unN;
			unN.agregarAlFinal(cadena.leer(offset,tamanioN));
			ns[posicion] = unN;
			offset += tamanioN;

			int tamanioEnteroFantasma = cadena.leerEntero(offset);
			offset += sizeof(int);
			Persistencia unEnteroFantasma;
			unEnteroFantasma.agregarAlFinal(cadena.leer(offset,tamanioEnteroFantasma));
			enterosFantasmas[posicion] = unEnteroFantasma;
			offset += tamanioEnteroFantasma;

			espacioOcupado +=  tamanioDato + tamanioN + tamanioEnteroFantasma + ARBOLBMAS_TAM_CONTROL_REGISTRO;
		}
		hojaSiguiente = cadena.leerEntero(offset);
	}
	return exito;
}

NodoHoja* NodoHoja::Clonar() {
	NodoHoja* nodoHoja = new NodoHoja();
	nodoHoja->nivel = this->nivel;
	nodoHoja->espacioOcupado = this->espacioOcupado;
	nodoHoja->cantidadClaves = this->cantidadClaves;
	nodoHoja->hojaSiguiente = this->hojaSiguiente;
	for (int i=0; i < this->cantidadClaves; ++i) {
		nodoHoja->claves[i] = this->claves[i];
	}
	for (int i=0; i < this->cantidadClaves; ++i) {
		nodoHoja->datos[i] = this->datos[i];
	}
	for (int i=0; i < this->cantidadClaves; ++i) {
		nodoHoja->ns[i] = this->ns[i];
	}
	for (int i=0; i < this->cantidadClaves; ++i) {
		nodoHoja->enterosFantasmas[i] = this->enterosFantasmas[i];
	}
	return nodoHoja;
}


Persistencia* NodoHoja::getDatos() const {
	return this->datos;
}

void NodoHoja::setDatos(Persistencia* datos){
	this->datos = datos;
}

Persistencia* NodoHoja::getNs() const {
	return this->ns;
}

void NodoHoja::setNs(Persistencia* ns){
	this->ns = ns;
}

Persistencia* NodoHoja::getEnterosFantasmas() const {
	return this->enterosFantasmas;
}

void NodoHoja::setEnterosFantasmas(Persistencia* enterosFantasmas){
	this->enterosFantasmas = enterosFantasmas;
}

int NodoHoja::getHojaSiguiente() const {
	return hojaSiguiente;
}
