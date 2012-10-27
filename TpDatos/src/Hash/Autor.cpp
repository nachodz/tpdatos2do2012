
#include "Autor.h"

Autor::Autor(){
	this->apellido = "";
	this->nombre = "";
}

Autor::Autor(string nombre, string apellido){
	this->apellido = apellido;
	this->nombre = nombre;
}

Autor::~Autor() {
	// TODO Auto-generated destructor stub
}

string Autor::getNombre(){
	return this->nombre;
}

void Autor::setNombre(string nombre){
	this->nombre = nombre;
}

string Autor::getApellido(){
	return this->apellido;
}

void Autor::setApellido(string apellido){
	this->apellido = apellido;
}

int Autor::getTamanio(){
	if(this->tieneNombre())
		return this->nombre.length()+this->apellido.length();
	return this->apellido.length();
}

bool Autor::tieneNombre(){
	if (!this->getNombre().empty() && this->getNombre().length()>0)
		return true;
	return false;
}

string Autor::toString(){
	string cadena;

	cadena = this->getApellido();
	if (this->tieneNombre())
		cadena += " "+this->getNombre();
	return cadena;
}

