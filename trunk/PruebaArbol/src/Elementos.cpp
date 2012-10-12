
#include "Elementos.h"
//#include "Utilitarios.h"

Elementos::Elementos()
{
	/* La clave se incializa vacia, por lo que luego
	 * habra que aditar su valor.
	 */
	this->clave = new Clave("");
	this->datos = new Persistencia;
	this->n = new Persistencia;
	this->enteroFantasma = new Persistencia;
}

Elementos::Elementos(Clave* clave, Persistencia* datos, Persistencia* n,Persistencia* enteroFantasma)
{
	this->clave = clave;
	this->datos = datos;
	this->n = n;
	this->enteroFantasma = enteroFantasma;
}


Persistencia Elementos::Serializar()
{
	Persistencia cadena;
	//int tamanio = getTamanio();

	//guardo tamanio clave
	int tamanioClave = this->getClave()->getTamanio();
	cadena.agregarAlFinal(&tamanioClave,sizeof(int));
	//guardo clave
	cadena.agregarAlFinal(this->clave->Serializar());
	//guardo tamanio datos
	int tamanioDatos = this->getDatos()->getTamanio();
	cadena.agregarAlFinal(&tamanioDatos,sizeof(int));
	//guardo datos
	Persistencia* datos = this->getDatos();
	cadena.agregarAlFinal(*datos);
	//guardo n
	string nString = this->getN()->toString();
	const char* nChar = nString.c_str();
	int n = atoi(nChar);
	cadena.agregarAlFinal(&n,sizeof(int));
	//guardo enteroFantasma
	string enteroFantasmaString = this->getEnteroFantasma()->toString();
	const char* enteroFantasmaChar = enteroFantasmaString.c_str();
	int enteroFantasma = atoi(enteroFantasmaChar);
	cadena.agregarAlFinal(&enteroFantasma,sizeof(int));

	/*cadena.agregarAlFinal(&tamanio,sizeof(int));
	cadena.agregarAlFinal(this->clave->Serializar());
	cadena.agregarAlFinal(*this->datos);
	cadena.agregarAlFinal(*this->n);
	cadena.agregarAlFinal(*this->enteroFantasma);*/

	return cadena;
}


bool Elementos::Hidratar(Persistencia &cadena){
	bool exito;
	//el tamaño debe ser al menos el tamaño de la longitud del registro y la clave
	if (cadena.getTamanio() < (TAM_LONG_REGISTRO + TAM_LONG_CLAVE))  {
		exito = false;
	}else{
		int offset = 0;
		//leo tamanioClave
		int tamClave = cadena.leerEntero(offset);
		//leo clave
		Persistencia cadenaClave = cadena.leer(TAM_LONG_CLAVE, tamClave);
		this->clave->Hidratar(cadenaClave);
		offset += tamClave;
		//leo tamanioDatos
		int tamanioDatos = cadena.leerEntero(offset);
		offset += sizeof(int);
		//leo datos
		Persistencia datos = cadena.leer(offset,tamanioDatos);
		this->setDatos(&datos);
		offset += tamanioDatos;
		//leo n
		Persistencia n = cadena.leer(offset,sizeof(int));
		this->setN(&n);
		offset += sizeof(int);
		// leo enteroFantasma
		Persistencia enteroFantasma = cadena.leer(offset,sizeof(int));
		this->setEnteroFantasma(&enteroFantasma);
		offset += sizeof(int);

		/*if (this->datos) {
			delete (this->datos);
			this->datos = new Persistencia;
		}

		int tamanioRegistro = cadena.leerEntero(0);
		char tamanioClave;
		cadena.leer(&tamanioClave,TAM_LONG_REGISTRO,TAM_LONG_CLAVE);
		Persistencia cadenaClave = cadena.leer(TAM_LONG_REGISTRO,TAM_LONG_CLAVE + int(tamanioClave));
		this->clave->Hidratar(cadenaClave);
		unsigned int posicionComienzoDatos = (TAM_LONG_REGISTRO + TAM_LONG_CLAVE + int(tamanioClave));
		this->datos->agregarAlFinal(cadena.leer(posicionComienzoDatos,tamanioRegistro - posicionComienzoDatos));
		unsigned int posicionComienzoID = (TAM_LONG_REGISTRO + TAM_LONG_CLAVE + int(tamanioClave) + datos->getTamanio());
		this->ID->agregarAlFinal(cadena.leer(posicionComienzoID,tamanioRegistro - posicionComienzoID));*/
		exito = true;
	}
	return exito;
}


Elementos* Elementos::Clonar()
{
	return new Elementos(this->clave->Clonar(),this->datos, this->n, this->enteroFantasma);
}

/*Persistencia* Elementos::getID(){
	return this->ID;
}
void Elementos::setID (Persistencia* id){
	this->ID = id;
}*/

/*
 * Getters y setters
 */
Clave *Elementos::getClave() const
{
    return clave;
}

void Elementos::setClave(Clave *clave)
{
	if(this->clave) delete this->clave;
    this->clave = clave;
}

Persistencia* Elementos::getDatos() const
{
    return datos;
}

void Elementos::setDatos(Persistencia* datos)
{
	this->datos = datos;
}

Persistencia* Elementos::getN() const{
	return this->n;
}

void Elementos::setN(Persistencia* n){
	this->n = n;
}

Persistencia* Elementos::getEnteroFantasma() const{
	return this->enteroFantasma;
}

void Elementos::setEnteroFantasma(Persistencia* enteroFantasma){
	this->enteroFantasma = enteroFantasma;
}

int Elementos::getTamanio() const
{
    return (sizeof(int) + clave->getTamanio() + sizeof(int) + datos->getTamanio() + n->getTamanio() + enteroFantasma->getTamanio());
}

/*
 * Destructor
 */
Elementos::~Elementos() {

	if (this->clave) delete (this->clave);
	if (this->datos) delete (this->datos);
	if (this->n) delete (this->n);
	if (this->enteroFantasma) delete (this->enteroFantasma);
	//if (this->ID) delete (this->ID);
}

string Elementos::toString(){
	string cadena;
	cadena += "Clave: ";
	cadena += this->clave->toString();
	cadena += " | ";
	cadena += "Dato : ";
	cadena += this->datos->toString();
	cadena += " | ";
	cadena += "N: ";
	cadena += this->n->toString();
	cadena += "EnteroFantasma: ";
	cadena += this->enteroFantasma->toString();
	return cadena;
}

