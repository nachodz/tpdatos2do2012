
#include "mapaBits.h"

mapaBits::mapaBits(){

}

mapaBits::mapaBits(int tamanio) {

	this->tamanio = tamanio;

	if (tamanio < TAMANIO_BINARIO) {
		this->porcion = new unsigned short int[1];
		this->longPorcion = 1;
	}
	else {
		if (tamanio%TAMANIO_BINARIO == 0) {
			this->porcion = new unsigned short int[tamanio/TAMANIO_BINARIO];
			this->longPorcion = tamanio/TAMANIO_BINARIO;
		}
		else {
			this->porcion = new unsigned short int[(tamanio/TAMANIO_BINARIO)+1];
			this->longPorcion = (tamanio/TAMANIO_BINARIO)+1;
		}
	}
}

mapaBits::~mapaBits() {
	delete[] porcion;
}

char* mapaBits::serializar() {

	char* serial = new char[this->tamanio];
	char* auxiliar = new char[sizeof(unsigned short int)];
	unsigned short int numero;

	if ((serial)&&(auxiliar)){
		for (int i = 0; i < (this->longPorcion); i++){
			numero = this->porcion[i];
			auxiliar = (char*)&numero;
			memmove(&(serial[i*sizeof(unsigned short int)]), auxiliar, sizeof(unsigned short int));
		}
	}
	else
		cout << "El programa no hallo memoria disponible";

	return serial; //No funciona el delete para el auxiliar
}

void mapaBits::hidratar(char*serial) {

	char* auxiliar = new char[sizeof(unsigned short int)];
	unsigned short int *numero = new unsigned short int(0);

	if (auxiliar) {
		for (int i = 0; i < (this->longPorcion); i++) {
			memmove(auxiliar, &(serial[i*sizeof(unsigned short int)]), sizeof(unsigned short int));
			numero = (unsigned short int*)auxiliar;
			this->porcion[i] = *numero;
		}
	}
	else
		cout << "El programa no hallo memoria disponible";

	delete[] auxiliar;
}

int mapaBits::getTamanio() {
	return this->tamanio;
}

unsigned short int mapaBits::getNumero(int posicion) {

	return this->porcion[posicion];
}

void mapaBits::putNumero(int posicion,int numero) {
	this->porcion[posicion] = numero;
}

int* mapaBits::generarBinario(unsigned short int numero) {

	int* binario = new int[TAMANIO_BINARIO];
	unsigned short int resto;

	if (binario) {
		for(int i = TAMANIO_BINARIO-1; i >= 0; i--) {
			if (numero >= 1) {
				resto = numero%2;
				binario[i] = resto;
				numero = numero/2;
			}
			else
				binario[i] = 0;
		}
	}
	else
		cout << "El programa no hallo memoria disponible" << endl;

	return binario;
}

int mapaBits::generarDecimal(int* binario) {

	int decimal = 0;
	int potencia;
	int base;

	for(int i = 0, j = TAMANIO_BINARIO - 1; i < TAMANIO_BINARIO; i++, j--) {

		base = binario[i];
		if(base == 1) {
			potencia = pow(2,j);
			decimal = decimal + potencia;
		}
	}

	return decimal;
}


void mapaBits::cambiarEstadoRegistro(int numeroRegistro) {

	if (numeroRegistro < this->tamanio) {

		int* binario = new int[TAMANIO_BINARIO];
		unsigned short int filaAbuscar;
		int fila = numeroRegistro/TAMANIO_BINARIO;
		int columna = numeroRegistro%TAMANIO_BINARIO;

		if (binario) {
			filaAbuscar = this->getNumero(fila);
			binario = this->generarBinario(filaAbuscar);

			if(binario[columna] == 0)
				binario[columna] = 1;
			else
				binario[columna] = 0;

			filaAbuscar = this->generarDecimal(binario);
			this->putNumero(fila,filaAbuscar);
		}
		else
			cout << "El programa no hallo memoria disponible";
	}
	else
		cout << "El numero excede el tamanio de la firma";
}

void mapaBits::mostrar() {

	unsigned short int fila;
	int* binario = new int[TAMANIO_BINARIO];

	for (int i = 0; i < (this->tamanio/TAMANIO_BINARIO); i++) {
		fila = this->getNumero(i);
		binario = this->generarBinario(fila);
		for (int j = 0; j < TAMANIO_BINARIO; j++) {
			int bit = binario[j];
			cout << bit;
		}
	}
	cout << endl;
	delete[] binario;
}

bool mapaBits::libre(int numeroRegistro) {

	int* binario = new int[TAMANIO_BINARIO];
	unsigned short int filaAbuscar;
	int fila = numeroRegistro/TAMANIO_BINARIO;
	int columna = numeroRegistro%TAMANIO_BINARIO;

	if (binario) {
		filaAbuscar = this->getNumero(fila);
		binario = this->generarBinario(filaAbuscar);

		if(binario[columna] == 1)
			return false;
		else
			return true;
	}
	else
	{
		cout << "El programa no hallo memoria disponible" << endl;
		return false;
	}
}

int mapaBits::getElementosOcupados() {

	int contador = 0;

	for (int i = 0; i < (this->tamanio); i++){
		if(!this->libre(i)){
			contador++;
		}
	}
	return contador-1;
}

void mapaBits::inicializar(){

	unsigned short int i = 0;
	while (i != this->longPorcion) {
		this->porcion[i] = 0;
		i++;
	}
}

int mapaBits::primerRegitroLibre() {

	int i = 0, j = 0;
	bool libre = false;
	unsigned short int numero;
	int* binario = new int[TAMANIO_BINARIO];

	if (binario) {

		while ((i < (this->longPorcion))&&(!libre)){
			numero = this->getNumero(i);
			binario = this->generarBinario(numero);

			while ((j < TAMANIO_BINARIO)&&(!libre)) {
				int auxiliar;
				auxiliar = binario[j];
				if(auxiliar == 0)
					libre = true;
				j = j+1;
			}
			i = i+1;
			if(!libre)
				j = 0;
		}
		delete[] binario;
		if (!libre)
			return -1; //Si devuelve -1 es que esta lleno
		else
			return ((j-1)+((i-1)*TAMANIO_BINARIO));
	}
	else
		cout << "El programa no hallo memoria disponible";
		return -2;
}

void mapaBits::asignarBit(int numeroRegistro) {

	if (numeroRegistro < this->tamanio) {

		int* binario = new int[TAMANIO_BINARIO];
		unsigned short int filaAbuscar;
		int fila = numeroRegistro/TAMANIO_BINARIO;
		int columna = numeroRegistro%TAMANIO_BINARIO;

		if (binario) {
			filaAbuscar = this->getNumero(fila);
			binario = this->generarBinario(filaAbuscar);

			if(binario[columna] == 0)
				binario[columna] = 1;

			filaAbuscar = this->generarDecimal(binario);
			this->putNumero(fila,filaAbuscar);
		}
		else
			cout << "El programa no hallo memoria disponible";
	}
	else
		cout << "El numero excede el tamanio de la firma";
}
