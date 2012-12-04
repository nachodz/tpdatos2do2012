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

}

Booleano::~Booleano() {
	delete [](this->listaStopWords);
}

void Booleano::cargar_ls_bloques (){

	unsigned char *tam_libre = new unsigned char[TAMANIO_BLOQUE_LISTAS_INV];

	for ( int i = 0; i < TAMANIO_BLOQUE_LISTAS_INV; i++){
		tam_libre[i] = TAMANIO_BLOQUE_LISTAS_INV;
	}
	ofstream invertidas (PATH_ARCHIVO_INVERTIDAS,ios::binary | ios::out);
	invertidas.seekp(0,ios::beg);
	invertidas.write((char*)tam_libre,TAMANIO_BLOQUE_LISTAS_INV);
	invertidas.close();
	delete []tam_libre;
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
   	    	   this->agregar_a_archivoT(palabraStr,&idT);  // si no lo encontro, agrego al "Archivo de ocurrencias"

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

	this->cargar_ls_bloques();
	ifstream arch_ocur_ord (PATH_ARCHIVO_OCURRENCIAS_ORD, ios::binary);
	fstream invertidas (PATH_ARCHIVO_INVERTIDAS,ios::binary | ios::in | ios::out);

	ArbolBMas* arbol = new ArbolBMas(PATH_ARBOL);
	list<int> listaInver;
    int cantDocs = 0;
    int pos;
    bool modificar;
    RegOcurrencia reg;

    arch_ocur_ord.read((char*)&reg,sizeof(reg));
    int idTerAux = reg.idTer;
    int idDocAux = -1;

    while (!arch_ocur_ord.eof()){

		if (reg.idTer == idTerAux) {
		    if (reg.idDoc != idDocAux){
		    	listaInver.push_back(reg.idDoc);
			    cantDocs++;
			    idDocAux = reg.idDoc;
		   }
			arch_ocur_ord.read((char*)&reg,sizeof(reg));
		}
		else{
		    listaInver.push_front(cantDocs);

		    if (this->agregar_arch_invertidas (listaInver,cantDocs,idTerAux,&pos,&invertidas)){
//		    	cout << "la posicion del idTermino: " << idTerAux << " es : " << pos << endl;
                modificar = false;
		        this->agregar_a_Arbol(idTerAux,pos,arbol,modificar);
		    }
		    listaInver.clear();
		    cantDocs = 0;
		    idTerAux = reg.idTer;
		    idDocAux = -1;
		  }
	}

     if (reg.idTer == idTerAux) {            // Repito esto para que tome el utlimo nroDoc;

    	listaInver.push_back(reg.idDoc);
    	cantDocs++;
    	listaInver.push_front(cantDocs);

    	if (this->agregar_arch_invertidas (listaInver,cantDocs,idTerAux,&pos,&invertidas)){
//    	  cout << "la posicion del idTermino: " << idTerAux << " es : " << pos << endl;
    	  modificar = false;
    	  this->agregar_a_Arbol(idTerAux,pos,arbol, modificar);
    	  }
    	}

	invertidas.close();
	arch_ocur_ord.close();
	delete arbol;

}

//cout <<"Lista antes de comprimir :   "<< ls_Comprimida << endl;
//cout <<"Lista comprimida :   "<< ls_ComprimidaEnBits << endl;
//cout <<"Lista despues de comprimir :   "<< gamma.convertirAString(strdup(ls_ComprimidaEnBits.c_str())) << endl;
//cout <<"Lista longitud comprimida :   "<< ls_ComprimidaEnBits.size() << endl;
//cout << "la longitud del string: " << ls_Comprimida << " es : " << (int)ls_long << endl;
//cout << "la longitud libre de : "<< *pos << " es: " << (int)this->tam_libre [*pos - 1] <<  endl;

