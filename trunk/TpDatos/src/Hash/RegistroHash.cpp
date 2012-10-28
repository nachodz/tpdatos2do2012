
#include "RegistroHash.h"
#include "../Constantes.h"

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

//TODO: implementar!
bool RegistroHash::vacio() {
	/*if (this->bloque_sig == -1 && this->offsets.empty() == true)
		return true;*/
	return false;
}

Persistencia RegistroHash::Serializar() {
	Persistencia cadena;

	//n es la clave
	cadena.agregarAlFinal(&this->n, sizeof(this->getN()));

	//guardo puntero a bloque siguiente
	cadena.agregarAlFinal(&this->bloqueSiguiente, sizeof(this->getBloqueSiguiente()));

	//guardo autor si es que existe
	if(this->autor != NULL){

		//guardo apellido autor
		//TODO: guardar el tamañio como char! se esta desperdiciando 3 bytes!
		int tamApellido = this->getAutor()->getApellido().length();
		cadena.agregarAlFinal(&tamApellido,sizeof(int));
		string ape = this->getAutor()->getApellido();
		cadena.agregarAlFinal(ape);

		if(this->getAutor()->tieneNombre()){
			//guardo nombre autor
			int tamNombre = this->getAutor()->getNombre().length();
			cadena.agregarAlFinal(&tamNombre,sizeof(int));
			string nom = this->getAutor()->getNombre();
			cadena.agregarAlFinal(nom);
		}

	}
	//guardo la frase
	int tamFrase = this->getFrase().length();
	cadena.agregarAlFinal(&tamFrase,sizeof(int));
	string frase = this->getFrase();
	cadena.agregarAlFinal(frase);

	return cadena;
}

bool RegistroHash::Hidratar(Persistencia& cadena) {

	bool exito;

	//el tamaño debe ser al menos el tamaño de la longitud del registro y la clave
	if (cadena.getTamanio() < (HASH_TAM_LONG_REGISTRO + HASH_TAM_LONG_CLAVE))  {
		exito = false;
	}else{
		//recupero tamanio registro
		int tamanioRegistro = cadena.getTamanio();
		int offset = 0;
		//recupero n
		int clave = cadena.leerEntero(offset);
		this->setN(clave);
		offset += HASH_TAM_LONG_CLAVE;

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

}

void RegistroHash::actualizar(Autor* autor,string frase){
	this->setAutor(autor);
	this->setFrase(frase);
}

