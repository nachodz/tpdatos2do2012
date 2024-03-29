
#include "ArbolBMas.h"
#include <iostream>


ArbolBMas::ArbolBMas(string ruta_archivo) {
	this->primeraHoja = 0;
	this->persistor = new PersistorArbol(ruta_archivo, ARBOLBMAS_TAM_TOTAL_NODO);
	this->raiz = hidratarNodo(0);
	if (this->raiz) {
		this->cantidadNodos = persistor->getTamanioArchivo() / ARBOLBMAS_TAM_TOTAL_NODO;
	} else {
		this->cantidadNodos = 0;
	}
	hidratarDatosConfiguracion();
}


ArbolBMas::~ArbolBMas() {
	if (raiz) {
		liberarMemoriaNodo(raiz);
	}
	delete this->persistor;
}

bool ArbolBMas::modificar(Elementos* registro) {
	Nodo *unNodo = raiz;
	if (!unNodo)
		return false;

	while (!unNodo->isNodoHoja()) {
		NodoInterior *unNodoInterior = static_cast<NodoInterior*> (unNodo);
		int posicion = obtenerPosicion(unNodoInterior, *(registro->getClave()));
		unNodo = hidratarNodo(unNodoInterior->hijos[posicion]);
		if (unNodoInterior != raiz)
			liberarMemoriaNodo(unNodoInterior);
	}

	NodoHoja *unNodoHoja = static_cast<NodoHoja*> (unNodo);
	int posicion = obtenerPosicion(unNodoHoja, *(registro->getClave()));
	bool existe = (posicion < unNodoHoja->cantidadClaves && claveIgual(*(registro->getClave()), unNodoHoja->claves[posicion]));
	if (existe) {
		unNodoHoja->ns[posicion].setBytes(registro->getN()->toString());
		unNodoHoja->enterosFantasmas[posicion].setBytes(registro->getEnteroFantasma()->toString());
		persistirNodo(unNodoHoja);
		return true;
	} else {
		if (unNodoHoja != raiz)
			liberarMemoriaNodo(unNodoHoja);
		return false;
	}
}



int ArbolBMas::insertar(Elementos* registro) {

	Nodo* nuevoNodoHijo = NULL;
	Clave clavePromocion;
	int idDevolucion = 0;

	if (raiz == NULL) {
		raiz = crearNodoHoja();
		raiz->numero = primeraHoja = 0;
		persistirDatosConfiguracion();
		(static_cast <NodoHoja*> (raiz))->hojaSiguiente = 0;
		this->cantidadNodos = 1;
	}
	string palabra = registro->getDatos()->toString();

	// Saco el frontcoding antes de insertar recursivamente
	registro->getDatos()->sacarElFrontCoding(palabra, persistor->getRuta());

	//TODO: devuelve bool
	insertarRecursivo(raiz, *(registro->getClave()), *(registro->getDatos()), *(registro->getN()), *(registro->getEnteroFantasma()), &clavePromocion, &nuevoNodoHijo);

	if (nuevoNodoHijo) {
		persistirNodo(nuevoNodoHijo);
		NodoInterior *nuevaRaiz = crearNodoInterior(raiz->nivel + 1);

		// Muevo la raiz a otra posicion y persisto la nueva raiz en la posicion cero
		raiz->numero = obtenerNumeroDeNodo();
		if (raiz->isNodoHoja()) {
			primeraHoja = raiz->numero;
			persistirDatosConfiguracion();
		}
		persistirNodo(raiz);

		nuevaRaiz->claves[0] = clavePromocion;
		nuevaRaiz->hijos[0] = raiz->numero;
		nuevaRaiz->hijos[1] = nuevoNodoHijo->numero;
		nuevaRaiz->cantidadClaves = 1;
		nuevaRaiz->espacioOcupado += clavePromocion.getTamanio() + ARBOLBMAS_TAM_CONTROL_REGISTRO;
		nuevaRaiz->numero = 0;
		persistirNodo(nuevaRaiz);

		liberarMemoriaNodo(raiz);
		liberarMemoriaNodo(nuevoNodoHijo);
		raiz = nuevaRaiz;
	} else {
		persistirNodo(raiz);
	}
	return idDevolucion;
}

void ArbolBMas::refactorizarNodoFrontCoding(NodoHoja** nodo){
	// Resto el tamaño del 1er dato
    (*nodo)->espacioOcupado -= ((*nodo))->datos[0].getTamanio();
    // Le saco el frontcoding a esa clave
    (*nodo)->datos[0].sacarElFrontCoding(((*nodo))->datos[0].toString(), persistor->getRuta());
    // Le sumo al nodo el tamaño del dato con la clave nueva
    (*nodo)->espacioOcupado += (*nodo)->datos[0].getTamanio();
	string primera = (*nodo)->datos[0].toString();

	// Hago lo mismo con el resto de las claves, pasandolas a frontcoding con respecto a la primera
	for (int i = 1; i < (*nodo)->cantidadClaves ; i++){
		(*nodo)->espacioOcupado -= ((*nodo))->datos[i].getTamanio();
		(*nodo)->datos[i].transformarAFrontCoding(primera, persistor->getRuta());
		(*nodo)->espacioOcupado += ((*nodo))->datos[i].getTamanio();
	}
}