bool Booleano::agregar_arch_invertidas (list<int> inver,int cantDoc, int idT, int *pos,fstream *invertidas){

	char *tam_libre = new char [TAMANIO_BLOQUE_LISTAS_INV];
	char *bloque = new char[TAMANIO_BLOQUE_LISTAS_INV];

	CodigoGamma gamma;
	*pos = 1;

	invertidas->seekg(0,ios::beg);
	invertidas->read (tam_libre,TAMANIO_BLOQUE_LISTAS_INV);

     string ls_Comprimida = gamma.comprimirLista(inver,cantDoc);
	 string ls_ComprimidaEnBits = gamma.stringABits(ls_Comprimida);

	unsigned char ls_long = ls_ComprimidaEnBits.size();
	unsigned short int id = idT;

	char long_libre = (unsigned char)tam_libre [*pos-1] - ls_long - sizeof (id) - sizeof (ls_long);

	if (long_libre >= 0){

     while ( (long_libre <= UMBRAL) && ( (*pos) < TAMANIO_BLOQUE_LISTAS_INV) ) {

    	(*pos)++;
    	long_libre = (unsigned char)tam_libre [*pos-1] - ls_long - sizeof (id) - sizeof (ls_long);
    }

    if ( *pos >= TAMANIO_BLOQUE_LISTAS_INV ){
    	cout << "No hay espacio suficiente en los bloques" << endl;
    	delete []tam_libre;
    	delete []bloque;
    	return false;
    }
    else{
    	if ((unsigned char)tam_libre [*pos-1] < TAMANIO_BLOQUE_LISTAS_INV ){

    		invertidas->seekg((*pos)*TAMANIO_BLOQUE_LISTAS_INV,ios::beg);
    		invertidas->read(bloque,TAMANIO_BLOQUE_LISTAS_INV);
    	}
        int desplazo = (TAMANIO_BLOQUE_LISTAS_INV - (unsigned char)tam_libre[*pos-1]);

        memmove (&bloque[desplazo],&id,sizeof(id));
        desplazo += sizeof(id);
        memmove (&bloque[desplazo],&ls_long,sizeof(ls_long));
        desplazo += sizeof(ls_long);
        memmove (&bloque[desplazo],ls_ComprimidaEnBits.c_str(),ls_long);

        invertidas->seekp((*pos)*TAMANIO_BLOQUE_LISTAS_INV,ios::beg);
        invertidas->write(bloque,TAMANIO_BLOQUE_LISTAS_INV);
        invertidas->flush();
        tam_libre [*pos-1] = long_libre;
        invertidas->seekp(0,ios::beg);
        invertidas->write(tam_libre,TAMANIO_BLOQUE_LISTAS_INV);
      }
      delete []bloque;
      delete []tam_libre;
      return true;

    }else{
		 cout << "No hay espacio suficiente en los bloques" << endl;
	     delete []bloque;
	     delete []tam_libre;
		 return false;
	     }
}

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

void Booleano::agregar_a_Arbol (int idT,int pos_Arch, ArbolBMas *arbol, bool modificar){

	Clave *clave = new Clave(this->obtenerTermino(idT));
	Persistencia *termino = new Persistencia(this->obtenerTermino(idT));
	Persistencia *posicion = new Persistencia(arbol->IntToStr(idT));
	Persistencia *fantasma = new Persistencia(arbol->IntToStr(pos_Arch));

	Elementos *elem = new Elementos(clave,termino,posicion,fantasma);

	if (modificar)
		arbol->modificar(elem);
	else
		arbol->insertar(elem);

    delete elem;
}

