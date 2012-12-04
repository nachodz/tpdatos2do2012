
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>

#include "Ordenador/Ordenador.h"
#include "Booleano.h"
#include "ArbolBMas/ArbolBMas.h"
#include "Gamma/CodigoGamma.h"
#include <bitset>



using namespace std;

int main() {

//   ifstream frases (PATH_ARCHIVO_FRASES,ios::binary);
//
//   Booleano indice;

//   indice.armarIndice();

//   indice.agregar_frase("el dinero es como los perros y tiene mucha falsedad",59);

//   list <int>listaDocs;
//   int nroBloque;

//   indice.alta("serio",28);
//
//   if (indice.obtenerListaIdT("serio",&listaDocs,&nroBloque)){
//        list <int>::iterator it;
//      for (it = listaDocs.begin(); it != listaDocs.end(); it++){
//         cout << *it << endl;
//        }
//       } else cout << "El termino no esta Indexado" << endl;

//   indice.baja("serio",29);
//
//   if (indice.obtenerListaIdT("serio",&listaDocs,&nroBloque)){
//     list <int>::iterator it;
//   for (it = listaDocs.begin(); it != listaDocs.end(); it++){
//      cout << *it << endl;
//     }
//    } else cout << "El termino no esta Indexado" << endl;
//
//   indice.~Booleano();

//	Booleano indice;
//    string lista;
//    int offsetEnBloque;
//	if ( indice.buscarEnBloque(8,1,&lista,&offsetEnBloque) ){
//		cout << offsetEnBloque << endl;
//	}
//	ifstream invertidas (PATH_ARCHIVO_INVERTIDAS,ios::binary | ios::in );
//
//    int offsetArch = 1*TAMANIO_BLOQUE_LISTAS_INV + offsetEnBloque;
//	invertidas.seekg(offsetArch,ios::beg);
//	unsigned short int idT;
//	invertidas.read((char*)&idT,sizeof(idT));
//	cout << (int)idT << endl;
//
//	indice.~Booleano();

//	fstream archivoT (PATH_ARCHIVO_TERMINOS,ios::binary | ios::out| ios::in);
//	Booleano indice;
//	int id;
//	bool encontrado;
//	indice.terminoEncontrado("dinero",&id,&encontrado);
//
//		if (encontrado) {
//			cout << "lo encontro" << endl;
//		}
//	      else
//	        cout << "no lo encontro" << endl;


//	Booleano indice;
//	Ordenador* unOrdenador = new Ordenador(indice.cant_registros_ocurrencias());
//	ifstream archivoOcur (PATH_ARCHIVO_OCURRENCIAS,ios::binary | ios::in);
//
//	cout << unOrdenador->ordenar(&archivoOcur) << endl;
//
//	delete unOrdenador;

//	    RegOcurrencia reg;
//		ifstream archivoOcur ("particion0",ios::binary | ios::in);
//		archivoOcur.read((char*)&reg,sizeof(reg));
//		int cont = 0;
//		while (!archivoOcur.eof()) {
//
//			cout << "" << endl;
//			cout << "idTermino: " << reg.idTer << endl;
//			cout << "idDocumento: " << reg.idDoc << endl;
//			archivoOcur.read((char*)&reg,sizeof(reg));
//			cont++;
//	}
//
//		cout << cont << endl;

//	CodigoGamma gamma;               /*11111001001111100011111110001011111000011111100000111101111111011011110101111101001111001111110010111100011111000011101111101011100111100011011100100 000*/
//	string EnBits = gamma.stringABits("11111001001111100011111110001011111000011111100000111101111111011011110101111101001111001111110010111100011111000011101111101011100111100011011100100");
//	cout << EnBits << endl;
//	string EnBytes = gamma.convertirAString(strdup (EnBits.c_str()));
//	cout << EnBytes << endl;

//	Booleano indice;
//	indice.armarIndice();
//	indice.~Booleano();
//
//	ifstream invertidas (PATH_ARCHIVO_INVERTIDAS,ios::binary | ios::in );
//	char *bloque = new char[TAMANIO_BLOQUE_LISTAS_INV];
//	invertidas.read(bloque,TAMANIO_BLOQUE_LISTAS_INV);
//
//		for (int i = 0; i < TAMANIO_BLOQUE_LISTAS_INV; i++){
//			cout << (int)bloque[i] << endl;
//		}
//		unsigned char libre = (unsigned char)bloque[0];
//
//		delete []bloque;
//
//	    char *bloqueLec = new char[TAMANIO_BLOQUE_LISTAS_INV];
//
//		invertidas.read(bloqueLec,TAMANIO_BLOQUE_LISTAS_INV);
//
//		int j = 0;
//
//		unsigned short int idT;
//		unsigned char longLista;
//
//    while (j < TAMANIO_BLOQUE_LISTAS_INV - libre){
//
//		memmove (&idT,&bloqueLec[j],sizeof (idT));
//		j += sizeof (idT);
//
//		cout << (int)idT << endl;
//
//		memmove (&longLista,&bloqueLec[j],sizeof (longLista));
//		j += sizeof (longLista);
//
//		cout << (int)longLista << endl;
//
//		char *lista = new char[longLista];
//
//		memmove (lista,&bloqueLec[j],longLista);
//
//		j += longLista;
//
//		CodigoGamma gamma;
//		string listaEnBytes = gamma.convertirAString(strdup(string(lista).substr(0,longLista).c_str()));
//
//		cout << listaEnBytes.size() << endl;
//
//		list <int> listaDocs = gamma.decodificarLista(listaEnBytes);
//		list <int>::iterator it;
//		it = listaDocs.begin();
//		while ( it != listaDocs.end() ){
//		        	 cout << *it << endl;
//		        	 it++;
//		         }
//
//		delete []lista;
//     }
//        invertidas.close();
//        delete []bloqueLec;

	return 0;
}