void ArbolBMas::refactorizarNodoNoHojaFrontCoding(Nodo** nodo){
	// Resto el tamaño del 1er dato
	static_cast<NodoHoja*>(*nodo)->espacioOcupado -= (static_cast<NodoHoja*>(*nodo))->datos[0].getTamanio();
	// Le saco el frontcoding a esa clave
	static_cast<NodoHoja*>(*nodo)->datos[0].sacarElFrontCoding((static_cast<NodoHoja*>(*nodo))->datos[0].toString(),  persistor->getRuta());
	// Le sumo al nodo el tamaño del dato con la clave nueva
	static_cast<NodoHoja*>(*nodo)->espacioOcupado += static_cast<NodoHoja*>(*nodo)->datos[0].getTamanio();
	string primera = static_cast<NodoHoja*>(*nodo)->datos[0].toString();

	// Hago lo mismo con el resto de las claves, pasandolas a frontcoding con respecto a la primera
	for (int i = 1; i < static_cast<NodoHoja*>(*nodo)->cantidadClaves ; i++){
		static_cast<NodoHoja*>(*nodo)->espacioOcupado -= (static_cast<NodoHoja*>(*nodo))->datos[i].getTamanio();
		static_cast<NodoHoja*>(*nodo)->datos[i].transformarAFrontCoding(primera,  persistor->getRuta());
		static_cast<NodoHoja*>(*nodo)->espacioOcupado += (static_cast<NodoHoja*>(*nodo))->datos[i].getTamanio();
	}
}
void ArbolBMas::sacarFrontCodingNodo (Nodo ** nodo){
	// Resto el tamaño original en el nodo
	static_cast<NodoHoja*>(*nodo)->espacioOcupado -= (static_cast<NodoHoja*>(*nodo))->datos[0].getTamanio();
	// Le saco el frontcoding
	static_cast<NodoHoja*>(*nodo)->datos[0].sacarElFrontCoding((static_cast<NodoHoja*>(*nodo))->datos[0].toString(),  persistor->getRuta());
	// Sumo el nuevo tamaño sin el frontcoding en el nodo
	static_cast<NodoHoja*>(*nodo)->espacioOcupado += static_cast<NodoHoja*>(*nodo)->datos[0].getTamanio();

	// Hago lo mismo con el resto de las claves
	for (int i = 1; i < static_cast<NodoHoja*>(*nodo)->cantidadClaves ; i++){
		static_cast<NodoHoja*>(*nodo)->espacioOcupado -= (static_cast<NodoHoja*>(*nodo))->datos[i].getTamanio();
		static_cast<NodoHoja*>(*nodo)->datos[i].sacarElFrontCoding(static_cast<NodoHoja*>(*nodo)->datos[i].toString(),  persistor->getRuta());
		static_cast<NodoHoja*>(*nodo)->espacioOcupado += (static_cast<NodoHoja*>(*nodo))->datos[i].getTamanio();
	}
}

void ArbolBMas::sacarFrontCodingNodoHoja (NodoHoja ** nodo){
	// Resto el tamaño original en el nodo
    (*nodo)->espacioOcupado -= ((*nodo))->datos[0].getTamanio();
    // Le saco el frontcoding
    (*nodo)->datos[0].sacarElFrontCoding(((*nodo))->datos[0].toString(), persistor->getRuta());
    // Sumo el nuevo tamaño sin el frontcoding en el nodo
    (*nodo)->espacioOcupado += (*nodo)->datos[0].getTamanio();

    // Hago lo mismo con el resto de las claves
	for (int i = 1; i < (*nodo)->cantidadClaves ; i++){
		(*nodo)->espacioOcupado -= ((*nodo))->datos[i].getTamanio();
		(*nodo)->datos[i].sacarElFrontCoding((*nodo)->datos[i].toString(),  persistor->getRuta());
		(*nodo)->espacioOcupado += ((*nodo))->datos[i].getTamanio();
	}
}

void ArbolBMas::mostrar(){
	ofstream fo;
	string ruta = this->persistor->getRuta() + "_Salida.txt";
	fo.open(ruta.c_str(), ios_base::out);
	fo << "********************************************************************************" << endl << endl;
	fo << "		                   " << this->persistor->getRuta() << "                    " << endl << endl;
	fo << "********************************************************************************" << endl << endl;
	if (raiz){
		fo << "Tamanio de Nodo:  " << ARBOLBMAS_TAM_TOTAL_NODO << endl;
		fo << "	Primer Hoja:  " << primeraHoja << endl;
		fo << "--------------------------------------------------------------------------------" << endl << endl;
	}
	if (this->raiz){
		toString(this->raiz,1, fo);
	}
	fo.flush();
	fo.close();
}

void ArbolBMas::toString(Nodo* nodoAmostrar, int tab, ofstream& fo){

	if(nodoAmostrar){
		if (nodoAmostrar->isNodoHoja()) {
			NodoHoja *nodo = static_cast<NodoHoja*> (nodoAmostrar);
			for(int i=0 ; i<tab ; i++) fo << "  ";
				fo   << "Numero: " << nodo->numero <<  "  Nivel: " << nodo->nivel << "  Cant.Elem: " << nodo->cantidadClaves
				<< " Esp.Libre: " << ARBOLBMAS_TAM_EFECTIVO_NODO - nodo->espacioOcupado << "  Hoja.Sig: " << nodo->hojaSiguiente << "    " << endl;

			for(int i=0 ; i<tab ; i++) fo << "  ";
			for (int posicion = 0; posicion < nodo->cantidadClaves; ++posicion){
				fo << "(";
				Clave clave = nodo->claves[posicion].toString();
				fo << "Clave: " << clave.getClave();
				fo << " , ";
				fo << "Elemento: " << "(" << nodo->datos[posicion].toString() << ";" << nodo->ns[posicion].toString() << ";" << nodo->enterosFantasmas[posicion].toString() << ")";
				fo << ")";
			}
			fo << endl;
		} else {
			NodoInterior *nodoInt= static_cast<NodoInterior*> (nodoAmostrar);
			fo << endl;
			for(int i=0; i<tab ; i++)
				fo << "  ";
			fo << "Numero: " << nodoInt->numero << "  Nivel: " << nodoInt->nivel << "  Cant.Elem: " << nodoInt->cantidadClaves
					<< "  Esp.Libre: " << ARBOLBMAS_TAM_EFECTIVO_NODO - nodoInt->espacioOcupado << "  Claves: (";
			for (int posicion = 0; posicion <= nodoInt->cantidadClaves; ++posicion) {
				if (posicion < nodoInt->cantidadClaves) {
					Clave clave = nodoInt->claves[posicion];
					fo << clave.getClave();
					if (posicion == nodoInt->cantidadClaves-1){
						fo << ")" << endl;
					}else{
						fo << "," ;
					}
				}
			}
			int * hijos;
			Nodo *hijo;
			for (int posicion = 0; posicion <= nodoInt->cantidadClaves; ++posicion) {

				hijos = nodoInt->getHijos();
				hijo = hidratarNodo(hijos[posicion]);
				toString(hijo, tab+2, fo);
				if (hijo)
					liberarMemoriaNodo(hijo);
			}
			fo << endl;
		}
	}
}

int ArbolBMas::getCantidadBloques(){
	int tamanio = this->persistor->getTamanioArchivo();

	return (tamanio / ARBOLBMAS_TAM_TOTAL_NODO);
}

Nodo* ArbolBMas::leerNodo(int numeroDeNodo) {
	return hidratarNodo(numeroDeNodo);
}

