#include "OrdenadorTP1.h"

using namespace std;

OrdenadorTP1::OrdenadorTP1(int tamBufLec_Esc) {

        this->tamBufLec_Esc = tamBufLec_Esc;
        this->tamBufOrd = tamBufLec_Esc * 10;
};

OrdenadorTP1::~OrdenadorTP1(){

};

void OrdenadorTP1::intercambio (tReg *buf, int a, int b){
   tReg aux;

   aux = buf[a];
   buf [a] = buf [b];
   buf [b] = aux;
};

void OrdenadorTP1::cargaInicial (ifstream *archIn, tReg *buffer) {

        archIn->read((char*)buffer,sizeof (tReg)*tamBufOrd);
};

void OrdenadorTP1::grabarBufferEscritura(ofstream *archIn, tReg *buffer, int regAgrabar){

        if (regAgrabar == this->tamBufLec_Esc){

                archIn->write((char*)buffer, sizeof(tReg) * this->tamBufLec_Esc);
        }
        else
        {
                archIn->write((char*)buffer, sizeof(tReg) * regAgrabar);
        }
};

void OrdenadorTP1::cargaBufferLectura(ifstream *archIn, tReg *buffer, int cantRegistros){

        if (cantRegistros >= this->tamBufLec_Esc) {

                archIn->read((char*)buffer, sizeof(tReg) * this->tamBufLec_Esc);
        }
        else
        {
                archIn->read((char*)buffer, sizeof(tReg) * cantRegistros);
        }
};

void OrdenadorTP1::achicarMonticulo (tReg *bufferSort,int tamHeap,ofstream *salida){

         while (tamHeap > 1){

                  salida->write((char*)&(bufferSort[0]),sizeof(tReg));
                  bufferSort[0] = bufferSort[tamHeap-1];
                  tamHeap = tamHeap - 1;

                  this->myheapsort(bufferSort,tamHeap);
     }

         salida->write((char*)&(bufferSort[0]),sizeof(tReg));
         salida->close();
};

