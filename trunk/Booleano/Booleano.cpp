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
	delete [](this->listaStopWords);
	delete [](this->tam_libre);
}

void Booleano::cargar_ls_bloques (){
	this->tam_libre = new unsigned char[TAMANIO_BLOQUE_LISTAS_INV];

	for ( int i = 0; i < TAMANIO_BLOQUE_LISTAS_INV; i++){
		this->tam_libre[i] = TAMANIO_BLOQUE_LISTAS_INV;
	}
	ofstream invertidas (PATH_ARCHIVO_INVERTIDAS,ios::binary);
	invertidas.write((char*)this->tam_libre,TAMANIO_BLOQUE_LISTAS_INV);
	invertidas.close();

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

void Booleano::armarIndice (){

    int idT;
	int nroDoc = 1;
	RegOcurrencia reg;
	Normalizador normalizar;
	mapaBits *mapa = new mapaBits(TAMANIO_REGISTRO_FRASES); // creo el mapa de bits para el archivo.
	char *serial = new char[TAMANIO_REGISTRO_FRASES];       // con Serial lo voy a hidratar en mapa.
	char *doc  = new char[TAMANIO_REGISTRO_FRASES];         // con Doc voy a ir leyendo los registros.

	ifstream arch_frases (PATH_ARCHIVO_FRASES,ios::binary | ios::in);  // archivo de Frases celebres.dat
	ofstream archivoOcur (PATH_ARCHIVO_OCURRENCIAS,ios::binary | ios::out);  //archivo de terminos por orden de aparicion en documentos.
	arch_frases.read(serial,TAMANIO_REGISTRO_FRASES);         // leo el mapa

	mapa->hidratar(serial);		                              // lo hidrato
	arch_frases.read(doc,TAMANIO_REGISTRO_FRASES);

	while (!arch_frases.eof()){                               // proceso el archivo de frases.dat hasta que se acaben las frases

    	if (!mapa->libre(nroDoc)) {                          // antes de leer un registro chequeo que este ocupado

            char *palabra = strtok (doc," .,;:¿?_-<>/!	");

            while (palabra != NULL) {

            string palabraStr = string (palabra);
       	    normalizar.normalizarPalabra(&palabraStr);                      // normalizo la palabra. VER ESTA PARTE!!!

       	    bool esStop = this->compararTermino (palabraStr);              // me fijo si es StopWord

            if (!esStop) {                                              // si no es Stop Word

             bool encontrado;

             this->terminoEncontrado(palabraStr,&idT,&encontrado);

   	    	 if (!encontrado)
   	    	   this->agregar_a_archivoT(palabraStr,&idT);  // sino lo agrego al "Archivo de ocurrencias"

      	       reg.idDoc = nroDoc;
      	       reg.idTer = idT;
      	       archivoOcur.write((char*)&reg,sizeof(reg));  // y luego al "Archivo de ocurrencia de terminos en docs"

      	     cout << reg.idDoc << " documento de : " << palabraStr << endl;
      	     cout << reg.idTer << " idT de: " << palabraStr << endl;
              }

      	       palabra = strtok (NULL," .,;:¿?_-<>/!	");
      	     }
           }
    	nroDoc++;
    	arch_frases.read(doc,TAMANIO_REGISTRO_FRASES);
     }
	arch_frases.close();
    archivoOcur.close();
    delete []doc;
    delete []serial;
    delete mapa;

    this->ordenarSort();
    this->cargar_listasInvertidas();
}
//  cout << palabraStr << " su tamaño es: " << palabraStr.size() << endl;      //ANTES DE NORMALIZAR
//  cout << palabraStr << endl;                                              //DESPUES DE NORMALIZAR


void Booleano::ordenarSort (){

	ifstream archivoOcur (PATH_ARCHIVO_OCURRENCIAS,ios::binary | ios::in);

	Ordenador* unOrdenador = new Ordenador(this->cant_registros_ocurrencias());

	unOrdenador->ordenar(&archivoOcur);

	delete unOrdenador;
	archivoOcur.close();
}

void Booleano::terminoEncontrado(string palabraStr,int *i, bool *encontrado){

	ifstream archivoTerminos (PATH_ARCHIVO_TERMINOS,ios::binary);  //archivo de terminos por orden de aparicion.
	*encontrado = false;

	if (archivoTerminos.is_open()) {

	archivoTerminos.seekg(0,ios::end);
	long int nBytes = archivoTerminos.tellg();

      if (nBytes > 0) {

        char* buffer = new char[nBytes];

        if (buffer) {
		   archivoTerminos.seekg(0,ios::beg);
		   archivoTerminos.read(buffer,nBytes);
		   archivoTerminos.close();


	      int j = 0;
		 char longitud;

	    while ( (nBytes > 0) && ( !( *encontrado ) ) ) {

	    	*i = j;
	    	memmove(&longitud,&buffer[j],sizeof(longitud));
			j = j + sizeof(longitud);
			nBytes = nBytes - sizeof(longitud);

			char* termino = new char[longitud];
			memmove(termino,&buffer[j],longitud);
			j = j + longitud;
			nBytes = nBytes - longitud;

			string palabra(termino);
			palabra = palabra.substr(0,longitud);

			if (palabra == palabraStr)
			   *encontrado = true;

            delete[] termino;
		}
    }
    else
    	cout << "No se tiene memoria para levantar el archivo" << endl;
   }
}

}

void Booleano::cargar_listasInvertidas (){

	ifstream arch_ocur_ord (PATH_ARCHIVO_OCURRENCIAS_ORD, ios::binary);
	fstream invertidas (PATH_ARCHIVO_INVERTIDAS,ios::binary | ios::in | ios::out);

	ArbolBMas* arbol = new ArbolBMas(PATH_ARBOL);
	list<int> listaInver;
    int cantDocs = 0;
    int pos;

    RegOcurrencia reg;

    arch_ocur_ord.read((char*)&reg,sizeof(reg));

    int idTerAux = reg.idTer;

	while (!arch_ocur_ord.eof()) {

		if (reg.idTer == idTerAux) {
			listaInver.push_back(reg.idDoc);
			cantDocs++;
			arch_ocur_ord.read((char*)&reg,sizeof(reg));
		}
		else{
		    listaInver.push_front(cantDocs);

		    if (this->agregar_arch_invertidas (listaInver,cantDocs,idTerAux,&pos,&invertidas)){

            cout << "la posicion del idTermino: " << idTerAux << " es : " << pos << endl;
		    this->agregar_a_Arbol(idTerAux,pos,arbol);         //aca iria el "cargar en el arbol"
		    }
		    listaInver.clear();
		    cantDocs = 0;
		    idTerAux = reg.idTer;

		}

	}
	invertidas.seekp(0,ios::beg);
	invertidas.write((char*)this->tam_libre,TAMANIO_BLOQUE_LISTAS_INV);
	invertidas.close();

	arch_ocur_ord.close();
	delete arbol;

}

bool Booleano::agregar_arch_invertidas (list<int> inver,int cantDoc, int idT, int *pos,fstream *invertidas){
//	cout << "la longitud del string: " << ls_Comprimida << " es : " << (int)ls_long << endl;
//	cout << "la longitud libre de : "<< *pos << " es: " << (int)this->tam_libre [*pos - 1] <<  endl;

	char *bloque = new char[TAMANIO_BLOQUE_LISTAS_INV];

	CodigoGamma gamma;

    *pos = 1;

	string ls_Comprimida = gamma.comprimirLista(inver,cantDoc);

	unsigned char ls_long = ls_Comprimida.size();
	unsigned short int id = idT;
	char long_libre = ( (this->tam_libre [*pos-1]) - ls_long - sizeof (id) - sizeof (ls_long) );

	if (long_libre >= 0){

    while ( (long_libre <= UMBRAL) && ( (*pos) < TAMANIO_BLOQUE_LISTAS_INV) ) {
    	(*pos)++;
    	long_libre = ( (this->tam_libre [*pos - 1]) - ls_long - sizeof (id) - sizeof (ls_long) );
    }
    if ( *pos >= TAMANIO_BLOQUE_LISTAS_INV ){
    	cout << "no hay espacio suficiente en los bloques" << endl;
    	delete []bloque;
    	return false;
    }
    else{
    	if (this->tam_libre [*pos-1] < TAMANIO_BLOQUE_LISTAS_INV ){
    		invertidas->seekg((*pos)*TAMANIO_BLOQUE_LISTAS_INV,ios::beg);
    		invertidas->read(bloque,TAMANIO_BLOQUE_LISTAS_INV);
    	}
        int desplazo = (TAMANIO_BLOQUE_LISTAS_INV - this->tam_libre [*pos-1]);
        memmove (&bloque[desplazo],&id,sizeof(id));
        desplazo += sizeof(id);
        memmove (&bloque[desplazo],&ls_long,sizeof(ls_long));
        desplazo += sizeof(ls_long);
        memmove (&bloque[desplazo],ls_Comprimida.c_str(),ls_long);

        invertidas->seekp((*pos)*TAMANIO_BLOQUE_LISTAS_INV,ios::beg);
        invertidas->write(bloque,TAMANIO_BLOQUE_LISTAS_INV);
        invertidas->flush();
        this->tam_libre [*pos-1] = long_libre;
      }
       delete []bloque;
       return true;

	}
	 else{
		 cout << "no hay espacio suficiente en los bloques" << endl;
	     delete []bloque;
		 return false;
	 }
}
//    int desplazo = (TAMANIO_BLOQUE_LISTAS_INV - this->tam_libre [*pos - 1]);
//    memmove (&bloque[desplazo],&id,sizeof(id));
//    desplazo += sizeof(id);
//    memmove (&bloque[desplazo],&ls_long,sizeof(ls_long));
//    desplazo += sizeof(ls_long);
//    memmove (&bloque[desplazo],ls_Comprimida.c_str(),ls_long);
//    invertidas->seekp((*pos)*TAMANIO_BLOQUE_LISTAS_INV,ios::beg);
//    invertidas->write(bloque,TAMANIO_BLOQUE_LISTAS_INV);
//    invertidas->flush();

//    int desplazo = (*pos)*TAMANIO_BLOQUE_LISTAS_INV + (TAMANIO_BLOQUE_LISTAS_INV - this->tam_libre [*pos]);
//    invertidas->seekp(desplazo,ios::beg);
//    invertidas->write((char*)&id,sizeof (id));
//    invertidas->write((char*)&ls_long,sizeof (ls_long));
//    invertidas->write((char*)&ls_Comprimida,sizeof (ls_Comprimida));

void Booleano::agregar_a_archivoT (string palabra, int *offset){

	ofstream archivoTerminos (PATH_ARCHIVO_TERMINOS,ios::binary | ios::app);  //archivo de terminos por orden de aparicion.

	archivoTerminos.seekp(0,ios::end);
	*offset = archivoTerminos.tellp();

	char long_term = palabra.size();

	archivoTerminos.write(&long_term,sizeof(long_term));
	archivoTerminos.write((char*)palabra.c_str(),long_term);
	archivoTerminos.flush();
	archivoTerminos.close();

//	cout << (int)long_term << " longitud de: " << palabra << endl;
//	cout << *offset << " offset de: " << palabra << endl;
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

string Booleano::obtenerTermino (int idT){
    char longitud;
	ifstream archivoT (PATH_ARCHIVO_TERMINOS,ios::binary);
    string term;

	archivoT.seekg(idT,ios::beg);
	archivoT.read(&longitud,sizeof(longitud));
	archivoT.read((char*)term.c_str(),longitud);
	string palabra(term.c_str());
	palabra = palabra.substr(0,longitud);
	archivoT.close();
	return palabra;

}

void Booleano::agregar_a_Arbol (int idT,int pos_Arch, ArbolBMas *arbol){

	Clave *clave = new Clave(this->obtenerTermino(idT));
	Persistencia *termino = new Persistencia(this->obtenerTermino(idT));
	Persistencia *posicion = new Persistencia(arbol->IntToStr(idT));
	Persistencia *fantasma = new Persistencia(arbol->IntToStr(pos_Arch));

	Elementos *elem = new Elementos(clave,termino,posicion,fantasma);

    arbol->insertar(elem);

    delete elem;
}

void Booleano::agregar_frase (string frase, int nroDoc){

	Normalizador normalizar;
	char *fraseProcesar = strdup (frase.c_str());
	char *palabra = strtok (fraseProcesar," .,;:¿?_-<>/!	");

	while (palabra != NULL) {
		string palabraStr(palabra);
		normalizar.normalizarPalabra(&palabraStr);
		bool esStop = this->compararTermino (palabraStr);
		if (!esStop) {
          cout << "no es stop" << endl;
		}
		palabra = strtok (NULL," .,;:¿?_-<>/!	");
	}
}

bool Booleano::obtenerListaIdT (string termino,list <int> *listaDocs){

	ArbolBMas* arbol = new ArbolBMas(PATH_ARBOL);

	bool encontrado;
	CodigoGamma gamma;
	string listaCod;
	Elementos* unElemento = this->buscarEnArbol(termino,arbol,&encontrado);
	delete arbol;

    if (encontrado) {

    	int bloqueLista = atoi (unElemento->getEnteroFantasma()->toString().c_str());
    	int idT = atoi(unElemento->getN()->toString().c_str());

    	if (this->buscarEnBloque(idT,bloqueLista,&listaCod))
    		*listaDocs = gamma.decodificarLista(listaCod);
    }
    return encontrado;
}

bool Booleano::buscarEnBloque (int id,int nroBloque,string *termDevuelto){

	bool encontrado = false;
	ifstream invertidas (PATH_ARCHIVO_INVERTIDAS,ios::binary);

	if (invertidas.is_open()){
	 unsigned char ls_long;
	 unsigned short int idT;
	 char *bloque = new char [TAMANIO_BLOQUE_LISTAS_INV];

	 invertidas.seekg(nroBloque*TAMANIO_BLOQUE_LISTAS_INV,ios::beg);
	 invertidas.read(bloque,TAMANIO_BLOQUE_LISTAS_INV);

	 int desplazo = 0;

	 while ((desplazo < TAMANIO_BLOQUE_LISTAS_INV) && (!encontrado)) {

	  memmove (&idT,&bloque[desplazo],sizeof(idT));
	  desplazo += sizeof(idT);

	  memmove (&ls_long,&bloque[desplazo],sizeof(ls_long));
      desplazo += sizeof(ls_long);

      char *lista = new char [(int)ls_long];

      memmove (lista,&bloque[desplazo],ls_long);
	  desplazo += (int)ls_long;

	  *termDevuelto = string(lista).substr(0,(int)ls_long);

	  delete []lista;

	  if (id == (int)idT) encontrado = true;
  }
	 delete []bloque;
 }
	invertidas.close();
	return encontrado;
}

Elementos* Booleano::buscarEnArbol (string palabra, ArbolBMas* arbol,bool * result){

	 Elementos* unElemento;
	 Clave* unaClave = new Clave(palabra);
	 unElemento = arbol->buscar(unaClave);
	 *result = ((unElemento != NULL) && (unElemento->getClave()->getClave()) == (unaClave->getClave()));
	 return unElemento;
}


//      this->agregar_a_Arbol (palabraStr,arbol,idT);       // y luego al Arbol como (termino, idT, 0)
//		arch_frases.seekg(nroDoc*TAMANIO_REGISTRO_FRASES,ios::beg);
//      arch_frases.read(doc,TAMANIO_REGISTRO_FRASES);