NodoHoja* ArbolBMas::obtenerPrimeraHoja(){

	Nodo *unNodo = raiz;
	Clave* clave = new Clave("a"); //primera clave.
	if (unNodo){

		while (!unNodo->isNodoHoja()) {
			NodoInterior *unNodoInterior = static_cast<NodoInterior*> (unNodo);
			int posicion = obtenerPosicion(unNodoInterior, *clave);
			unNodo = hidratarNodo(unNodoInterior->hijos[posicion]);
			if (unNodoInterior != raiz)
				liberarMemoriaNodo(unNodoInterior);
		}

		NodoHoja *unNodoHoja = static_cast<NodoHoja*> (unNodo);
		return unNodoHoja;
	}

	return NULL;
}

void ArbolBMas::mostrarTodosTerminos(){

	NodoHoja *hoja = this->obtenerPrimeraHoja();
	bool mostrando = true;
	int nroHojaSiguiente;

	ofstream fo;
	string ruta = this->persistor->getRuta() + "_TodosTerminos.txt";
	fo.open(ruta.c_str(), ios_base::out);

	fo << "********************************************************************************" << endl << endl;
	fo << "		                    " << this->persistor->getRuta() << "                    " << endl << endl;
	fo << "                              Lista de términos                                 " << endl << endl;
	fo << "********************************************************************************" << endl << endl;

	while(mostrando){

		//Leo secuencialemente todos los terminos de las hojas
		for (int posicion = 0; posicion < hoja->cantidadClaves; ++posicion){
			Clave clave = hoja->claves[posicion].toString();
			fo << clave.getClave() << endl;
		}

		nroHojaSiguiente = hoja->getHojaSiguiente();
		if(nroHojaSiguiente != 0)
			hoja =  static_cast<NodoHoja*> (this->leerNodo(nroHojaSiguiente));
		else
			mostrando = false;
	}

	fo.flush();
	fo.close();
}


bool ArbolBMas::claveMenor(Clave clave1, Clave clave2) {
	if (clave1.getClave() < clave2.getClave()) return true;
	return false;
}

bool ArbolBMas::claveMenorIgual(Clave clave1, Clave clave2) {
	if (clave1.getClave() <= clave2.getClave()) return true;
	return false;
}

bool ArbolBMas::claveIgual(Clave clave1, Clave clave2) {
	if (clave1.getClave() == clave2.getClave()) return true;
	return false;
}

NodoHoja* ArbolBMas::crearNodoHoja() {
	NodoHoja* unNodoHoja = new NodoHoja();
	return unNodoHoja;
}

NodoInterior* ArbolBMas::crearNodoInterior(int nivel) {
	NodoInterior* unNodoInterior = new NodoInterior(nivel);
	return unNodoInterior;
}

void ArbolBMas::liberarMemoriaNodo(Nodo *unNodo) {
	if (unNodo->isNodoHoja()) {
		delete static_cast<NodoHoja*> (unNodo);
	} else {
		delete static_cast<NodoInterior*> (unNodo);
	}
	unNodo = NULL;
}

int ArbolBMas::obtenerPosicion(Nodo *unNodo, Clave clave) {

	if (unNodo->cantidadClaves == 0)
		return 0;

	int inferior = 0;
	int superior = (unNodo->cantidadClaves)-1;

	while (inferior < superior) {
		int medio = (inferior + superior) / 2;

		if (claveMenorIgual(clave, unNodo->claves[medio])) {
			superior = medio - 1;
		} else {
			inferior = medio + 1;
		}
	}

	if (superior < 0 || claveMenor(unNodo->claves[superior], clave))
		superior++;

	return superior;
}

