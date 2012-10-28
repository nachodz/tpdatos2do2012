
#ifndef NODOHOJA_H_
#define NODOHOJA_H_

#include "Nodo.h"

class NodoHoja : public Nodo {

	friend class ArbolBMas;
	friend class IteradorArbolBMas;

private:
	int hojaSiguiente;
	Persistencia* datos;
	Persistencia* ns;
	Persistencia* enterosFantasmas;

public:
	NodoHoja();
	virtual ~NodoHoja();

	Persistencia Serializar();
	bool Hidratar(Persistencia & cadena);

    Persistencia *getDatos() const;
    void setDatos(Persistencia* datos);

    Persistencia *getNs() const;
    void setNs(Persistencia* ns);

    Persistencia *getEnterosFantasmas() const;
    void setEnterosFantasmas(Persistencia* enterosFantasmas);

    int getHojaSiguiente() const;

    NodoHoja* Clonar();
};

#endif /* NODOHOJA_H_ */
