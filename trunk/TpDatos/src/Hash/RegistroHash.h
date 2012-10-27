
#ifndef REGISTROHASH_H_
#define REGISTROHASH_H_

#include "Autor.h"
#include "Serializable.h"
#include <string>

using namespace std;

class RegistroHash : public Serializable {

private:
	int n;
	int bloqueSiguiente;
	Autor* autor;
	string frase;

public:
	RegistroHash();
	RegistroHash(int clave,Autor* autor,string frase);
	RegistroHash(int clave);
	virtual ~RegistroHash();

	int getN();
	void setN(int n);

	Autor* getAutor();
	void setAutor(Autor* autor);

	string getFrase();
	void setFrase(string frase);

	int getTamanio();

	int getClave();
	void setClave(int clave);

	int getBloqueSiguiente();
	void setBloqueSiguiente(int bloqueSiguiente);

	void toString(ostream& os);
	bool vacio();

	void actualizar(Autor* autor,string frase);

	Persistencia Serializar();
	bool Hidratar(Persistencia &cadena);

};

#endif /* REGISTROHASH_H_ */