void OrdenadorTP1::myheapsort (tReg *buffer,int tamHeap){

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

string OrdenadorTP1::IntToStr(int n) {

        stringstream result;
        result << n;
        return result.str();
}

void OrdenadorTP1::copiarReg (tReg* regDestino,tReg* regOrigen){

        regDestino->id = regOrigen->id;
        strcpy (regDestino->termino,regOrigen->termino);
};

void OrdenadorTP1::correrBuffer (tReg* bufNuevo, tReg* bufViejo, int cantaPasar){


        for (int i = 0,j = (tamBufOrd-cantaPasar); i < cantaPasar; i++,j++)
        {
                this->copiarReg(&(bufNuevo[i]),&(bufViejo[j]));
        }
};

int OrdenadorTP1::ordenar (ifstream *arch, int cantRegistrosArchivo) {

        ofstream informes (PATH_INFORMES,ios::app);

        int tamHeap = this->tamBufOrd;
        int ultimoID,tamUltHeap;
        int nroPart = 0;
        int lec = 0, esc = 0;

    string filename = PATH_PARTICION + IntToStr(nroPart);
        ofstream *partNro = new ofstream [CANT_PARTICIONES];

        if (!partNro) cout << "No hay espacio en memoria" << endl;
        else
        {
                partNro[nroPart].open(filename.c_str(),ios::out | ios::binary);

                if (!(*arch))  cout << "No se pudo abrir el archivo" << endl;
                else
                {
                        tReg *bufferSort = new tReg [this->tamBufOrd];
                        tReg *bufferLectura = new tReg [this->tamBufLec_Esc];
                        tReg *bufferEscritura = new tReg [this->tamBufLec_Esc];

                        if ((!bufferSort ) || (!bufferLectura) || (!bufferEscritura)) cout << "No hay espacio en memoria" << endl;
                        else
                        {
                                this->cargaInicial(arch,bufferSort);
                                cantRegistrosArchivo = cantRegistrosArchivo - (BUFFER_LEC_ESC_SORT * 10);
                                this->myheapsort(bufferSort,tamHeap);

                                this->cargaBufferLectura(arch,bufferLectura,BUFFER_LEC_ESC_SORT);
                                cantRegistrosArchivo = cantRegistrosArchivo - BUFFER_LEC_ESC_SORT;

                                while (cantRegistrosArchivo > 0 || lec != 0){

                                        ultimoID = bufferSort[0].id;

                                        this->copiarReg(&(bufferEscritura[esc]),&(bufferSort[0]));
                                        esc++;


                                        if (esc == BUFFER_LEC_ESC_SORT) {
                                                this->grabarBufferEscritura(&(partNro[nroPart]),bufferEscritura,esc);
                                                esc = 0;
                                        }

                                        if (bufferLectura[lec].id > ultimoID) {

                                                this->copiarReg(&(bufferSort[0]),&(bufferLectura[lec]));
                                                lec++;

                                                if (lec == BUFFER_LEC_ESC_SORT) {
                                                        if (cantRegistrosArchivo < BUFFER_LEC_ESC_SORT){
                                                                this->cargaBufferLectura(arch,bufferLectura,cantRegistrosArchivo);
                                                                cantRegistrosArchivo = 0;
                                                        }
                                                        else
                                                        {
                                                                this->cargaBufferLectura(arch,bufferLectura,BUFFER_LEC_ESC_SORT);
                                                                cantRegistrosArchivo = cantRegistrosArchivo - BUFFER_LEC_ESC_SORT;
                                                        }
                                                        lec = 0;
                                                }
                                        }
                                        else
                                        {
                                                bufferSort[0] = bufferSort[tamHeap-1];
                                                this->copiarReg(&(bufferSort[tamHeap-1]),&(bufferLectura[lec]));
                                                lec++;

                                                if (lec == BUFFER_LEC_ESC_SORT) {
                                                        if (cantRegistrosArchivo < BUFFER_LEC_ESC_SORT){
                                                                this->cargaBufferLectura(arch,bufferLectura,cantRegistrosArchivo);
                                                                cantRegistrosArchivo = 0;
                                                        }
                                                        else
                                                        {
                                                                this->cargaBufferLectura(arch,bufferLectura,BUFFER_LEC_ESC_SORT);
                                                                cantRegistrosArchivo = cantRegistrosArchivo - BUFFER_LEC_ESC_SORT;
                                                        }
                                                        lec = 0;
                                                }

                                                tamHeap = tamHeap - 1;
                                        }

                                        if (tamHeap == 1) {

                                                this->copiarReg(&(bufferEscritura[esc]),&(bufferSort[0]));
                                                esc++;

                                                this->grabarBufferEscritura(&(partNro[nroPart]),bufferEscritura,esc);
                                                esc = 0;

                                                partNro[nroPart].close();
                                                nroPart++;

                                                this->copiarReg(&(bufferSort[0]),&(bufferLectura[lec]));
                                                lec++;

                                                if (lec == BUFFER_LEC_ESC_SORT) {
                                                        if (cantRegistrosArchivo < BUFFER_LEC_ESC_SORT){
                                                                this->cargaBufferLectura(arch,bufferLectura,cantRegistrosArchivo);
                                                                cantRegistrosArchivo = 0;
                                                        }
                                                        else
                                                        {
                                                                this->cargaBufferLectura(arch,bufferLectura,BUFFER_LEC_ESC_SORT);
                                                                cantRegistrosArchivo = cantRegistrosArchivo - BUFFER_LEC_ESC_SORT;
                                                        }
                                                        lec = 0;
                                                }

                                                tamHeap = this->tamBufOrd;
                                                string filename = PATH_PARTICION + IntToStr(nroPart);
                                                partNro[nroPart].open(filename.c_str(),ios::out | ios::binary);
                                                this->myheapsort(bufferSort,tamHeap);
                                        }
                                        else
                                        {
                                                this->myheapsort(bufferSort,tamHeap);

                                                if (lec == BUFFER_LEC_ESC_SORT) {
                                                        if (cantRegistrosArchivo < BUFFER_LEC_ESC_SORT){
                                                                this->cargaBufferLectura(arch,bufferLectura,cantRegistrosArchivo);
                                                                cantRegistrosArchivo = 0;
                                                        }
                                                        else
                                                        {
                                                                this->cargaBufferLectura(arch,bufferLectura,BUFFER_LEC_ESC_SORT);
                                                                cantRegistrosArchivo = cantRegistrosArchivo - BUFFER_LEC_ESC_SORT;
                                                        }
                                                        lec = 0;
                                                }
                                         }
                                   }
                                }

                                arch->close();

                                if (tamHeap < this->tamBufOrd)
                                    tamUltHeap = ((this->tamBufOrd) - tamHeap);
                                else
                                    tamUltHeap = this->tamBufOrd;

                                this->grabarBufferEscritura(&(partNro[nroPart]),bufferEscritura,esc);
                                esc = 0;

                                this->achicarMonticulo(bufferSort,tamHeap,&(partNro[nroPart]));

                                nroPart++;
                                string filename = PATH_PARTICION + IntToStr(nroPart);
                                partNro[nroPart].open(filename.c_str(),ios::out | ios::binary);

                                tReg *bufferUltHeap = new tReg [tamUltHeap];

                                this->correrBuffer(bufferUltHeap,bufferSort,tamUltHeap);
                                this->myheapsort(bufferUltHeap,tamUltHeap);
                                this->achicarMonticulo(bufferUltHeap,tamUltHeap,&(partNro[nroPart]));

                informes << "Cantidad de particiones generadas:  " << nroPart+1 << endl;

                                delete []bufferSort;
                                delete []bufferUltHeap;
                                delete []partNro;
                                delete []bufferLectura;
                                delete []bufferEscritura;
                                informes.close();
                        }
                }
        return nroPart + 1;
 }
