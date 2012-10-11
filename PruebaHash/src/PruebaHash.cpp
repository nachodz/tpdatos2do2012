
#include <stdio.h>
#include <iostream>
#include "Constantes.h"
#include "Autor.h"
#include "Hash.h"
#include "RegistroHash.h"


using namespace std;

int main() {

	Hash hash(NOM_BLOQUES, NOM_ESP_LIBRE, NOM_TABLA);

	int n = 1234;
	Autor* autor = new Autor("Bayetto","Ignacio Javier");
	string frase = "Dale que sale el TP de Datos!";

	hash.alta(n,autor,frase);

	int n2 = 45;
	Autor* autor2 = new Autor("Perez","Juan");
	string frase2 = "Racing y nada mas";

	hash.alta(n2,autor2,frase2);

	int n3 = 41029;
	//Autor* autor3 = new Autor("Garcia","Carlos");
	string frase3 = "Listo el Hash :)";

	hash.alta(n3,NULL,frase3);

	hash.modificar(12,autor2,"Mira como modifico");

	hash.mostrar(NOM_SALIDA);

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

