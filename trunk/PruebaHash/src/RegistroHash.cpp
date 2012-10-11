/*
 * RegistroHash.cpp
 *
 *  Created on: 07/10/2012
 *      Author: nacho
 */

#include "RegistroHash.h"
#include "Constantes.h"

RegistroHash::RegistroHash(){
	 this->setClave(-1);
	 this->setBloqueSiguiente(-1);
}

RegistroHash::RegistroHash(int clave,Autor* autor, string frase){
	this->setClave(clave);
	this->setAutor(autor);
	this->setBloqueSiguiente(-1);
	this->setFrase(frase);
}

RegistroHash::RegistroHash(int clave){
	this->setClave(clave);
	this->setBloqueSiguiente(-1);
}

RegistroHash::~RegistroHash() {
	// TODO Auto-generated destructor stub
}

int RegistroHash::getN(){
	return this->n;
}

void RegistroHash::setN(int n){
	this->n = n;
}

Autor* RegistroHash::getAutor(){
	return this->autor;
}

void RegistroHash::setAutor(Autor* autor){
	this->autor = autor;
}

string RegistroHash::getFrase(){
	return this->frase;
}

void RegistroHash::setFrase(string frase){
	this->frase = frase;
}

int RegistroHash::getTamanio() {
	int tamApellidoAutor = 0;
	int tamNombreAutor = 0;

	//los sizeof(int) son porque se guardan las longitudes de los string
	if (this->autor != NULL){
		tamApellidoAutor = this->getAutor()->getApellido().length() + sizeof(int);
		if (this->getAutor()->tieneNombre()){
			tamNombreAutor = this->getAutor()->getNombre().length() + sizeof(int);
		}
	}
    return (sizeof(this->n) + sizeof(this->bloqueSiguiente) + tamApellidoAutor + tamNombreAutor + sizeof(int) + this->frase.length());
}

int RegistroHash::getClave(){
	return this->getN();
}

void RegistroHash::setClave(int clave){
	this->setN(clave);
}

int RegistroHash::getBloqueSiguiente(){
	return this->bloqueSiguiente;
}

void RegistroHash::setBloqueSiguiente(int bloqueSiguiente){
	this->bloqueSiguiente = bloqueSiguiente;
}

bool RegistroHash::vacio() {
	//TODO: esperando respuesta!
	/*if (this->bloque_sig == -1 && this->offsets.empty() == true)
		return true;*/
	return false;
}

Persistencia RegistroHash::Serializar() {
	Persistencia cadena;

	//guardo tamanio del registro
	//int tamanio = getTamanio();
	//cadena.agregarAlFinal(&tamanio,sizeof(int));

	//n es la clave
	cadena.agregarAlFinal(&this->n, sizeof(this->getN()));

	//guardo puntero a bloque siguiente
	cadena.agregarAlFinal(&this->bloqueSiguiente, sizeof(this->getBloqueSiguiente()));

	//guardo auto si es que existe
	if(this->autor != NULL){

		//agrego un byte con el caracter # para saber si hay autor
		//char flag = '#';
		//cadena.agregarAlFinal(&flag,sizeof(char));
		int tamApellido = this->getAutor()->getApellido().length();
		cadena.agregarAlFinal(&tamApellido,sizeof(int));
		string ape = this->getAutor()->getApellido();
		//cadena.agregarAlFinal(&ape,ape.length());
		cadena.agregarAlFinal(ape);

		if(this->getAutor()->tieneNombre()){

			//agrego un byte con el caracter ? para saber si hay nombre
			//char flag2 = '?';
			//cadena.agregarAlFinal(&flag2,sizeof(char));
			int tamNombre = this->getAutor()->getNombre().length();
			cadena.agregarAlFinal(&tamNombre,sizeof(int));
			string nom = this->getAutor()->getNombre();
			//cadena.agregarAlFinal(&nom,nom.length());
			cadena.agregarAlFinal(nom);

		}

	}
	//guardo la frase
	int tamFrase = this->getFrase().length();
	cadena.agregarAlFinal(&tamFrase,sizeof(int));
	string frase = this->getFrase();
	//cadena.agregarAlFinal(&frase,frase.length());
	cadena.agregarAlFinal(frase);

	return cadena;
}