bool ArbolBMas::insertarRecursivo(Nodo* nodoCorriente, Clave clave, Persistencia dato, Persistencia n, Persistencia enteroFantasma, Clave* clavePromocion, Nodo** nuevoNodo) {

	if (!nodoCorriente->isNodoHoja()) {

		NodoInterior *nodoInteriorCorriente = static_cast<NodoInterior*> (nodoCorriente);
		Clave nuevaClave;
		Nodo* nuevoNodoHijo = NULL;
		int posicion = obtenerPosicion(nodoInteriorCorriente, clave);
		Nodo* nodoHijo = hidratarNodo(nodoInteriorCorriente->hijos[posicion]);

		bool resultado = insertarRecursivo(nodoHijo, clave, dato, n, enteroFantasma, &nuevaClave, &nuevoNodoHijo);

		if (nuevoNodoHijo) {

			if (nodoInteriorCorriente->isOverflow(nuevaClave.getTamanio() + ARBOLBMAS_TAM_CONTROL_REGISTRO + ARBOLBMAS_TAM_CONTROL_OVERFLOW)) {

				dividirNodoInterior(nodoInteriorCorriente, clavePromocion, nuevoNodo, posicion);

				if (posicion == nodoInteriorCorriente->cantidadClaves + 1
						&& nodoInteriorCorriente->cantidadClaves < (*nuevoNodo)->cantidadClaves) {

					NodoInterior *nuevoNodoInterior = static_cast<NodoInterior*> (*nuevoNodo);
					nodoInteriorCorriente->claves[nodoInteriorCorriente->cantidadClaves] = *clavePromocion;
					nodoInteriorCorriente->hijos[nodoInteriorCorriente->cantidadClaves + 1] = nuevoNodoInterior->hijos[0];
					nodoInteriorCorriente->cantidadClaves++;
					nodoInteriorCorriente->espacioOcupado += (*clavePromocion).getTamanio() + ARBOLBMAS_TAM_CONTROL_REGISTRO;
					nuevoNodoInterior->hijos[0] = nuevoNodoHijo->numero;
					*clavePromocion = nuevaClave;

					persistirNodo(nuevoNodoHijo);
					liberarMemoriaNodo(nuevoNodoHijo);

					persistirNodo(nodoHijo);
					liberarMemoriaNodo(nodoHijo);

					return resultado;

				} else {

					if (posicion >= nodoInteriorCorriente->cantidadClaves + 1) {
						posicion -= (nodoInteriorCorriente->cantidadClaves + 1);
						nodoInteriorCorriente = static_cast<NodoInterior*> (*nuevoNodo);
					}
				}
			}

			int i = nodoInteriorCorriente->cantidadClaves;
			while (i > posicion) {
				nodoInteriorCorriente->claves[i] = nodoInteriorCorriente->claves[i - 1];
				nodoInteriorCorriente->hijos[i + 1] = nodoInteriorCorriente->hijos[i];
				i--;
			}
			nodoInteriorCorriente->claves[posicion] = nuevaClave;
			nodoInteriorCorriente->hijos[posicion + 1] = nuevoNodoHijo->numero;
			nodoInteriorCorriente->cantidadClaves++;
			nodoInteriorCorriente->espacioOcupado += nuevaClave.getTamanio() + ARBOLBMAS_TAM_CONTROL_REGISTRO;

			persistirNodo(nuevoNodoHijo);
			liberarMemoriaNodo(nuevoNodoHijo);
		}
		persistirNodo(nodoHijo);
		liberarMemoriaNodo(nodoHijo);

		return resultado;

	} else {

		NodoHoja *nodoHojaCorriente = static_cast<NodoHoja*> (nodoCorriente);

		// Saco el frontcoding antes de calcular la posicion
		sacarFrontCodingNodoHoja(&nodoHojaCorriente);
		int posicion = obtenerPosicion(nodoHojaCorriente, clave);

		// Chequeo que no exista la clave
		if (posicion <= nodoHojaCorriente->cantidadClaves && claveIgual(clave, nodoHojaCorriente->claves[posicion])) {
			refactorizarNodoFrontCoding(&nodoHojaCorriente);
			return false;
		}

		int i = nodoHojaCorriente->cantidadClaves - 1;
		while (i >= 0 && claveMenor(clave, nodoHojaCorriente->claves[i])) {
			nodoHojaCorriente->claves[i + 1] = nodoHojaCorriente->claves[i];
			nodoHojaCorriente->datos[i + 1] = nodoHojaCorriente->datos[i];
			nodoHojaCorriente->ns[i + 1] = nodoHojaCorriente->ns[i];
			nodoHojaCorriente->enterosFantasmas[i + 1] = nodoHojaCorriente->enterosFantasmas[i];
			i--;
		}

		nodoHojaCorriente->claves[i + 1] = clave;
		nodoHojaCorriente->datos[i + 1] = dato;
		nodoHojaCorriente->ns[i + 1] = n;
		nodoHojaCorriente->enterosFantasmas[i + 1] = enteroFantasma;
		nodoHojaCorriente->cantidadClaves++;

		if (nodoHojaCorriente->cantidadClaves > 1){
			refactorizarNodoFrontCoding(&nodoHojaCorriente);
		}

		nodoHojaCorriente->espacioOcupado += nodoHojaCorriente->enterosFantasmas[i + 1].getTamanio() + nodoHojaCorriente->ns[i + 1].getTamanio() + nodoHojaCorriente->datos[i + 1].getTamanio() + nodoHojaCorriente->claves[i + 1].getTamanio() + ARBOLBMAS_TAM_CONTROL_REGISTRO;

		if (nodoHojaCorriente->isOverflow(ARBOLBMAS_TAM_CONTROL_OVERFLOW)) {

			dividirNodoHoja(nodoHojaCorriente, clavePromocion, nuevoNodo);
			refactorizarNodoFrontCoding(&nodoHojaCorriente);
			refactorizarNodoNoHojaFrontCoding(&(*nuevoNodo));
			if (posicion >= nodoHojaCorriente->cantidadClaves) {
				posicion -= nodoHojaCorriente->cantidadClaves;
				nodoHojaCorriente = static_cast<NodoHoja*> (*nuevoNodo);
			}
		}
		else{
			if (nodoHojaCorriente->nivel == 0){
				refactorizarNodoFrontCoding(&nodoHojaCorriente);
			}
		}
		if (nuevoNodo && nodoHojaCorriente != *nuevoNodo && posicion == nodoHojaCorriente->cantidadClaves - 1) {
			*clavePromocion = clave;
		}

		return true;
	}
}


void ArbolBMas::dividirNodoHoja(NodoHoja* unNodoHoja, Clave* clavePromocion, Nodo** nuevoNodoHoja) {
	sacarFrontCodingNodoHoja(&unNodoHoja);
	int espacioMedio = (unNodoHoja->espacioOcupado) / 2;
	int espacioNodoIzquierdo = 0;
	int cantidadClaves = 0;
	while (cantidadClaves < unNodoHoja->cantidadClaves && espacioNodoIzquierdo < espacioMedio){

		espacioNodoIzquierdo +=  unNodoHoja->enterosFantasmas[cantidadClaves].getTamanio() + unNodoHoja->ns[cantidadClaves].getTamanio() + unNodoHoja->datos[cantidadClaves].getTamanio() + unNodoHoja->claves[cantidadClaves].getTamanio() + ARBOLBMAS_TAM_CONTROL_REGISTRO;
		cantidadClaves++;
		if (espacioNodoIzquierdo > ARBOLBMAS_TAM_EFECTIVO_NODO) {
			cantidadClaves--;
			espacioNodoIzquierdo -= (unNodoHoja->enterosFantasmas[cantidadClaves].getTamanio() + unNodoHoja->ns[cantidadClaves].getTamanio()  +  unNodoHoja->datos[cantidadClaves].getTamanio() + unNodoHoja->claves[cantidadClaves].getTamanio() + ARBOLBMAS_TAM_CONTROL_REGISTRO);
			break;
		}
	}

	NodoHoja *auxNuevoNodoHoja = crearNodoHoja();
	auxNuevoNodoHoja->numero = obtenerNumeroDeNodo();
	auxNuevoNodoHoja->cantidadClaves = unNodoHoja->cantidadClaves - cantidadClaves;
	auxNuevoNodoHoja->espacioOcupado = unNodoHoja->espacioOcupado - espacioNodoIzquierdo;
	auxNuevoNodoHoja->hojaSiguiente = unNodoHoja->hojaSiguiente;

	for (int posicion = cantidadClaves; posicion < unNodoHoja->cantidadClaves; ++posicion) {

		int auxPosicion = posicion - cantidadClaves;
		auxNuevoNodoHoja->claves[auxPosicion] = unNodoHoja->claves[posicion];
		auxNuevoNodoHoja->datos[auxPosicion] = unNodoHoja->datos[posicion];
		auxNuevoNodoHoja->ns[auxPosicion] = unNodoHoja->ns[posicion];
		auxNuevoNodoHoja->enterosFantasmas[auxPosicion] = unNodoHoja->enterosFantasmas[posicion];

	}

	unNodoHoja->espacioOcupado -= auxNuevoNodoHoja->espacioOcupado;
	unNodoHoja->cantidadClaves = cantidadClaves;
	unNodoHoja->hojaSiguiente = auxNuevoNodoHoja->numero;
	*clavePromocion = unNodoHoja->claves[unNodoHoja->cantidadClaves - 1];
	*nuevoNodoHoja = auxNuevoNodoHoja;
}


