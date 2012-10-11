//============================================================================
// Name        : PruebaHash.cpp
// Author      : Nacho
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <iostream>
#include "Constantes.h"
#include "Autor.h"
#include "Hash.h"
#include "RegistroHash.h"


using namespace std;

int main() {

	printf("Se generó un archivo en el directorio con la salida ( Path: SalidaPalabra )\n");
	Hash hash(NOM_BLOQUES_PALABRA, NOM_ESP_LIBRE_PALABRA, NOM_TABLA_PALABRA);
	//hash.mostrar(NOM_SALIDA_PALABRA);

	int n = 1234;
	Autor* autor = new Autor("Bayetto","Ignacio Javier");
	string frase = "Dale que sale el TP de Datos!";

	hash.alta(n,autor,frase);

	int n2 = 45;
	Autor* autor2 = new Autor("Bergmann","Catalina Victoria");
	string frase2 = "Amo mucho a mi novio nacho que es pegote y que me gusta mucho mucho mucho!!!!";

	hash.alta(n2,autor2,frase2);

	int n3 = 41029;
	//Autor* autor3 = new Autor("Fontela","Carlos");
	string frase3 = "tito";

	hash.alta(n3,NULL,frase3);

	hash.modificar(12,autor2,"Nacho me quiere!");

	hash.mostrar("SALIDAHASH");

	/*RegistroHash reg = hash.consultar(41,0);

	cout << "CLAVE - ";
	cout << reg.getN() << endl;
	cout << "AUTOR - Apellido: ";
	cout << reg.getAutor()->getApellido() << endl;
	cout << "AUTOR - Nombre:";
	cout << reg.getAutor()->getNombre() << endl;
	cout << "FRASE - ";
	cout << reg.getFrase() << endl;*/

	return 0;
}

