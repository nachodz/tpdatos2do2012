/*
 * Ordenador.cpp
 *
 *  Created on: 19/09/2012
 *      Author: nachodz
 */


#include "Ordenador.h"



using namespace std;

Ordenador::Ordenador(){};

Ordenador::~Ordenador(){};

void Ordenador::intercambio (tReg *buf, int a, int b){
   tReg aux;

   aux = buf[a];
   buf [a] = buf [b];
   buf [b] = aux;
};

void Ordenador::cargaInicial (ifstream *archIn, tReg *buffer) {

	archIn->read((char*)buffer,sizeof (tReg)*tamBufOrd);
};

void Ordenador::achicarMonticulo (tReg *bufferSort,int tamHeap,ofstream *salida){

	 while (tamHeap > 1){

	          salida->write((char*)&(bufferSort[0]),sizeof(tReg));
	          bufferSort[0] = bufferSort[tamHeap-1];
	          tamHeap = tamHeap - 1;

	          this->myheapsort(bufferSort,tamHeap);
     }

	 salida->write((char*)&(bufferSort[0]),sizeof(tReg));
	 salida->close();
};

void Ordenador::myheapsort (tReg *buffer,int tamHeap){

  for (int i = 1; i <= tamHeap; i++ ) {

      int padre = (i/2); // i = 1 ; padre = 0
      int hijo = i;      //         hijo = 1


      while ((padre > 0) && (buffer[padre-1].id > buffer[hijo-1].id )) {

    	  this->intercambio (buffer,padre-1,hijo-1);

    	  hijo = padre;          //hijo = 1
    	  padre = (padre/2);    // padre = 0
      }
   }
};

string Ordenador::IntToStr(int n) {

	stringstream result;
	result << n;
	return result.str();
}

void Ordenador::copiarReg (tReg* regDestino,tReg* regOrigen){

	regDestino->id = regOrigen->id;
	strcpy (regDestino->termino,regOrigen->termino);
};

void Ordenador::correrBuffer (tReg* bufNuevo, tReg* bufViejo, int cantaPasar){


	for (int i = 0,j = (tamBufOrd-cantaPasar); i < cantaPasar; i++,j++)
	{
		this->copiarReg(&(bufNuevo[i]),&(bufViejo[j]));
	}
};

void Ordenador::ordenar (ifstream *arch, int cantReg){

	tamBufOrd = cantReg*10;
	int tamHeap = tamBufOrd;
	tReg reg;
	int ultimoID,tamUltHeap;
	int nroPart = 0;

    string filename = PATH + IntToStr(nroPart);
 	ofstream *partNro = new ofstream [CANTPARTES];

 	if (!partNro) cout << "No hay espacio en memoria" << endl;
 	else  {

     partNro[nroPart].open(filename.c_str(),ios::out | ios::binary);

     if (!(*arch))  cout << "No se pudo abrir el archivo" << endl;
	else {

	    tReg *bufferSort = new tReg [tamBufOrd];

	    if (!bufferSort ) cout << "No hay espacio en memoria" << endl;
        else {

		this->cargaInicial(arch,bufferSort);
		this->myheapsort(bufferSort,tamHeap);

		arch->read((char*)&reg,sizeof(tReg));

	       while (!arch->eof()) {

		    ultimoID = bufferSort[0].id;

		    partNro[nroPart].write((char*)&(bufferSort[0]),sizeof(tReg));

            if (reg.id > ultimoID) this->copiarReg(&(bufferSort[0]),&reg);

            else {
             	bufferSort[0] = bufferSort[tamHeap-1];
             	this->copiarReg(&(bufferSort[tamHeap-1]),&reg);
                tamHeap = tamHeap - 1;
            }

            if (tamHeap == 1) {
        	partNro[nroPart].write((char*)&(bufferSort[0]),sizeof(tReg));
        	partNro[nroPart].close();
        	nroPart++;

   	        arch->read((char*)&reg,sizeof(tReg));
   	        this->copiarReg(&(bufferSort[0]),&reg);

   	        tamHeap = tamBufOrd;

   	        string filename = PATH + IntToStr(nroPart);
   	        partNro[nroPart].open(filename.c_str(),ios::out | ios::binary);
            this->myheapsort(bufferSort,tamHeap);
            } else
            	this->myheapsort(bufferSort,tamHeap);

        arch->read((char*)&reg,sizeof(tReg));
   }

	arch->close();

    if (tamHeap < tamBufOrd )
    	tamUltHeap = (tamBufOrd - tamHeap);
    else
    	tamUltHeap = tamBufOrd;

    cout << tamUltHeap << endl;

	this->achicarMonticulo(bufferSort,tamHeap,&(partNro[nroPart]));

	nroPart++;
	string filename = PATH + IntToStr(nroPart);
    partNro[nroPart].open(filename.c_str(),ios::out | ios::binary);

    tReg *bufferUltHeap = new tReg [tamUltHeap];

    this->correrBuffer (bufferUltHeap,bufferSort,tamUltHeap);
    this->myheapsort(bufferUltHeap,tamHeap);
 	this->achicarMonticulo(bufferUltHeap,tamUltHeap,&(partNro[nroPart]));

 	delete []bufferSort;
 	delete []bufferUltHeap;
 	delete []partNro;
   }
  }
 }
};











//void Ordenador::cantBuffersIn (ifstream *arch, int *cantBuf){
//	long begin,end,size;
//
//      begin = arch->tellg();
//      arch->seekg (0, ios::end);
//	  end = arch->tellg();
//	  size = end-begin;
//	  *cantBuf = (size/sizeof(tReg)) - 100;
//};
//
//
//void Ordenador::armarNuevoHeap (tReg *buffer){};

//     for (int i = 0; i < tamBufOrd; i++) {
//    	cout <<  bufferSort[i].id << "   " << bufferSort[i].termino << endl;
//
//     };

//void Ordenador::cargarBufIn (ifstream *archIn, tReg *bufIn) {
//	archIn->read((char*)bufIn,sizeof (tReg)*tamBufIO);
//};
//
//void Ordenador::escribirRegOut (ofstream *archOut, tReg *regOut) {
//
//	archOut->write((char*)&regOut,sizeof(tReg));
//};

//			    	 long begin,end;
//			    	 		begin = arch->tellg();
//			    	 		arch->seekg (0, ios::end);
//			    	 		end = arch->tellg();
//			    	 		cout << "size is: " << (end-begin) << " bytes." << endl;