void ArbolBMas::dividirNodoInterior(NodoInterior* unNodoInterior, Clave* clavePromocion, Nodo** nuevoNodoInterior, int nuevaPosicion) {

	int medio = unNodoInterior->cantidadClaves / 2;

	if (nuevaPosicion <= medio && medio > unNodoInterior->cantidadClaves - (medio + 1)) {
		medio--;
	}

	NodoInterior *auxNuevoNodoInterior = crearNodoInterior(unNodoInterior->nivel);
	auxNuevoNodoInterior->numero = obtenerNumeroDeNodo();
	auxNuevoNodoInterior->cantidadClaves = unNodoInterior->cantidadClaves - (medio + 1);
	for (int posicion = medio + 1; posicion < unNodoInterior->cantidadClaves; ++posicion) {
		int auxPosicion = posicion - (medio + 1);
		auxNuevoNodoInterior->claves[auxPosicion] = unNodoInterior->claves[posicion];
		auxNuevoNodoInterior->hijos[auxPosicion] = unNodoInterior->hijos[posicion];
		auxNuevoNodoInterior->espacioOcupado += unNodoInterior->claves[posicion].getTamanio() + ARBOLBMAS_TAM_CONTROL_REGISTRO;
	}

	auxNuevoNodoInterior->hijos[auxNuevoNodoInterior->cantidadClaves] = unNodoInterior->hijos[unNodoInterior->cantidadClaves];
	unNodoInterior->cantidadClaves = medio;
	unNodoInterior->espacioOcupado -= auxNuevoNodoInterior->espacioOcupado;
	*clavePromocion = unNodoInterior->claves[medio];
	*nuevoNodoInterior = auxNuevoNodoInterior;
}


int ArbolBMas::pasarElementosHojaIzquierda(NodoHoja *hojaIzquierda, NodoHoja *hojaDerecha, NodoInterior *nodoPadre, int posicionPadre) {

	int tamanioMedio = (hojaDerecha->espacioOcupado - hojaIzquierda->espacioOcupado) / 2;
	int espacioDesplazado = 0;
	int cantidadClavesDesplazadas = 0;
	while (cantidadClavesDesplazadas < hojaDerecha->cantidadClaves && espacioDesplazado < tamanioMedio){

		espacioDesplazado += hojaDerecha->enterosFantasmas[cantidadClavesDesplazadas].getTamanio()
								   + hojaDerecha->ns[cantidadClavesDesplazadas].getTamanio()
								   + hojaDerecha->datos[cantidadClavesDesplazadas].getTamanio()
								   + hojaDerecha->claves[cantidadClavesDesplazadas].getTamanio()
								   + ARBOLBMAS_TAM_CONTROL_REGISTRO;
		cantidadClavesDesplazadas++;
		if (espacioDesplazado + hojaIzquierda->espacioOcupado > ARBOLBMAS_TAM_EFECTIVO_NODO) {
			cantidadClavesDesplazadas--;

			espacioDesplazado -= ( hojaDerecha->enterosFantasmas[cantidadClavesDesplazadas].getTamanio()
										   + hojaDerecha->ns[cantidadClavesDesplazadas].getTamanio()
										   + hojaDerecha->datos[cantidadClavesDesplazadas].getTamanio()
										   + hojaDerecha->claves[cantidadClavesDesplazadas].getTamanio()
										   + ARBOLBMAS_TAM_CONTROL_REGISTRO);
			break;
		}
	}

	if (cantidadClavesDesplazadas > 0) {

		for (int i = 0; i < cantidadClavesDesplazadas; i++) {
			hojaIzquierda->claves[hojaIzquierda->cantidadClaves + i] = hojaDerecha->claves[i];
			hojaIzquierda->datos[hojaIzquierda->cantidadClaves + i] = hojaDerecha->datos[i];
			hojaIzquierda->ns[hojaIzquierda->cantidadClaves + i] = hojaDerecha->ns[i];
			hojaIzquierda->enterosFantasmas[hojaIzquierda->cantidadClaves + i] = hojaDerecha->enterosFantasmas[i];
		}

		hojaIzquierda->cantidadClaves += cantidadClavesDesplazadas;
		hojaIzquierda->espacioOcupado += espacioDesplazado;
		hojaDerecha->cantidadClaves -= cantidadClavesDesplazadas;
		hojaDerecha->espacioOcupado -= espacioDesplazado;

		for (int i = 0; i < hojaDerecha->cantidadClaves; i++) {
			hojaDerecha->claves[i] = hojaDerecha->claves[i + cantidadClavesDesplazadas];
			hojaDerecha->datos[i] = hojaDerecha->datos[i + cantidadClavesDesplazadas];
			hojaDerecha->ns[i] = hojaDerecha->ns[i + cantidadClavesDesplazadas];
			hojaDerecha->enterosFantasmas[i] = hojaDerecha->enterosFantasmas[i + cantidadClavesDesplazadas];
		}
	}
	refactorizarNodoFrontCoding(&hojaDerecha);
	refactorizarNodoFrontCoding(&hojaIzquierda);
	persistirNodo(hojaIzquierda);
	persistirNodo(hojaDerecha);

	if (cantidadClavesDesplazadas > 0) {
		if (posicionPadre < nodoPadre->cantidadClaves) {
			nodoPadre->espacioOcupado -= nodoPadre->claves[posicionPadre].getTamanio();
			nodoPadre->espacioOcupado += hojaIzquierda->claves[hojaIzquierda->cantidadClaves - 1].getTamanio();
			nodoPadre->claves[posicionPadre] = hojaIzquierda->claves[hojaIzquierda->cantidadClaves - 1];
			return RESULTADO_OK;
		} else {
			ultimaClave = hojaIzquierda->claves[hojaIzquierda->cantidadClaves - 1];
			return ACTUALIZAR_ULTIMA_CLAVE;
		}
	} else {
		return RESULTADO_OK;
	}
}


