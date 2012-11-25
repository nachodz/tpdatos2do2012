/*
 * Booleano.cpp
 *
 *  Created on: 19/11/2012
 *      Author: ignacio
 */

#include "Booleano.h"

Booleano::Booleano() {
	this->cant_stopWords = 0;
	this->cargar_stops();
    this->cargar_ls_bloques ();
}

Booleano::~Booleano() {
	delete []listaStopWords;
}

void Booleano::cargar_ls_bloques (){

	for ( int i = 0; i < TAMANIO_BLOQUE_LISTAS_INV; i++){
		this->tam_libre [i] = TAMANIO_BLOQUE_LISTAS_INV;
	}
}

void Booleano::armarIndice (){

    int idT;
	int nroDoc = 1;
	RegOcurrencia reg;
	Normalizador normalizar;
	Elementos* Elemento;
	ArbolBMas* arbol = new ArbolBMas(PATH_ARBOL);           // Arbol que voy a ir cargando con las palabras no encontradas.
	mapaBits *mapa = new mapaBits(TAMANIO_REGISTRO_FRASES); // creo el mapa de bits para el archivo.
	char *serial = new char[TAMANIO_REGISTRO_FRASES];       // con Serial lo voy a hidratar en mapa.
	char *doc  = new char[TAMANIO_REGISTRO_FRASES];                     // con Doc voy a ir leyendo los registros.

	ifstream arch_frases (PATH_ARCHIVO_FRASES,ios::binary | ios::in);  // archivo de Frases celebres.dat
	ofstream archivoT (PATH_ARCHIVO_TERMINOS,ios::binary | ios::out);;  //archivo de terminos por orden de aparicion.
	ofstream archivoOcur (PATH_ARCHIVO_OCURRENCIAS,ios::binary | ios::out);  //archivo de terminos por orden de aparicion en documentos.
	arch_frases.read(serial,TAMANIO_REGISTRO_FRASES);         // leo el mapa

	mapa->hidratar(serial);		                              // lo hidrato
	arch_frases.read(doc,TAMANIO_REGISTRO_FRASES);

	while (!arch_frases.eof()){                               // proceso el archivo de frases.dat hasta que se acaben las frases

    	if (!mapa->libre(nroDoc)) {                          // antes de leer un registro chequeo que este ocupado

//    		arch_frases.seekg(nroDoc*TAMANIO_REGISTRO_FRASES,ios::beg);
//    		arch_frases.read(doc,TAMANIO_REGISTRO_FRASES);                                           // y leo

            char *palabra = strtok (doc," .,;:¿?_-<>/!	");

            while (palabra != NULL) {

            string palabraStr = string (palabra);
//  cout << palabraStr << " su tamaño es: " << palabraStr.size() << endl;      //ANTES DE NORMALIZAR
       	    normalizar.normalizarPalabra(&palabraStr);                      // normalizo la palabra. VER ESTA PARTE!!!
//  cout << palabraStr << endl;                                              //DESPUES DE NORMALIZAR
            bool esStop = this->compararTermino (palabraStr);              // me fijo si es StopWord
      	      if (!esStop) {                                              // si no es Stop Word
      	    	bool encontrado;

      	    	  Elemento = this->terminoEncontrado(palabraStr,arbol,&encontrado);

      	         if (encontrado)    										// me fijo si esta en el Arbol o no.
      	          idT = atoi (Elemento->getN()->toString().c_str());          // si esta en el Arbol, obtengo su ID del Elemento de Arbol.

      	            else{
      	              this->agregar_a_archivoT(palabraStr,&archivoT,&idT);  // sino lo agrego al "Archivo de ocurrencias"
                      this->agregar_a_Arbol (palabraStr,arbol,idT);         // y luego al Arbol como (termino, idT, 0)
      	                }

      	       reg.idDoc = nroDoc;
      	       reg.idTer = idT;
      	       archivoOcur.write((char*)&reg,sizeof(reg));                  // y luego al "Archivo de ocurrencia de terminos en docs"

      	       }

      	       palabra = strtok (NULL," .,;:¿?_-<>/!	");
      	     }
           }
    	nroDoc++;
    	arch_frases.read(doc,TAMANIO_REGISTRO_FRASES);
    }

     arch_frases.close();
     archivoT.close();
     archivoOcur.close();
     delete []doc;
     delete []serial;
     delete Elemento;
     delete arbol;
     delete mapa;

//     this->cargar_listasInvertidas();
}

