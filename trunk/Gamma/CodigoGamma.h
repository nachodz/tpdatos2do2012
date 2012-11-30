#ifndef CODIGOGAMMA_H_
#define CODIGOGAMMA_H_
#include <string>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <list>
#include <iostream>

using namespace std;
class CodigoGamma {

private:
	int numAConvertir;
	/*
	 * MÃ©todo que me forma la primer parte de la conversion correspondiente al unario
	 * pre: -
	 * pos: Obtengo en un string el unario correspondiente
	 */
	std::string obtenerUnario(int numAConvertir);
	/*
	 * MÃ©todo que me forma la segunda parte de la conversion correspondiente al binario
	 * pre: -
	 * pos: Obtengo en un string el binario correspondiente
	 */
	std::string conversionRepresentacion(int numAConvertir);

	/*
	 * MÃ©todo que me pasa a binario un numero en "cantidadBits" de  bits
	 * pre: -
	 * pos: Obtengo en un string el binario correspondiente
	 */
	std::string obtenerBinarioDeNBits(int valorConversion, int cantidadBits);

	/*
	 * MÃ©todo que me pasa un binario a un numero entero
	 * pre: -
	 * pos: Obtengo el entero correspondiente al binario pasado por parametro
	 */
	int interpretarBinario(std::string binarioAInterpretar);
public:
/*------------ Constructores y destructor --------------*/
	CodigoGamma();
	CodigoGamma(int numeroAConvertir);
	virtual ~CodigoGamma();

/*-----MÃ©todo de conversion y de interpretacion Gamma-----*/
	/*
	 * Metodo que realiza la compresiÃ³n a Gamma
	 * pre:-
	 * pos: Conversion realizada y devuelta en un string
	 */
	std::string aplicarConversion();

	/*
	 * Realiza la conversion de un string en gamma que contiene cantDocs y los nrosDocs
	 * y devuelve una lista de los nroDocs
	 * pre: Le paso un string en gamma que tiene primero la cantDocs y despues los nroDocs
	 * post: Devuelvo lista de nroDocs
	 */

	std::list<int> decodificarLista(std::string conversion);

	/*
	 * Metodo que realiza la conversion de Gamma a un numero
	 * pre: Le paso una conversion hecha en gamma
	 * pos: Obtengo el numero que representa esa conversion
	 */

	int interpretarConversion(std::string conversion);

	/*
	 * Metodo que realiza la compresion de una lista en codigos gamma
	 * pre: Le paso la lista a comprimir
	 * pos: Obtengo la tira de bits en un string
	 */
	std::string comprimirLista(std::list<int> listaInvertida, int primero);

	/*
	 * Metodo que convierte una tira de bits a un string de unos y ceros
	 * pre: Le paso un char*
	 * post: devuelve el valor del char* en binario, en un string de unos y ceros
	 */

	std::string convertirAString(char* buf);

	/*
	 * Metodo que convierte un string de unos y ceros a caracteres en un string
	 * pre: Le paso un string de unos y ceros entornado a byte(longitud multiplo de 8)
	 * post: devuelve el string correspondiente
	 */
	std::string stringABits(std::string cadena);

/*------------ GETTERS AND SETTERS --------------*/
	void setNumAConvertir (int num){
		this->numAConvertir = num;
	}
	int getNumAConvertir() const{
		return this->numAConvertir;
	}

};

#endif /* CODIGOGAMMA_H_ */