void ArbolBMas::pasarElementosNodoInteriorIzquierdo(NodoInterior *nodoIzquierda, NodoInterior *nodoDerecha,	NodoInterior *nodoPadre, int posicionPadre) {

	int tamanioMedio = (nodoDerecha->espacioOcupado - nodoIzquierda->espacioOcupado) / 2;
	int espacioDesplazado = 0;
	int cantidadClavesDesplazadas = 0;
	while (cantidadClavesDesplazadas < nodoDerecha->cantidadClaves && espacioDesplazado < tamanioMedio){
		espacioDesplazado += nodoDerecha->claves[cantidadClavesDesplazadas].getTamanio()
						   + ARBOLBMAS_TAM_CONTROL_REGISTRO;
		cantidadClavesDesplazadas++;
		if (espacioDesplazado + nodoIzquierda->espacioOcupado > ARBOLBMAS_TAM_EFECTIVO_NODO) {
			cantidadClavesDesplazadas--;
			espacioDesplazado -= (nodoDerecha->claves[cantidadClavesDesplazadas].getTamanio()
							   + ARBOLBMAS_TAM_CONTROL_REGISTRO);
			break;
		}
	}

	if (cantidadClavesDesplazadas > 0) {
		espacioDesplazado = 0;

		nodoIzquierda->claves[nodoIzquierda->cantidadClaves] = nodoPadre->claves[posicionPadre];
		nodoIzquierda->cantidadClaves++;
		nodoIzquierda->espacioOcupado += nodoPadre->claves[posicionPadre].getTamanio() + ARBOLBMAS_TAM_CONTROL_REGISTRO;

		for (int i = 0; i < cantidadClavesDesplazadas - 1; i++) {
			nodoIzquierda->claves[nodoIzquierda->cantidadClaves + i] = nodoDerecha->claves[i];
			nodoIzquierda->hijos[nodoIzquierda->cantidadClaves + i] = nodoDerecha->hijos[i];
			espacioDesplazado += nodoDerecha->claves[i].getTamanio() + ARBOLBMAS_TAM_CONTROL_REGISTRO;
		}

		nodoIzquierda->cantidadClaves += cantidadClavesDesplazadas - 1;
		nodoIzquierda->espacioOcupado += espacioDesplazado;
		nodoIzquierda->hijos[nodoIzquierda->cantidadClaves] = nodoDerecha->hijos[cantidadClavesDesplazadas - 1];
		nodoPadre->espacioOcupado -= nodoPadre->claves[posicionPadre].getTamanio();
		nodoPadre->espacioOcupado += nodoDerecha->claves[cantidadClavesDesplazadas - 1].getTamanio();
		nodoPadre->claves[posicionPadre] = nodoDerecha->claves[cantidadClavesDesplazadas - 1];
		nodoDerecha->cantidadClaves -= cantidadClavesDesplazadas;
		nodoDerecha->espacioOcupado -= espacioDesplazado;
		nodoDerecha->espacioOcupado -= nodoDerecha->claves[cantidadClavesDesplazadas - 1].getTamanio();

		for (int i = 0; i < nodoDerecha->cantidadClaves; i++) {
			nodoDerecha->claves[i] = nodoDerecha->claves[i + cantidadClavesDesplazadas];
			nodoDerecha->hijos[i] = nodoDerecha->hijos[i + cantidadClavesDesplazadas];
		}
		nodoDerecha->hijos[nodoDerecha->cantidadClaves] = nodoDerecha->hijos[nodoDerecha->cantidadClaves + cantidadClavesDesplazadas];
	}
	persistirNodo(nodoIzquierda);
	persistirNodo(nodoDerecha);
}


void ArbolBMas::pasarElementosHojaDerecha(NodoHoja *hojaIzquierda, NodoHoja *hojaDerecha, NodoInterior *nodoPadre, int posicionPadre) {

	int espacioOcupadoMedio = (hojaIzquierda->espacioOcupado - hojaDerecha->espacioOcupado) / 2;
	int espacioDesplazado = 0;
	int cantidadClavesDesplazadas = 0;
	for (int i = hojaIzquierda->cantidadClaves; i > 0 && espacioDesplazado < espacioOcupadoMedio; i--) {
		espacioDesplazado +=  hojaIzquierda->enterosFantasmas[i-1].getTamanio() + hojaIzquierda->ns[i-1].getTamanio() + hojaIzquierda->datos[i-1].getTamanio() + hojaIzquierda->claves[i-1].getTamanio() + ARBOLBMAS_TAM_CONTROL_REGISTRO;
		cantidadClavesDesplazadas++;
		if (espacioDesplazado + hojaDerecha->espacioOcupado > ARBOLBMAS_TAM_EFECTIVO_NODO) {
			espacioDesplazado -= (hojaIzquierda->enterosFantasmas[i-1].getTamanio() + hojaIzquierda->ns[i-1].getTamanio() + hojaIzquierda->datos[i-1].getTamanio() + hojaIzquierda->claves[i-1].getTamanio() + ARBOLBMAS_TAM_CONTROL_REGISTRO);
			cantidadClavesDesplazadas--;
			break;
		}
	}

	if (cantidadClavesDesplazadas > 0) {

		for (int i = hojaDerecha->cantidadClaves; i >= 0; i--) {
			hojaDerecha->claves[i + cantidadClavesDesplazadas] = hojaDerecha->claves[i];
			hojaDerecha->datos[i + cantidadClavesDesplazadas] = hojaDerecha->datos[i];
			hojaDerecha->ns[i + cantidadClavesDesplazadas] = hojaDerecha->ns[i];
			hojaDerecha->enterosFantasmas[i + cantidadClavesDesplazadas] = hojaDerecha->enterosFantasmas[i];
		}

		hojaDerecha->cantidadClaves += cantidadClavesDesplazadas;
		hojaDerecha->espacioOcupado += espacioDesplazado;

		for (int i = 0; i < cantidadClavesDesplazadas; i++) {
			hojaDerecha->claves[i] = hojaIzquierda->claves[hojaIzquierda->cantidadClaves - cantidadClavesDesplazadas + i];
			hojaDerecha->datos[i] = hojaIzquierda->datos[hojaIzquierda->cantidadClaves - cantidadClavesDesplazadas + i];
			hojaDerecha->ns[i] = hojaIzquierda->ns[hojaIzquierda->cantidadClaves - cantidadClavesDesplazadas + i];
			hojaDerecha->enterosFantasmas[i] = hojaIzquierda->enterosFantasmas[hojaIzquierda->cantidadClaves - cantidadClavesDesplazadas + i];
		}

		hojaIzquierda->cantidadClaves -= cantidadClavesDesplazadas;
		hojaIzquierda->espacioOcupado -= espacioDesplazado;
		nodoPadre->espacioOcupado -= nodoPadre->claves[posicionPadre].getTamanio();
		nodoPadre->espacioOcupado += hojaIzquierda->claves[hojaIzquierda->cantidadClaves - 1].getTamanio();
		nodoPadre->claves[posicionPadre] = hojaIzquierda->claves[hojaIzquierda->cantidadClaves - 1];
	}
	refactorizarNodoFrontCoding(&hojaDerecha);
	refactorizarNodoFrontCoding(&hojaIzquierda);
	persistirNodo(hojaIzquierda);
	persistirNodo(hojaDerecha);
}