void Booleano::agregarDocALista (int nroDoc, int idT, int numBlok){

	CodigoGamma gamma;
	string listaEnBitsVieja;
	int offsetEnBloque;

	if (this->buscarEnBloque(idT,numBlok,&listaEnBitsVieja,&offsetEnBloque)){

	 list <int> listaDocs = gamma.decodificarLista(gamma.convertirAString(strdup(listaEnBitsVieja.c_str())));
	 if (! this->buscarEnListaDocs(listaDocs,nroDoc) ) {
		  listaDocs.push_back(nroDoc);
	      int cantDocs = listaDocs.front();
	      listaDocs.pop_front();
	      cantDocs++;
	      listaDocs.push_front(cantDocs);
	      string listaComprNueva = gamma.comprimirLista(listaDocs,cantDocs);
          string listaEnBitsNueva = gamma.stringABits(listaComprNueva);

          bool darAlta = true;

          if ( this->actualizar_bloqueLista (listaEnBitsNueva,listaEnBitsVieja.size(),numBlok,offsetEnBloque,darAlta) )
        	 cout << "Se actualizo bien la lista" << endl;
          else
        	 cout << "No se actualizo bien la lista" << endl;

   }else
		cout << "El documento ya se encuentra en la lista" << endl;
 }else
	  cout << "No se encontro termino en Archivo de Listas Invertidas" << endl;
}

bool Booleano::actualizar_bloqueLista (string listNuevaCodEnBits,int tam_listVieja,int numBloq, int offsetEnBloke, bool alta){

	fstream invertidas (PATH_ARCHIVO_INVERTIDAS,ios::binary | ios::in | ios::out);
	CodigoGamma gamma;

	int variacion,desplazoI,desplazoF,cantCopiar,posGrabar;
	unsigned char long_lista;
	char long_libre;

	bool actualizado = false;
	int tamFijo = sizeof(unsigned short int) + sizeof (unsigned char); // Tamaño que es fijo para todas las listas;

	char *bloque = new char[TAMANIO_BLOQUE_LISTAS_INV];

	char *tam_libre = new char [TAMANIO_BLOQUE_LISTAS_INV];
	invertidas.seekg(0,ios::beg);
	invertidas.read (tam_libre,TAMANIO_BLOQUE_LISTAS_INV);  // Levanto el array de Espacio libre;

	if (alta){
		variacion = listNuevaCodEnBits.size() - tam_listVieja;   // Tamaño en el que vario la lista nueva respecto de la vieja;
	    long_libre = (unsigned char)tam_libre[numBloq-1] - variacion;  //Esp.Libre que va a quedar en el bloque;
	}
	else{
		 variacion = tam_listVieja -listNuevaCodEnBits.size();
	     long_libre = (unsigned char)tam_libre[numBloq-1] + variacion;
	}

	if (long_libre >= 0){                    // Me fijo si entra el bloque la lista nueva;
		cout << "Se puede agregar/quitar Doc" << endl;

		invertidas.seekg(numBloq*TAMANIO_BLOQUE_LISTAS_INV,ios::beg);
        invertidas.read (bloque,TAMANIO_BLOQUE_LISTAS_INV);          // Leo el bloque a modificar;

        if (alta){
        	desplazoI = offsetEnBloke + tamFijo + tam_listVieja;    // Posicion a partir de la cual voy a correr para adelante;
		    desplazoF = desplazoI + variacion;                      // A partir de donde se va a empezar a copiar;
	    }
        else{
        	desplazoF = offsetEnBloke + tamFijo + listNuevaCodEnBits.size();
        	desplazoI = desplazoF + variacion;
	    }

        cantCopiar = ( TAMANIO_BLOQUE_LISTAS_INV - (unsigned char)tam_libre[numBloq-1] ) - desplazoI; // Cant. bytes que voy a correr;

        memmove (&bloque[desplazoF],&bloque[desplazoI],cantCopiar);  // Corro en el bloque;

		long_lista = listNuevaCodEnBits.size();       // Tamaño lista nueva a agregar;

		posGrabar = offsetEnBloke + sizeof (unsigned short int); // Pos. en la que grabo el nuevo tam de la lista.

        memmove (&bloque[posGrabar],&long_lista, sizeof(long_lista)); // Grabo el long de la lista;

        posGrabar = posGrabar + sizeof(long_lista);

        memmove (&bloque[posGrabar],listNuevaCodEnBits.c_str(), long_lista);   // Grabo la lista;

        invertidas.seekg(numBloq*TAMANIO_BLOQUE_LISTAS_INV,ios::beg);
        invertidas.write(bloque,TAMANIO_BLOQUE_LISTAS_INV);            // Grabo bloque en el archivo;

        tam_libre[numBloq-1] = long_libre;    // Actualizo lista de tamaño libre;
        invertidas.seekg(0,ios::beg);
        invertidas.write (tam_libre,TAMANIO_BLOQUE_LISTAS_INV);

	    actualizado = true;
	}
	else
		cout << "No se puede agregar/quitar Doc" << endl;

	delete []tam_libre;
    delete []bloque;
    invertidas.close();
    return actualizado;
}

