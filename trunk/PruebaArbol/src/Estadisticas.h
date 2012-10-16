/*
 * Estadisticas.h
 *
 *  Created on: 13/10/2012
 *      Author: nachodz
 */

#ifndef ESTADISTICAS_H_
#define ESTADISTICAS_H_

#define CANT_STOPW 500
#define PATH_TERM_NO_ENCONTRADOS "TerminosNoEncontrados.txt"

#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <memory.h>
#include <sstream>
#include <map>
#include <iterator>
#include <vector>
#include <algorithm>

#include "ArbolBMas.h"
#include "Normalizador.h"


using namespace std;


class Estadisticas {

private:
	int term_total_frases;
	int cant_frases;
	int term_no_encontrados;
	int term_encontrados;
	int cant_stopWords;

	map <string,int> ranking;
	string *listaStopWords;



public:
	Estadisticas();
	virtual ~Estadisticas();
	void procesar_frase (string frase,ArbolBMas* arbol);
	void cargar_stops();
	bool compararTermino (string term);
	void agregar_term_no_encontrados(string palabra);
	int terminos_prom_frase ();
	int tasa_fallo_terminos ();
	void listar_ranking (int n);
	//	void mostrar_stopWords ();
};

#endif /* ESTADISTICAS_H_ */