void ArbolBMas::pasarElementosNodoInteriorDerecho(NodoInterior *nodoIzquierda, NodoInterior *nodoDerecha, NodoInterior *nodoPadre, int posicionPadre) {

	int espacioOcupadoMedio = (nodoIzquierda->espacioOcupado - nodoDerecha->espacioOcupado) / 2;
	int espacioDesplazado = 0;
	int cantidadClavesDesplazadas = 0;
	for (int i = nodoIzquierda->cantidadClaves; i > 0 && espacioDesplazado < espacioOcupadoMedio; i--) {
		espacioDesplazado += nodoIzquierda->claves[i-1].getTamanio() + ARBOLBMAS_TAM_CONTROL_REGISTRO;
		cantidadClavesDesplazadas++;
		if (espacioDesplazado + nodoDerecha->espacioOcupado > ARBOLBMAS_TAM_EFECTIVO_NODO) {
			espacioDesplazado -= (nodoIzquierda->claves[i-1].getTamanio() + ARBOLBMAS_TAM_CONTROL_REGISTRO);
			cantidadClavesDesplazadas--;
			break;
		}
	}

	if (cantidadClavesDesplazadas > 0) {
		espacioDesplazado = 0;

		nodoDerecha->hijos[nodoDerecha->cantidadClaves + cantidadClavesDesplazadas] = nodoDerecha->hijos[nodoDerecha->cantidadClaves];

		for (int i = nodoDerecha->cantidadClaves - 1; i >= 0; i--) {
			nodoDerecha->claves[i + cantidadClavesDesplazadas] = nodoDerecha->claves[i];
			nodoDerecha->hijos[i + cantidadClavesDesplazadas] = nodoDerecha->hijos[i];
		}

		nodoDerecha->cantidadClaves += cantidadClavesDesplazadas;
		nodoDerecha->claves[cantidadClavesDesplazadas - 1] = nodoPadre->claves[posicionPadre];
		nodoDerecha->hijos[cantidadClavesDesplazadas - 1] = nodoIzquierda->hijos[nodoIzquierda->cantidadClaves];
		nodoDerecha->espacioOcupado += nodoPadre->claves[posicionPadre].getTamanio()+ ARBOLBMAS_TAM_CONTROL_REGISTRO;

		for (int i = 0; i < cantidadClavesDesplazadas - 1; i++) {
			nodoDerecha->claves[i] = nodoIzquierda->claves[nodoIzquierda->cantidadClaves - cantidadClavesDesplazadas + i + 1];
			nodoDerecha->hijos[i] = nodoIzquierda->hijos[nodoIzquierda->cantidadClaves - cantidadClavesDesplazadas + i + 1];
			espacioDesplazado += nodoDerecha->claves[i].getTamanio() + ARBOLBMAS_TAM_CONTROL_REGISTRO;
		}
		nodoDerecha->espacioOcupado += espacioDesplazado;

		nodoPadre->espacioOcupado -= nodoPadre->claves[posicionPadre].getTamanio();
		nodoPadre->espacioOcupado += nodoIzquierda->claves[nodoIzquierda->cantidadClaves - cantidadClavesDesplazadas].getTamanio();
		nodoPadre->claves[posicionPadre] = nodoIzquierda->claves[nodoIzquierda->cantidadClaves - cantidadClavesDesplazadas];
		nodoIzquierda->cantidadClaves -= cantidadClavesDesplazadas;
		nodoIzquierda->espacioOcupado -= espacioDesplazado;
		nodoIzquierda->espacioOcupado -= (nodoIzquierda->claves[nodoIzquierda->cantidadClaves - cantidadClavesDesplazadas].getTamanio());
	}
	persistirNodo(nodoIzquierda);
	persistirNodo(nodoDerecha);
}

void ArbolBMas::persistirNodo(Nodo* unNodo) {
	persistor->guardarBloque(unNodo->numero, unNodo->Serializar());
}


Nodo* ArbolBMas::hidratarNodo(int numeroDeNodo) {

	Persistencia cadena = this->persistor->leerBloque(numeroDeNodo);
	if (cadena.estaVacia()) {
		return NULL;
	} else {
		int nivel = cadena.leerEntero(0);
		if (nivel == 0) {
			NodoHoja *nuevoNodoHoja = crearNodoHoja();
			nuevoNodoHoja->Hidratar(cadena);
			nuevoNodoHoja->numero = numeroDeNodo;
			return nuevoNodoHoja;
		} else {
			NodoInterior *nuevoNodoInterior = crearNodoInterior(nivel);
			nuevoNodoInterior->Hidratar(cadena);
			nuevoNodoInterior->numero = numeroDeNodo;
			return nuevoNodoInterior;
		}
	}
}


int ArbolBMas::obtenerNumeroDeNodo() {
	int numeroDeNodo;
	if (nodosLibres.empty()) {
		this->cantidadNodos++;
		numeroDeNodo = this->cantidadNodos-1;
	} else {
		numeroDeNodo = nodosLibres.back();
		nodosLibres.pop_back();
		persistirDatosConfiguracion();
	}
	return numeroDeNodo;
}


void ArbolBMas::persistirDatosConfiguracion() {
	vector<int>::iterator it = nodosLibres.begin();
	string nombreArchivo = persistor->getRuta() + "_Configuracion.txt";
	ofstream ofs(nombreArchivo.c_str());

	if (!ofs.fail()) {

		ofs.write((char*)(&primeraHoja),sizeof(int));

		while (it != nodosLibres.end()) {
			int numeroDeNodo = *it;
			ofs.write((char*)(&numeroDeNodo),sizeof(int));
			it++;
		}
	}
	ofs.close();
}


void ArbolBMas::hidratarDatosConfiguracion() {

	nodosLibres.clear();
	string nombreArchivo = persistor->getRuta() + "_Configuracion.txt";
	fstream ifs(nombreArchivo.c_str());

	if (ifs.is_open()) {

		ifs.seekg(0, ios_base::end);
		int tamanio = ifs.tellg();
		ifs.seekg(0, ios_base::beg);


	if (tamanio != 0){
		char* sPrimeraHoja = new char[sizeof(int)];
		ifs.read(sPrimeraHoja,sizeof(int));
		primeraHoja = *((int*)sPrimeraHoja);
		delete[] sPrimeraHoja;

			while (ifs.tellg() < tamanio) {
				char* s = new char[sizeof(int)];
				ifs.read(s,sizeof(int));
				int numeroDeNodo = *((int*)s);
				nodosLibres.push_back(numeroDeNodo);
				delete[] s;
		}
	}
		ifs.close();
	}else{
		ifs.open(nombreArchivo.c_str(), ios_base::out);
		ifs.close();

	}
}