//this->terminoEncontrado(termino,&idT,&encontrado);
void Booleano::alta (string termino, int nroDoc){

	int idT,bloqueLista;
    Normalizador normalizar;
    ArbolBMas* arbol = new ArbolBMas(PATH_ARBOL);

	normalizar.normalizarPalabra(&termino);
	bool esStop = this->compararTermino (termino);

		if (!esStop) {

		  bool encontrado;
		  Elementos *elem = this->buscarEnArbol(termino,arbol,&encontrado);

	      if (encontrado) {

	    	  bloqueLista = atoi (elem->getEnteroFantasma()->toString().c_str());
	    	          idT = atoi (elem->getN()->toString().c_str());

	    	  if (bloqueLista != 0)
	    		  this->agregarDocALista (nroDoc,idT,bloqueLista);
	    	  else{
	    		  this->agregarNuevaListaInvertidas(idT,nroDoc,&bloqueLista);
	    		  bool modificar = true;
	    		  this->agregar_a_Arbol(idT,bloqueLista,arbol,modificar);
	    	  }

	      }
		  else{
			   cout << "El termino: "<< termino <<" no esta Indexado" << endl;

	           this->agregar_a_archivoT(termino,&idT);
	           this->agregarNuevaListaInvertidas(idT,nroDoc,&bloqueLista);
	           bool modificar = false;
	           this->agregar_a_Arbol(idT,bloqueLista,arbol,modificar);

	           cout << "El termino: "<< termino <<" ahora esta Indexado" << endl;
		      }
		}
	    else
	    	cout <<"Es una StopWord" << endl;

     delete arbol;
}

void Booleano::baja (string terminoBaja, int nroDocBaja){

	int idTBaja;
    Normalizador normalizar;
	ArbolBMas* arbol = new ArbolBMas(PATH_ARBOL);

	normalizar.normalizarPalabra(&terminoBaja);
	bool esStop = this->compararTermino (terminoBaja);

    if (!esStop) {
    	bool encontrado;
		Elementos *elem = this->buscarEnArbol(terminoBaja,arbol,&encontrado);

      if (encontrado) {
    	  int bloqueLista = atoi (elem->getEnteroFantasma()->toString().c_str());

    	  if (bloqueLista != 0) {

      	     idTBaja = atoi (elem->getN()->toString().c_str());

      	     bool estaVacio;
		     this->quitarDocLista (nroDocBaja,idTBaja,bloqueLista,&estaVacio);

             if (estaVacio)
            	 this->quitar_termino_Arbol (terminoBaja,idTBaja,arbol);

    	  }else
    		  cout << "El termino: "<< terminoBaja << "ya esta dado de baja" << endl;
	 }else
		cout << "No se encontro termino: " << terminoBaja << " ,en el Indice" << endl;
   }else
	  cout <<"Es una StopWord" << endl;

    delete arbol;
}

