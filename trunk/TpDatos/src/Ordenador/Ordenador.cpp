
#include "Ordenador.h"

using namespace std;

Ordenador::Ordenador(int tamBufOrd) {

	this->tamBufOrd = tamBufOrd;
};

Ordenador::~Ordenador(){

};

void Ordenador::intercambio (Ocurrencias *buf, int a, int b){

	Ocurrencias aux;

    aux = buf[a];
    buf [a] = buf [b];
    buf [b] = aux;
};

void Ordenador::cargaInicial (ifstream *archIn, Ocurrencias *buffer) {

	 archIn->read((char*)buffer,sizeof(Ocurrencias)*tamBufOrd);
};

void Ordenador::achicarMonticulo (Ocurrencias *bufferSort,int tamHeap,ofstream *salida){

	 while (tamHeap > 1){


		 	 salida->write((char*)&(bufferSort[0]),sizeof(Ocurrencias));
	         bufferSort[0] = bufferSort[tamHeap-1];
	         tamHeap = tamHeap - 1;

	         this->myheapsort(bufferSort,tamHeap);
     }

	 salida->write((char*)&(bufferSort[0]),sizeof(Ocurrencias));
	 salida->close();
};

void Ordenador::myheapsort (Ocurrencias *buffer,int tamHeap){

  for (int i = 1; i <= tamHeap; i++ ) {

      int padre = (i/2); // i = 1 ; padre = 0
      int hijo = i;      //         hijo = 1


      while ((padre > 0) && ((mayor(buffer[padre-1],buffer[hijo-1])) == 1)) {

    	  this->intercambio(buffer,padre-1,hijo-1);

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

void Ordenador::copiarReg (Ocurrencias* regDestino,Ocurrencias* regOrigen){

	regDestino->idTermino = regOrigen->idTermino;
	regDestino->idFrase = regOrigen->idFrase;
};

void Ordenador::correrBuffer (Ocurrencias* bufNuevo, Ocurrencias* bufViejo, int cantaPasar){


	for (int i = 0,j = (tamBufOrd-cantaPasar); i < cantaPasar; i++,j++)
	{
		this->copiarReg(&(bufNuevo[i]),&(bufViejo[j]));
	}
};


int Ordenador::ordenar (ifstream *arch){

    int tamHeap = tamBufOrd;
    Ocurrencias ocurrencia, ultimoID;
    int tamUltHeap;
    int nroPart = 0;

    string filename = PATH_PARTICION + IntToStr(nroPart);
    ofstream *partNro = new ofstream [CANT_PARTICIONES];

    if
    	(!partNro) cout << "No hay espacio en memoria" << endl;

    else  {

    partNro[nroPart].open(filename.c_str(),ios::out | ios::binary);

    if (!(*arch))  cout << "No se pudo abrir el archivo" << endl;

    else {

    	Ocurrencias *bufferSort = new Ocurrencias [tamBufOrd];

    if (!bufferSort ) cout << "No hay espacio en memoria" << endl;

    else {

       this->cargaInicial(arch,bufferSort);
       this->myheapsort(bufferSort,tamHeap);

       arch->read((char*)&ocurrencia,sizeof(Ocurrencias));

       while (!arch->eof()) {

          ultimoID = bufferSort[0];

          partNro[nroPart].write((char*)&(bufferSort[0]),sizeof(Ocurrencias));

          if (this->mayor(ocurrencia,ultimoID) == 1)
        	  bufferSort[0] = ocurrencia;

          else {
             bufferSort[0] = bufferSort[tamHeap-1];
             this->copiarReg(&(bufferSort[tamHeap-1]),&ocurrencia);
             tamHeap = tamHeap - 1;
          }

          if (tamHeap == 1) {
            partNro[nroPart].write((char*)&(bufferSort[0]),sizeof(Ocurrencias));
            partNro[nroPart].close();
            nroPart++;

            arch->read((char*)&ocurrencia,sizeof(Ocurrencias));
            bufferSort[0] = ocurrencia;

            tamHeap = tamBufOrd;

            string filename = PATH_PARTICION + IntToStr(nroPart);
            partNro[nroPart].open(filename.c_str(),ios::out | ios::binary);
            this->myheapsort(bufferSort,tamHeap);
          }
          else
              this->myheapsort(bufferSort,tamHeap);

          arch->read((char*)&ocurrencia,sizeof(Ocurrencias));
       }

       arch->close();

    if (tamHeap < tamBufOrd )
        tamUltHeap = (tamBufOrd - tamHeap);
    else
        tamUltHeap = tamBufOrd;



    this->achicarMonticulo(bufferSort,tamHeap,&(partNro[nroPart]));

    nroPart++;
    string filename = PATH_PARTICION + IntToStr(nroPart);
    partNro[nroPart].open(filename.c_str(),ios::out | ios::binary);

    Ocurrencias *bufferUltHeap = new Ocurrencias [tamUltHeap];

    this->correrBuffer(bufferUltHeap,bufferSort,tamUltHeap);
    this->myheapsort(bufferUltHeap,tamHeap);
    this->achicarMonticulo(bufferUltHeap,tamUltHeap,&(partNro[nroPart]));

    delete []bufferSort;
    delete []bufferUltHeap;
    delete []partNro;

    }
  }
 }
  return nroPart;
};

int Ordenador::mayor(Ocurrencias ocurrencia1, Ocurrencias ocurrencia2) {

	if (ocurrencia1.idTermino > ocurrencia2.idTermino)
		return 1;
	else
		if (ocurrencia1.idTermino < ocurrencia2.idTermino)
			return 2;
		else
			if (ocurrencia1.idFrase >= ocurrencia2.idFrase)
				return 1;
			else
				return 2;
}

void Ordenador::ordenamientoEnRam(ifstream* archivo) {


}

