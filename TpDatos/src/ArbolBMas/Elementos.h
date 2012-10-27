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
	//Persistencia* ID;
	Persistencia* n;
	Persistencia* enteroFantasma;
public:
	/*
	 * Constructor vacio
	 */
	Elementos();

	/*
	 * Constructor
	 */
	Elementos(Clave* clave, Persistencia* datos, Persistencia* n,Persistencia* enteroFantasma);

	/*
	 * Clone
	 */
	Elementos* Clonar();

	/*
	 * Serializar
	 */
	Persistencia Serializar();

	/*
	 * Metodo que hidrata un registro.
	 * Pre: la cadena debe representar a un registro
	 * Pos: queda hidratado el registro
	 */
	bool Hidratar(Persistencia &cadena);

	/*
	 * Getters y setters
	 */
	Clave *getClave() const;
	Persistencia* getDatos() const;
	Persistencia* getN() const;
	Persistencia* getEnteroFantasma() const;

    /* El getTamanio calcula la suma de los sizeof de:
     * 		datos
     * 		clave
     * 		int
     */
    int getTamanio() const;
//    Persistencia* getID();
    void setClave(Clave *clave);
    void setDatos(Persistencia* datos);
    void setN(Persistencia* n);
    void setEnteroFantasma(Persistencia* enteroFantasma);
//	void setID (Persistencia* id);
    string toString();

	/*
	 * Destructor
	 * Pos: libera la memoria de clave y de los datos
	 * 		si estos existian.
	 */
	virtual ~Elementos();

};

#endif /* REGISTRO_H_ */