void Booleano::quitar_frase (string frase, int nroDoc){

	char *fraseProcesar = strdup (frase.c_str());
	char *palabra = strtok (fraseProcesar," .,;:¿?_-<>/!	");

	while (palabra != NULL) {

		string palabraStr(palabra);

        this->baja(palabraStr,nroDoc);

		palabra = strtok (NULL," .,;:¿?_-<>/!	");
	}
}

void Booleano::quitar_termino_Arbol (string terminoBaja, int idT, ArbolBMas* arbol){

	    Clave *clave = new Clave(terminoBaja);
		Persistencia *termino = new Persistencia(terminoBaja);
		Persistencia *posicion = new Persistencia(arbol->IntToStr(idT));
		Persistencia *fantasma = new Persistencia("0");

		Elementos *elem = new Elementos(clave,termino,posicion,fantasma);

	    if ( arbol->modificar(elem) )
	    	cout << "Se quito el termino del Arbol" << endl;
	    else
	    	cout << "No se pudo quitar el termino del Arbol, porque no existe" << endl;

	    delete elem;
}

void Booleano::quitarDocLista (int DocBaja,int idBaja, int bloqueLs, bool *vacio){

	CodigoGamma gamma;
	string listaEnBitsVieja;
	int offsetEnBloque;
	*vacio = false;

	if (this->buscarEnBloque(idBaja,bloqueLs,&listaEnBitsVieja,&offsetEnBloque)){

	 list <int> listaDocs = gamma.decodificarLista(gamma.convertirAString(strdup(listaEnBitsVieja.c_str())));

     if ( this->buscarEnListaDocs(listaDocs,DocBaja) ){

    	 int cantDocs = listaDocs.front();
         if (cantDocs == 1){
        	 this->eliminarListaInvertida (bloqueLs,offsetEnBloque,listaEnBitsVieja.size());
		     *vacio = true;
	     }
	     else{
	    	 listaDocs.pop_front();
	         cantDocs--;
	         listaDocs.remove(DocBaja);
	         listaDocs.push_front(cantDocs);
	         string listaNuevaEnBits = gamma.stringABits(gamma.comprimirLista(listaDocs,cantDocs));
	         bool darAlta = false;

	         if ( this->actualizar_bloqueLista(listaNuevaEnBits,listaEnBitsVieja.size(),bloqueLs,offsetEnBloque,darAlta) )
	    	   cout << "Se actualizo correctamente la lista correspondiente al termino" << endl;
	         else
	    	   cout << "No se actualizo correctamente la lista correspondiente al termino" << endl;
	        }
	    }else
	    	cout << "No se encontro el Documento a borrar" << endl;
   }else
      cout << "No se encontro lista en el Archivo de Listas Invertidas" << endl;
}

void Booleano::eliminarListaInvertida (int nBloq, int offsetEnBloq, unsigned int listaSize){

	fstream invertidas (PATH_ARCHIVO_INVERTIDAS,ios::binary | ios::in | ios::out);

	char *bloque = new char[TAMANIO_BLOQUE_LISTAS_INV];
	char *tam_libre = new char [TAMANIO_BLOQUE_LISTAS_INV];

	invertidas.seekg(0,ios::beg);
	invertidas.read (tam_libre,TAMANIO_BLOQUE_LISTAS_INV);  // Levanto el array de Espacio libre;

	invertidas.seekg(nBloq*TAMANIO_BLOQUE_LISTAS_INV,ios::beg);
    invertidas.read (bloque,TAMANIO_BLOQUE_LISTAS_INV);          // Leo el bloque a modificar;

    int tamFijo = sizeof(unsigned short int) + sizeof (unsigned char); // Tamaño que es fijo para todas las listas;
    int desplazoI = offsetEnBloq + tamFijo + listaSize;
    int cantCopiar = (TAMANIO_BLOQUE_LISTAS_INV - (unsigned char)tam_libre[nBloq-1]) - desplazoI; // Cant. bytes que voy a correr;

    memmove (&bloque[offsetEnBloq],&bloque[desplazoI],cantCopiar);  // Corro en el bloque;

    invertidas.seekg(nBloq*TAMANIO_BLOQUE_LISTAS_INV,ios::beg);
    invertidas.write(bloque,TAMANIO_BLOQUE_LISTAS_INV);            // Grabo bloque en el archivo;

    tam_libre[nBloq-1] -= tamFijo + listaSize;    // Actualizo lista de tamaño libre;

    invertidas.seekg(0,ios::beg);
    invertidas.write (tam_libre,TAMANIO_BLOQUE_LISTAS_INV);

	delete []bloque;
	delete []tam_libre;
	invertidas.close();
}