void Booleano::cargar_listasInvertidas (){

	ifstream arch_ocur_ord (PATH_ARCHIVO_OCURRENCIAS_ORD, ios::binary);
	ofstream arch_ls_invertidas (PATH_ARCHIVO_INVERTIDAS,ios::binary);

	list<int> listaInver;
    int cantDocs = 0;
    int pos = 0;

	RegOcurrencia reg;
	arch_ocur_ord.read((char*)&reg,sizeof(reg));

    int idTerAux = reg.idTer;

	while (!arch_ocur_ord.eof()) {

		while (reg.idTer == idTerAux) {
			listaInver.push_back(reg.idDoc);
			cantDocs++;
		}
		listaInver.push_front(cantDocs);
		this->agregar_arch_invertidas (listaInver,cantDocs,reg.idTer,&pos);
		listaInver.clear();
		cantDocs = 0;
	}



}

void Booleano::agregar_arch_invertidas (list<int> inver,int cantDoc, int idT, int *pos){

	CodigoGamma gamma;

	string ls_Comprimida = gamma.comprimirLista(inver,cantDoc);

    unsigned short int id = idT;

	unsigned char ls_long = ls_Comprimida.size();

	this->tam_libre [*pos] = TAMANIO_BLOQUE_LISTAS_INV - ls_long - sizeof (id) - sizeof (ls_long);

    // En proceso...


}

void Booleano::agregar_a_archivoT (string palabra, ofstream *archT, int *offset){

	char long_term = palabra.size();
	archT->seekp(0,ios::end);
	*offset = archT->tellp();

	archT->write(&long_term,sizeof(long_term));
	archT->write((char*)palabra.c_str(),long_term);

//	cout << (int)long_term << " longitud de: " << palabra << endl;
//	cout << *offset << " offset de: " << palabra << endl;
}

void Booleano::agregar_a_Arbol (string palabra, ArbolBMas *arbol,int idT){

	Clave *clave = new Clave(palabra);
	Persistencia *termino = new Persistencia(palabra);
	Persistencia *posicion = new Persistencia(arbol->IntToStr(idT));
	Persistencia *fantasma = new Persistencia("0");

	cout << atoi (posicion->toString().c_str()) << endl;

	Elementos *elem = new Elementos(clave,termino,posicion,fantasma);



    arbol->insertar(elem);

    delete elem;
}

Elementos* Booleano::terminoEncontrado (string palabra, ArbolBMas *arbol,bool * result){
	 Elementos* unElemento;
	 Clave* unaClave = new Clave(palabra);
	 unElemento = arbol->buscar(unaClave);
	 *result = ((unElemento != NULL) && (unElemento->getClave()->getClave()) == (unaClave->getClave()));

	 return unElemento;
}

void Booleano::cargar_stops (){

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

bool Booleano::compararTermino (string term){
	bool result = false;
	int i = 0;
	while ((i < this->cant_stopWords) && (!result) ){
		result = (this->listaStopWords[i] == term);
		i++;
	}
	return result;
}
int Booleano::cant_registros_ocurrencias (){
	  int begin,end;
	  ifstream archivoOcur (PATH_ARCHIVO_OCURRENCIAS,ios::binary | ios::in);
	  begin = archivoOcur.tellg();
	  archivoOcur.seekg (0, ios::end);
	  end = archivoOcur.tellg();
	  archivoOcur.close();
	  int cant = (end-begin);

	  return cant/sizeof (RegOcurrencia);
}

