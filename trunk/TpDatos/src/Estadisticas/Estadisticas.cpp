/*
 * Estadisticas.cpp
 *
 *  Created on: 13/10/2012
 *      Author: nachodz
 */

#include "Estadisticas.h"
bool myfunction (pair<string, int> x, pair<string, int> y) { return x.second > y.second; }

Estadisticas::Estadisticas() {
	this->cant_frases = 0;
    this->term_total_frases = 0;
    this->term_no_encontrados = 0;
    this->term_encontrados = 0;
    this->cant_stopWords = 0;
    this->cargar_stops();

}


Estadisticas::~Estadisticas() {
	delete []listaStopWords;
}

void Estadisticas::cargar_stops (){

	this->listaStopWords = new string [CANT_STOPW];

	ifstream stopw (PATH_STOPWORDS);

    int i = 0;

    if (stopw) {

    	stopw >> this->listaStopWords[i];
    	i++;
    	while ( !stopw.eof() ) {
    		stopw >> this->listaStopWords[i];
    		i++;
    	}
    	this->cant_stopWords = i;

    }else cout << "No se pudo abrir archivo Stop Words" << endl;
}


bool Estadisticas::compararTermino (string term){
	bool result = false;
	int i = 0;
	while ((i < this->cant_stopWords) && (!result) ){
		result = (this->listaStopWords[i] == term);
		i++;
	}
	return result;
}


void Estadisticas::agregar_term_no_encontrados(string palabra){

	ofstream arch (PATH_TERM_NO_ENCONTRADOS,ios::app);

	if ((arch))
		arch << palabra << endl;
	else
		cout << "el termino no encotnrado "<< palabra <<" no se agrego al archivo " << PATH_TERM_NO_ENCONTRADOS << endl;

	arch.close();
}

void Estadisticas::procesar_frase (string frase,ArbolBMas* arbol) {

	Normalizador normalizar;
	Elementos* unElemento;
	char *palabra;
	string palabraStr;

	this->cant_frases ++;
    char *fraseProcesar = strdup (frase.c_str());
    palabra = strtok (fraseProcesar," .,;:¿?_-<>/¡!");

	while (palabra != NULL) {

		palabraStr = string (palabra);
	    normalizar.normalizarPalabra(&palabraStr);
        bool esStop = this->compararTermino (palabraStr);

	    if (!esStop) {
	    	this->term_total_frases ++;

     	    Clave* unaClave = new Clave(palabraStr);

		    ++this->ranking[unaClave->getClave()];

		    unElemento = arbol->buscar(unaClave);

		    if ((unElemento->getClave()->getClave()) == (unaClave->getClave())){
			     this->term_encontrados++;
		  }
		    else {
			     this->agregar_term_no_encontrados(unaClave->getClave());
			     this->term_no_encontrados++;
			     }
		  delete unaClave;
	  }
    palabra = strtok (NULL," .,;:?_-</>");
 }

}

int Estadisticas::terminos_prom_frase () {
    return (this->term_total_frases/this->cant_frases);
}

int Estadisticas::tasa_fallo_terminos () {
    return (this->term_no_encontrados/this->term_total_frases);   //no se si es "term_no_encontrados" o "term_encontrados", estan los dos,
                                                                  // hay que cambiarlo ahi nomas y listo.
}

void Estadisticas::listar_ranking (int n) {

	vector < pair<string,int> > vec (this->ranking.begin(),this->ranking.end());  //guardo todos los pares (string,int) del mapa en el vector

	if (n > (int)vec.size()) {
		cout << "Hay menos elementos para mostrar" << endl;
        n = (int)vec.size();
	}
	sort (vec.begin(),vec.end(),myfunction);   //ordeno el vector por cant de palabras.
	for (int i = 0; i < n; i++)
		cout << vec[i].first << ": "<< vec[i].second << " veces" << endl; //lo muestro.

}

//void Estadisticas::mostrar_stopWords () {
//
//	cout << this->cant_stopWords << endl;
//
//	for (int i = 0; i <= this->cant_stopWords; i++)		cout << this->listaStopWords[i] << endl;
//
//
//
//}