void Booleano::agregarNuevaListaInvertidas(int id, int nroDoc, int *pos){

    CodigoGamma gamma;
	list <int> listaAgregar;

    listaAgregar.push_front(1);
    listaAgregar.push_back(nroDoc);
    string listaComprEnBits = gamma.stringABits(gamma.comprimirLista(listaAgregar,1));

    fstream invertidas (PATH_ARCHIVO_INVERTIDAS,ios::binary |ios::in | ios::out);

    if ( !( this->agregar_arch_invertidas(listaAgregar,1,id,pos,&invertidas) ) )
    	cout << "No se pudo agregar lista, bloques llenos" << endl;

    invertidas.close();

}

void Booleano::agregar_frase (string frase, int nroDoc){

	char *fraseProcesar = strdup (frase.c_str());
	char *palabra = strtok (fraseProcesar," .,;:¿?_-<>/!	");

	while (palabra != NULL) {

		string palabraStr(palabra);

        this->alta(palabraStr,nroDoc);

		palabra = strtok (NULL," .,;:¿?_-<>/!	");
	}
}

bool Booleano::obtenerListaIdT (string termino,list <int> *listaDocs,int *nroBloque){

	ArbolBMas* arbol = new ArbolBMas(PATH_ARBOL);
	bool encontrado;
	CodigoGamma gamma;
	string listaCod;
	int offsetLista;
	Normalizador normalizar;
	normalizar.normalizarPalabra(&termino);

	Elementos* unElemento = this->buscarEnArbol(termino,arbol,&encontrado);
	delete arbol;

    if (encontrado) {

     int bloqueLista = atoi (unElemento->getEnteroFantasma()->toString().c_str());

     if (bloqueLista != 0) {

    	 int idTer = atoi(unElemento->getN()->toString().c_str());
         *nroBloque = bloqueLista;

         if ( this->buscarEnBloque(idTer,bloqueLista,&listaCod,&offsetLista) )
             *listaDocs = gamma.decodificarLista(gamma.convertirAString(strdup(listaCod.c_str())));
     }else
    	  encontrado = false;
   }
    return encontrado;
}

//cout << gamma.convertirAString(strdup(listaCod.c_str())) << endl;
/*const_cast <char*>*/
//char *listaProcesar = strdup (listaCod.c_str());

bool Booleano::buscarEnBloque (int id,int nroBloque,string *listaDevuelto, int *offsetEnBloque){

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

	  *offsetEnBloque = desplazo;

	  memmove (&idT,&bloque[desplazo],sizeof(idT));
	  desplazo += sizeof(idT);

	  if (id == (int)idT) {

       encontrado = true;

	   memmove (&ls_long,&bloque[desplazo],sizeof(ls_long));
       desplazo += sizeof(ls_long);

       char *lista = new char [(int)ls_long];

       memmove (lista,&bloque[desplazo],ls_long);
   	   desplazo += (int)ls_long;

   	   *listaDevuelto = string(lista).substr(0,(int)ls_long);
	}
	 else {
	   memmove (&ls_long,&bloque[desplazo],sizeof(ls_long));
       desplazo += sizeof(ls_long) + (int)ls_long;
	  }
  }
	 delete []bloque;
 }
	invertidas.close();
	return encontrado;
}