void ArbolBMas::buscar(list<Elementos*>* listaElementos, Clave* clave){

	Nodo *unNodo = raiz;
	if (unNodo){

		while (!unNodo->isNodoHoja()) {
			NodoInterior *unNodoInterior = static_cast<NodoInterior*> (unNodo);
			int posicion = obtenerPosicion(unNodoInterior, *(clave));
			unNodo = hidratarNodo(unNodoInterior->hijos[posicion]);
			if (unNodoInterior != raiz)
				liberarMemoriaNodo(unNodoInterior);
		}

		NodoHoja *unNodoHoja = static_cast<NodoHoja*> (unNodo);
		int posicion = obtenerPosicion(unNodoHoja, *(clave));

		llenarListadeBusqueda(listaElementos, unNodoHoja, posicion, clave);
	}

}

Elementos* ArbolBMas::buscar(Clave* clave){

	Nodo *unNodo = raiz;
	if (unNodo){

		while (!unNodo->isNodoHoja()) {
			NodoInterior *unNodoInterior = static_cast<NodoInterior*> (unNodo);
			int posicion = obtenerPosicion(unNodoInterior, *(clave));
			unNodo = hidratarNodo(unNodoInterior->hijos[posicion]);
			if (unNodoInterior != raiz)
				liberarMemoriaNodo(unNodoInterior);
		}

		NodoHoja *unNodoHoja = static_cast<NodoHoja*> (unNodo);
		int posicion = obtenerPosicion(unNodoHoja, *(clave));

		this->sacarFrontCodingNodoHoja(&unNodoHoja);
		for (int i = posicion; (i < unNodoHoja->cantidadClaves); ++i){
			if (unNodoHoja->claves[i].getClave() == clave->getClave() || unNodoHoja->claves[i].getClave() >= clave->getClave()){
				Clave* unaClave = new Clave(unNodoHoja->claves[i]);
				Elementos* elemento = new Elementos(unaClave, new Persistencia(unNodoHoja->datos[i].toString()), new Persistencia(unNodoHoja->ns[i].toString()), new Persistencia(unNodoHoja->enterosFantasmas[i].toString()));
				return elemento;
			}
		}
	}
	return NULL;

}


void ArbolBMas::llenarListadeBusqueda(list<Elementos*>* listaElementos, NodoHoja* nodo, int posicion, Clave* clave){
	bool distinto = false;
	this->sacarFrontCodingNodoHoja(&nodo);
	for (int i = posicion; (i < nodo->cantidadClaves) && (!distinto); ++i){
		if (nodo->claves[i].getClave() == clave->getClave()){
			Clave unaClave = nodo->claves[i];
			Elementos* elemento = new Elementos(clave, new Persistencia(nodo->datos[i].toString()), new Persistencia(nodo->ns[i].toString()), new Persistencia(nodo->enterosFantasmas[i].toString()));
			listaElementos->push_back(elemento);
		}else{
			distinto = true;
		}
	}
	if(!distinto && nodo->hojaSiguiente != 0){
		Nodo * nuevoNodo = hidratarNodo(nodo->hojaSiguiente);
		NodoHoja* nuevoNodoHoja = static_cast<NodoHoja*> (nuevoNodo);
		refactorizarNodoFrontCoding(&nodo);
		llenarListadeBusqueda(listaElementos, nuevoNodoHoja, 0 , clave);
	}
}


//Carga inicial
void ArbolBMas::cargaInicial(int cantRegistros) {

	ifstream archivoAcargar;
	tRegistroDiccionario *bufferLectura = new tRegistroDiccionario[TAM_BUFFER_LEC];
	Elementos *elementos = new Elementos[TAM_BUFFER_LEC];
	int posicion = 0;
	//int numero = 0;

	archivoAcargar.open(PATH_ALEATORIO, ios::in | ios::binary);

	if ((elementos) && (bufferLectura)) {

		archivoAcargar.read((char*)bufferLectura,(sizeof(tRegistroDiccionario)*TAM_BUFFER_LEC));

		this->generarClaves(bufferLectura,elementos,TAM_BUFFER_LEC, &posicion);
		cantRegistros = cantRegistros - TAM_BUFFER_LEC;

		while (cantRegistros >= TAM_BUFFER_LEC) {

			for (int i = 0; i < TAM_BUFFER_LEC; i++) {

				this->insertar(&elementos[i]);
			}

			archivoAcargar.read((char*)bufferLectura,(sizeof(tRegistroDiccionario)*TAM_BUFFER_LEC));

			this->generarClaves(bufferLectura,elementos,TAM_BUFFER_LEC, &posicion);
			cantRegistros = cantRegistros - TAM_BUFFER_LEC;
		}

		for (int i = 0; i < TAM_BUFFER_LEC; i++) {

			this->insertar(&elementos[i]);
		}

		if (cantRegistros != 0) {

			archivoAcargar.read((char*)bufferLectura,(sizeof(tRegistroDiccionario)*cantRegistros));

			this->generarClaves(bufferLectura,elementos,TAM_BUFFER_LEC, &posicion);

			for (int i = 0; i < cantRegistros; i++) {

				this->insertar(&elementos[i]);
			}
		}
	}
	else {
		cout << "No se pudo abrir el archivo aleatorizado o no hay espacio en memoria";
	}

	delete []bufferLectura;
	delete []elementos;
}

void ArbolBMas::generarClaves(tRegistroDiccionario *buffer, Elementos *elementos, int cant, int *pos) {

	for (int i = 0; i < cant; i++) {


		string auxiliar = buffer[i].termino;
		Clave *clave = new Clave(auxiliar);

		Persistencia *termino = new Persistencia(auxiliar);
		Persistencia *posicion = new Persistencia(IntToStr(*pos));
		Persistencia *fantasma = new Persistencia("0");
		Elementos *elemento = new Elementos(clave,termino,posicion,fantasma);

		elementos[i] = *elemento;
		(*pos)++;
	}
}

string ArbolBMas::IntToStr(int n) {

	stringstream result;
	result << n;
	return result.str();
}