bool RegistroHash::Hidratar(Persistencia& cadena) {

	bool exito;
	//int hayAutor=0,hayNombreAutor=0;

	//el tamaño debe ser al menos el tamaño de la longitud del registro y la clave
	if (cadena.getTamanio() < (TAM_LONG_REGISTRO + TAM_LONG_CLAVE))  {
		exito = false;
	}else{
		//recupero tamanio registro
		//int tamanioRegistro = cadena.leerEntero(0);
		int tamanioRegistro = cadena.getTamanio();
		int offset = 0;
		//recupero n
		int clave = cadena.leerEntero(offset);
		this->setN(clave);
		offset += TAM_LONG_CLAVE;

		//recupero puntero a bloque siguiente
		int bloqueSiguiente = cadena.leerEntero(offset);
		this->setBloqueSiguiente(bloqueSiguiente);
		offset += sizeof(this->getBloqueSiguiente());

		Persistencia campo;
		int tamCampo;
		tamCampo = cadena.leerEntero(offset);
		offset += sizeof(int);
		campo = cadena.leer(offset,tamCampo);
		offset += tamCampo;

		//si es igual al tamReg Campo = Frase
		//TODO: hacer el delete!
		this->setAutor(new Autor());
		if (offset != tamanioRegistro){
			//si no es igual al tamReg Campo = Apellido
			this->getAutor()->setApellido(campo.toString());
			tamCampo = cadena.leerEntero(offset);
			offset += sizeof(int);
			campo = cadena.leer(offset,tamCampo);
			offset += tamCampo;

			//si es igual al tamReg Campo = Frase
			if (offset != tamanioRegistro){
				//si no es igual al tamReg Campo = Nombre
				this->getAutor()->setNombre(campo.toString());
				tamCampo = cadena.leerEntero(offset);
				offset += sizeof(int);
				campo = cadena.leer(offset,tamCampo);
				offset += tamCampo;
			}
		}

		this->setFrase(campo.toString());

		//Persistencia flagAutor = cadena.leer(TAM_LONG_CLAVE + sizeof(this->getBloqueSiguiente()),1);
		//char* flag = new char('#');
		/*if(flagAutor.toString().compare(flag)==0){
			//recuepero autor
			this->setAutor(new Autor());
			hayAutor = 1;
			unsigned int posIniApe = (TAM_LONG_CLAVE + sizeof(this->getBloqueSiguiente()) + sizeof(char));
			Persistencia apellido = (cadena.leer(posIniApe,tamanioRegistro - posIniApe));
			this->getAutor()->setApellido(apellido.toString());

			Persistencia flagNombre = cadena.leer(TAM_LONG_CLAVE + sizeof(this->getBloqueSiguiente()) + sizeof(char) + this->getAutor()->getApellido().length(),1);
			char* flag2 = new char('?');
			if (flagNombre.toString().compare(flag2)==0){
				//recupero nombre autor
				hayNombreAutor = 1;
				unsigned int posIniNom = (TAM_LONG_CLAVE + sizeof(this->getBloqueSiguiente()) + sizeof(char) + this->getAutor()->getApellido().length() + sizeof(char));
				Persistencia nombre = (cadena.leer(posIniNom,tamanioRegistro - posIniNom));
				this->getAutor()->setNombre(nombre.toString());
			}
		}

		//recupero frase
		 int espFlagAutor = hayAutor;
		 int espApellidoAutor = 0;
		 if (hayAutor==1)
			espApellidoAutor =  this->getAutor()->getApellido().length();
		 int espFlagNombreAutor = hayNombreAutor;
		 int espNombreAutor = 0;
		 if (hayNombreAutor == 1)
			 espNombreAutor = this->getAutor()->getNombre().length();

		unsigned int posIniFrase = (TAM_LONG_REGISTRO + TAM_LONG_CLAVE + espFlagAutor + espApellidoAutor + espFlagNombreAutor + espNombreAutor);
		Persistencia frase = cadena.leer(posIniFrase,tamanioRegistro - posIniFrase);
		this->setFrase(frase.toString());
		*/
		exito = true;
	}

	return exito;
}

void RegistroHash::toString(ostream& os) {
	os << "   Registro --> " << endl;

	os << "     Clave:   " << this->getClave() << endl;
	os << "     Bloque siguiente:   " << this->getBloqueSiguiente() << endl;
	if(this->getAutor()!= NULL)
		os << "     Autor:   " << this->getAutor()->toString() << endl;
	os << "     Frase:   " << this->getFrase() << endl;
	os << "     Tamaño ocupado:   " << this->getTamanio() << " Bytes" << endl;

	/*list < int > ::iterator it;
	int i = 0;
	for (it = this->offsets.begin(); it != this->offsets.end(); ++ it) {
		os << "     Offset #" << i << ":   " << *it << endl;
		++ i;
	}
	*/
}

void RegistroHash::actualizar(Autor* autor,string frase){
	this->setAutor(autor);
	this->setFrase(frase);
}