Elementos* Booleano::buscarEnArbol (string palabra, ArbolBMas* arbol,bool *result){

	 Elementos* unElemento;
	 Clave* unaClave = new Clave(palabra);
	 unElemento = arbol->buscar(unaClave);
	 *result = ((unElemento != NULL) && (unElemento->getClave()->getClave()) == (unaClave->getClave()));
	 return unElemento;
}

bool Booleano::buscarEnListaDocs (list <int> listaDoc, int nroDc){

   bool encontrado = false;
   list <int>::iterator it = listaDoc.begin();
   it++;

   while ( it != listaDoc.end() && !encontrado){
	   encontrado = ( (*it) == nroDc );
       it++;
      }

   return encontrado;
}

// EN PROCESO....
void Booleano::buscarListaTerminos (string *listaTerminos, int cantTerm){

	Normalizador normalizar;
	list <int> listaDocsAux, listDocsTotal,listaDocsMerge;
	list <int>::iterator it;
	int numBloque, inicio, fin, docAux, cont;

	inicio = clock();

	for(int i = 0; i < cantTerm; i++){

		normalizar.normalizarPalabra(&listaTerminos[i]);

		if ( this->obtenerListaIdT(listaTerminos[i],&listaDocsAux,&numBloque) ){
			listaDocsAux.pop_front();
			listaDocsAux.sort();
			listDocsTotal.merge(listaDocsAux);
		}
	 }
	// LISTA CON TODOS LOS DOCS
	if (!listDocsTotal.empty()){

    	  docAux = listDocsTotal.front();
          cont = 0;
	   for (it = listDocsTotal.begin(); it != listDocsTotal.end(); it++){

		   if (docAux == *it) cont++;
		   else{
			   docAux = *it;
			   cont = 1;
		      }
           if (cont == cantTerm)
        	   listaDocsMerge.push_back(*it);
	   }

   }else
    	cout << "No se encontraron estos terminos indexados, no se genero el archivoTxt" << endl;

// LISTA FINAL CON LOS DOCS ENCONTRADOS EN TODAS LAS LISTAS
      if (!listaDocsMerge.empty()){
    	  fin = clock();
          float tEjec = fin - inicio;
    	  this->mostrarEnTxt (listaDocsMerge,cantTerm,listaTerminos,tEjec);
      }else
    	  cout << "No se encontraron Registros con esos terminos, no se genero archivoTxt" << endl;
}

void Booleano::mostrarEnTxt (list <int> listaDocs, int cantTerm, string *listaTerminos, float t){

	list <int>::iterator it;
	ifstream frases (PATH_ARCHIVO_FRASES,ios::binary | ios::in);
	ofstream ArchBusqueda(PATH_ARCHIVO_BUSQUEDA);
	char * Frase = new char [TAMANIO_REGISTRO_FRASES];

	ArchBusqueda << "Terminos : " << endl;

	for(int i = 0; i < cantTerm; i++)
	       ArchBusqueda << listaTerminos[i] << ",  ";

	ArchBusqueda << endl;
	ArchBusqueda << "Tiempo de ejecucion: " << t << " segundos" << endl;

	for (it = listaDocs.begin(); it != listaDocs.end(); it++){

		frases.seekg((*it)*TAMANIO_REGISTRO_FRASES,ios::beg);
		frases.read(Frase,TAMANIO_REGISTRO_FRASES);

		ArchBusqueda <<"El Nro Relativo es: "<< *it << " de la frase: " << string (Frase) << endl;
	}

	delete []Frase;
	ArchBusqueda.close();
	frases.close();
}

//      this->agregar_a_Arbol (palabraStr,arbol,idT);       // y luego al Arbol como (termino, idT, 0)
//		arch_frases.seekg(nroDoc*TAMANIO_REGISTRO_FRASES,ios::beg);
//      arch_frases.read(doc,TAMANIO_REGISTRO_FRASES);

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

