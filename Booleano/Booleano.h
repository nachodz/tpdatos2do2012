/*
 * Booleano.h
 *
 *  Created on: 19/11/2012
 *      Author: ignacio
 */

#ifndef BOOLEANO_H_
#define BOOLEANO_H_

//#define CANTIDAD_DE_FRASES_A_CARGAR 60

#define TAMANIO_BLOQUE_LISTAS_INV 128
#define TAMANIO_REGISTRO_FRASES 256
#define CANT_STOPW 500
#define UMBRAL 26
#define PATH_ARCHIVO_FRASES "Frases celebres.dat"
#define PATH_STOPWORDS "stopwords.txt"
#define PATH_ARCHIVO_TERMINOS "archivo_T.dat"
#define PATH_ARCHIVO_OCURRENCIAS "archivo_Ocurrencias.dat"
#define PATH_ARCHIVO_OCURRENCIAS_ORD "particion0"
#define PATH_ARCHIVO_INVERTIDAS "ls_invertidas.dat"
#define PATH_ARCHIVO_BUSQUEDA "resultadoBusqueda.txt"

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <algorithm>
#include <list>

#include "mapaBits.h"
#include "Normalizador.h"

#include "ArbolBMas/ArbolBMas.h"
#include "ArbolBMas/Elementos.h"
#include "ArbolBMas/Clave.h"
#include "Persistencia/Persistencia.h"
#include "Gamma/CodigoGamma.h"
#include "Ordenador/Ordenador.h"

struct RegOcurrencia {
	int idTer;
	int idDoc;
}__attribute__((packed));

using namespace std;


class Booleano {
private:
	int cant_stopWords;
	string *listaStopWords;



public:
	Booleano();

	virtual ~Booleano();

	void armarIndice();

	void cargar_ls_bloques ();

	void cargar_stops();

	bool compararTermino (string term);

	void terminoEncontrado(string palabraStr,int *id, bool *encontrado);

	void agregar_a_archivoT (string palabra, int *offset);

	void agregar_a_Arbol (int idT,int pos_Arch, ArbolBMas *arbol, bool modificar);

	int cant_registros_ocurrencias ();

	void cargar_listasInvertidas ();

	bool agregar_arch_invertidas (list<int> inver,int cantDoc, int idT,int *pos, fstream *invertidas);

	void ordenarSort ();

	string obtenerTermino (int idT);

	bool obtenerListaIdT (string termino,list <int> *listaDocs,int *nroBloque);

	bool buscarEnBloque (int id,int nroBloque,string *listaDevuelto, int *offsetEnBloque);

	Elementos* buscarEnArbol (string palabra, ArbolBMas *arbol,bool *result);

	void agregarDocALista (int nroDoc, int idT, int numBlok);

	void agregar_frase (string frase, int nroDoc);

	void agregarNuevaListaInvertidas(int id, int nroDoc, int *pos);

	bool actualizar_bloqueLista (string listNueva, int tam_listVieja,int numBloq, int offsetEnBloke,bool alta);

	void alta (string termino,int nroDoc);

	void baja (string terminoBaja, int nroDocBaja);

	void quitarDocLista (int DocBaja,int idBaja, int bloqueLs, bool *vacio);

	void eliminarListaInvertida (int nBloq, int offsetEnBloq, unsigned int listaSize);

	void quitar_termino_Arbol (string termino, int idT, ArbolBMas* arbol);

	bool buscarEnListaDocs (list <int> listaDoc, int nroDc);

	void buscarListaTerminos (string *listaTerminos, int cantTerm);

	void mostrarEnTxt (list <int> listaDocs, int cantTerm, string *listaTerminos,float t);

	void quitar_frase (string frase, int nroDoc);
};



#endif /* BOOLEANO_H_ */
