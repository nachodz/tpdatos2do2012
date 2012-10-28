
#ifndef _ARBOLBMAS_H_
#define _ARBOLBMAS_H_

#include "Elementos.h"
#include "NodoInterior.h"
#include "../Persistencia/PersistorArbol.h"
#include "Solucion.h"
#include <fstream>
#include <vector>
#include <list>

using namespace std;

struct tRegistroDiccionario {
	int ID;
	char termino[25];
}__attribute__((packed));


class ArbolBMas {

	friend class Nodo;
	friend class NodoInterior;
	friend class NodoHoja;

private:
	Nodo* raiz;
	int primeraHoja;
	int cantidadNodos;
	vector<int> nodosLibres;
	PersistorArbol* persistor;

	Clave ultimaClave;
	enum enumReturn {RESULTADO_OK = 0, NO_ENCONTRADO = 1, ACTUALIZAR_ULTIMA_CLAVE = 2, FUSION = 4} flags;

public:

	ArbolBMas(string ruta_archivo);

	~ArbolBMas();

	int insertar(Elementos* registro);

	bool modificar(Elementos* registro);

	void cargaInicial(int cantRegistros);

	void generarClaves(tRegistroDiccionario *buffer, Elementos *claves, int cant, int *pos);

	string IntToStr(int numero);

	bool borrar(Elementos* elemento);

	void mostrar();

	void mostrarTodosTerminos();

	Nodo* leerNodo(int numeroDeNodo);

	int getCantidadBloques();

	void buscar(list<Elementos*>* listaElementos, Clave* clave);
	//TODO: sacar! el que va es este!!
	Elementos* buscar(Clave* clave);


private:

	void llenarListadeBusqueda(list<Elementos*>* listaElementos, NodoHoja* nodo, int posicion, Clave* clave);

	bool claveMenor(Clave clave1, Clave clave2);

	bool claveMenorIgual(Clave clave1, Clave clave2);

	bool claveIgual(Clave clave1, Clave clave2);

	NodoHoja* crearNodoHoja();

	NodoInterior* crearNodoInterior(int nivel);

	void liberarMemoriaNodo(Nodo *unNodo);

	int obtenerPosicion(Nodo *unNodo, Clave clave);

	bool insertarRecursivo(Nodo* nodoCorriente, Clave clave, Persistencia dato, Persistencia n, Persistencia enteroFantasma,  Clave* clavePromocion, Nodo** nuevoNodo);

	void dividirNodoHoja(NodoHoja* unNodoHoja, Clave* clavePromocion, Nodo** nuevoNodoHoja);

	void dividirNodoInterior(NodoInterior* unNodoInterior, Clave* clavePromocion, Nodo** nuevoNodoInterior, int nuevaPosicion);

	int borrarRecursivo(Elementos* elem, Clave clave, Nodo *nodoCorriente, Nodo *nodoIzquierda, Nodo *nodoDerecha,
			NodoInterior *nodoPadreIzquierda, NodoInterior *nodoPadreDerecha, NodoInterior *nodoPadre, int posicionPadre);

	int fusionarHojas(NodoHoja* hojaIzquierda, NodoHoja* hojaDerecha);

	int fusionarNodosInteriores(NodoInterior* nodoIzquierda, NodoInterior* nodoDerecha, NodoInterior* nodoPadre, int posicionPadre);

	int pasarElementosHojaIzquierda(NodoHoja *hojaIzquierda, NodoHoja *hojaDerecha, NodoInterior *nodoPadre, int posicionPadre);

	void pasarElementosNodoInteriorIzquierdo(NodoInterior *nodoIzquierda, NodoInterior *nodoDerecha, NodoInterior *nodoPadre, int posicionPadre);

	void pasarElementosHojaDerecha(NodoHoja *hojaIzquierda, NodoHoja *hojaDerecha, NodoInterior *nodoPadre, int posicionPadre);

	void pasarElementosNodoInteriorDerecho(NodoInterior *nodoIzquierda, NodoInterior *nodoDerecha, NodoInterior *nodoPadre, int posicionPadre);

	void persistirNodo(Nodo* unNodo);

	Nodo* hidratarNodo(int numeroDeNodo);

	int obtenerNumeroDeNodo();

	void persistirDatosConfiguracion();

	void hidratarDatosConfiguracion();

	void toString(Nodo* nodoAmostrar, int tab, ofstream& fo);

	void refactorizarNodoFrontCoding(NodoHoja** nodoHojaCorriente);

	void refactorizarNodoNoHojaFrontCoding(Nodo** nodo);

	void sacarFrontCodingNodo (Nodo ** nodo);

	void sacarFrontCodingNodoHoja (NodoHoja ** nodo);

	Solucion buscarSecuencialClave(int nodo, Elementos* elemento, int posicion);

	Persistencia obtenerNuevoId(string path);

	NodoHoja* obtenerPrimeraHoja();

};

#endif // _ARBOLBMAS_H_
