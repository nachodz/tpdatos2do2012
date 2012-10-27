
#include "Nodo.h"


Nodo::Nodo(int nivel) {
	this->nivel = nivel;
	this->espacioOcupado = 0;
	this->cantidadClaves = 0;
	this->claves = new Clave[(ARBOLBMAS_TAM_EFECTIVO_NODO/(ARBOLBMAS_TAM_CONTROL_REGISTRO)) + 2];
}

Nodo::~Nodo() {
	delete[] claves;
}

bool Nodo::isNodoHoja() {
	return (nivel == 0);
}

bool Nodo::isOverflow(int tamanioRegistro) {
	return (espacioOcupado + tamanioRegistro > ARBOLBMAS_TAM_EFECTIVO_NODO);
}

bool Nodo::isUnderflow() {
	return (espacioOcupado < ARBOLBMAS_TAM_EFECTIVO_NODO / 2);
}

bool Nodo::puedeCederElementos() {
	return (espacioOcupado > ARBOLBMAS_TAM_EFECTIVO_NODO / 2);
}
