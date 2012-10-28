#ifndef REGISTRO_H_
#define REGISTRO_H_
#include "Clave.h"
#include <string>
using namespace std;
using std::string;

class Elementos : public Serializable {

private:
	Clave* clave;
	Persistencia* datos;
	Persistencia* n;
	Persistencia* enteroFantasma;
public:

	Elementos();

	Elementos(Clave* clave, Persistencia* datos, Persistencia* n,Persistencia* enteroFantasma);

	Elementos* Clonar();

	Persistencia Serializar();

	bool Hidratar(Persistencia &cadena);

	Clave *getClave() const;
	Persistencia* getDatos() const;
	Persistencia* getN() const;
	Persistencia* getEnteroFantasma() const;

    int getTamanio() const;
    void setClave(Clave *clave);
    void setDatos(Persistencia* datos);
    void setN(Persistencia* n);
    void setEnteroFantasma(Persistencia* enteroFantasma);
    string toString();

	virtual ~Elementos();

};

#endif /* REGISTRO_H_ */
