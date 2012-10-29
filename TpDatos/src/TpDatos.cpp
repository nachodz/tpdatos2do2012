
#include <iostream>
#include <fstream>
#include "Constantes.h"
#include <stdio.h>
#include <stdlib.h>
#include "Aleatorizador/Aleatorizador.h"
#include "Normalizador/Normalizador.h"
#include "Estadisticas/Estadisticas.h"
#include "Hash/Hash.h"
#include "Hash/Autor.h"
#include "ArbolBMas/ArbolBMas.h"
#include <sys/stat.h>
#include <sys/types.h>


using namespace std;

void menuDiccionario(){

	int op;
	bool ejecutando = true;

	while(ejecutando){

		cout << " " << endl;
		cout << MD << endl;
		cout << INGRESO << endl;
		cout << MD_OP1 << endl;
		cout << MD_OP2 << endl;
		cout << "3) " << SALIR << endl;

		cin >> op;

		while(op<1 || op>3){
			cout<< ERR_RANGO << INF_ERR_RANGO << op << endl;
			cout << INGRESO << endl;
			cin>> op;
		}

		switch(op){
			case 1: {
					Normalizador unNormalizador;
					unNormalizador.normalizarArchivo();
					unNormalizador.~Normalizador();
			}
			break;

			case 2: {
					Aleatorizador unAleatorizador;
					unAleatorizador.aleatorizarArchivo();
					unAleatorizador.~Aleatorizador();
			}
			break;

			case 3: ejecutando = false;break;

			default: /*no hago nada*/;break;
		}
	}
}

void menuOperacionesArbol(){

	int op;
	bool ejecutando = true;

	ArbolBMas* arbol = new ArbolBMas(PATH_ARBOL);

	while(ejecutando){

		cout << " " << endl;
		cout << MA << endl;
		cout << INGRESO << endl;
		cout << MA_OP1 << endl;
		cout << MA_OP2 << endl;
		cout << MA_OP3 << endl;
		cout << MA_OP4 << endl;
		cout << "5) " << SALIR << endl;

		cin >> op;

		while(op<1 || op>5){
			cout<< ERR_RANGO << INF_ERR_RANGO << op << endl;
			cout << INGRESO << endl;
			cin>> op;
		}

		switch(op){
			case 1: {
				cout << ARBOLBMAS_CARGAINICIAL << endl;
				cout << MSJ_PROCESANDO << endl;
				int registros;
				ifstream metadata;
				metadata.open(PATH_METADATA, ios::binary);
				metadata.read((char*)&registros,sizeof(int));
				arbol->cargaInicial(registros);
				remove(PATH_METADATA);
				cout << ARBOLBMAS_CARGAINICIALOK << endl;
				break;
			}
			case 2: {
				string termino;

				cout << ARBOLBMAS_INGRESARTERMINO << endl;
				cin >> termino;

				Clave* clave = new Clave(termino);
				Elementos* elemento = arbol->buscar(clave);

				cout << ARBOLBMAS_INFORMETERMINO << endl;
				cout << elemento->toString() << endl;

				break;
			}
			case 3: {
				cout << ARBOLBMAS_LISTARENPREORDEN << endl;
				arbol->mostrar();
				cout << ARBOLBMAS_LISTARENPREORDENOK << endl;
				break;
			}
			case 4: {
				cout << ARBOLBMAS_LISTARTODOSTERMINOS << endl;
				arbol->mostrarTodosTerminos();
				cout << ARBOLBMAS_LISTARTODOSTERMINOSOK << endl;
				break;
			}
			case 5: ejecutando = false;break;
			default: /*no hago nada*/;break;
		}
	}
}

void menuOperacionesDispersionExtensible(){

	int op;
	bool ejecutando = true;

	Hash hash(HASH_NOM_BLOQUES, HASH_NOM_ESP_LIBRE, HASH_NOM_TABLA);

	while(ejecutando){

		cout << " " << endl;
		cout << MDE << endl;
		cout << INGRESO << endl;
		cout << MDE_OP1 << endl;
		cout << MDE_OP2 << endl;
		cout << MDE_OP3 << endl;
		cout << MDE_OP4 << endl;
		cout << MDE_OP5 << endl;
		cout << "6) " << SALIR << endl;

		cin >> op;

		while(op<1 || op>6){
			cout<< ERR_RANGO << INF_ERR_RANGO << op << endl;
			cout << INGRESO << endl;
			cin>> op;
		}

		switch(op){
			case 1: {
				cout << HASH_CARGAINICIALCOMIENZO << endl;
				cout << MSJ_PROCESANDO << endl;
				hash.cargaInicial();
				cout << HASH_CARGAINICIALOK << endl;
				break;
			}
			case 2: {
				string nombreAutor = "";
				string apellidoAutor = "";
				string frase;
				Autor* autor;
				int op2,op3;
				int n;

				cout << HASH_INGRESARN << endl;
				cin >> n;

				cout << HASH_OPCIONINGRESARAUTOR << endl;
				cin >> op2;

				while(op2<1 || op2>2){
					cout<< ERR_RANGO << INF_ERR_RANGO << op2 << endl;
					cout << INGRESO << endl;
					cin>> op2;
				}

				if (op2 == 1){
					cout << HASH_INGRESARAPEAUTOR << endl;
					cin >> apellidoAutor;

					cout << HASH_OPCIONINGRESARNOMAUTOR << endl;
					cin >> op3;

					while(op3<1 || op3>2){
						cout<< ERR_RANGO << INF_ERR_RANGO << op3 << endl;
						cout << INGRESO << endl;
						cin>> op3;
					}

					if (op3 == 1){
						cout << HASH_INGRESARNOMAUTOR << endl;
						cin >> nombreAutor;
					}
				}
				autor = new Autor(apellidoAutor,nombreAutor);

				cout << HASH_INGRESARFRASE << endl;
				cin >> frase;

				hash.alta(n,autor,frase);

				cout << HASH_ALTAOK << endl;
				break;
			}
			case 3: {
				string nombreAutor, apellidoAutor, frase;
				int n;

				cout << HASH_INGRESARN << endl;
				cin >> n;

				hash.baja(n);

				cout << HASH_BAJAOK << endl;
				break;
			}
			case 4: {
				string nombreAutor2 = "";
				string apellidoAutor2 = "";
				string frase2;
				Autor* autor;
				int n2,op4,op5;

				cout << HASH_INGRESARN << endl;
				cin >> n2;
				cout << HASH_OPCIONINGRESARAUTOR << endl;
				cin >> op4;

				while(op4<1 || op4>2){
					cout<< ERR_RANGO << INF_ERR_RANGO << op4 << endl;
					cout << INGRESO << endl;
					cin>> op4;
				}

				if (op4 == 1){
					cout << HASH_INGRESARAPEAUTOR << endl;
					cin >> apellidoAutor2;

					cout << HASH_OPCIONINGRESARNOMAUTOR << endl;
					cin >> op5;

					while(op5<1 || op5>2){
						cout<< ERR_RANGO << INF_ERR_RANGO << op5 << endl;
						cout << INGRESO << endl;
						cin>> op5;
					}

					if (op5 == 1){
						cout << HASH_INGRESARNOMAUTOR << endl;
						cin >> nombreAutor2;
					}
				}

				autor = new Autor(apellidoAutor2,nombreAutor2);

				cout << HASH_INGRESARFRASE << endl;
				cin >> frase2;

				hash.modificar(n2,autor,frase2);

				cout << HASH_MODIFICAROK << endl;
				break;
			}
			case 5: {
				hash.mostrar(HASH_NOM_SALIDA);
				cout << HASH_SALIDAOK << endl;
				break;
			}
			case 6: ejecutando = false;break;
			default: /*no hago nada*/;break;
		}
	}
}

void menuOrganizacionArchivo(){

	int op;
	bool ejecutando = true;

	while(ejecutando){

		cout << " " << endl;
		cout << MOAA << endl;
		cout << INGRESO << endl;
		cout << MOAA_OP1 << endl;
		cout << MOAA_OP2 << endl;
		cout << "3) " << SALIR << endl;

		cin >> op;

		while(op<1 || op>3){
			cout<< ERR_RANGO << INF_ERR_RANGO << op << endl;
			cout << INGRESO << endl;
			cin>> op;
		}

		switch(op){
			case 1: menuOperacionesArbol();break;
			case 2: menuOperacionesDispersionExtensible();break;
			case 3: ejecutando = false;break;
			default: /*no hago nada*/;break;
		}
	}
}

void menuComponenteEstadisticas(){

	int op;
	bool ejecutando = true;

	Estadisticas* estadistico = new Estadisticas();
	ArbolBMas* arbol = new ArbolBMas(PATH_ARBOL);
	Hash hash(HASH_NOM_BLOQUES, HASH_NOM_ESP_LIBRE, HASH_NOM_TABLA);
	int n;

	while(ejecutando){

		cout << " " << endl;
		cout << MCE << endl;
		cout << INGRESO << endl;
		cout << MCE_OP1 << endl;
		cout << MCE_OP2 << endl;
		cout << MCE_OP3 << endl;
		cout << MCE_OP4 << endl;
		cout << MCE_OP5 << endl;
		cout << "6) " << SALIR << endl;

		cin >> op;

		while(op<1 || op>6){
			cout<< ERR_RANGO << INF_ERR_RANGO << op << endl;
			cout << INGRESO << endl;
			cin>> op;
		}

		switch(op){
			case 1: {
				cout << ESTADISTICO_CARGAINICIALCOMIENZO << endl;
				cout << MSJ_PROCESANDO << endl;
				estadistico->cargaInicial(hash,arbol);
				cout << ESTADISTICO_CARGAINICIALOK << endl;
				break;
			}
			case 2: {
				cout << ESTADISTICO_TERMINOSPROMPORFRASE << endl;
				cout << estadistico->terminos_prom_frase() << endl;
				break;
			}
			case 3: {
				cout << ESTADISTICO_TASAFALLOS << endl;
				cout << estadistico->tasa_fallo_terminos() << endl;
				break;
			}
			case 4: {
				cout << ESTADISTICO_LISTATERMINOSNOENCONTRADOS << endl;
				cout << "El listado se ha generado en un archivo de texto." << endl;
				break;
			}
			case 5: {
				cout << ESTADISTICO_INGRESARN << endl;
				cin >> n;
				cout << ESTADISTICO_RANKING << endl;
				estadistico->listar_ranking(n);
				break;
			}
			case 6: ejecutando = false;break;
			default: /*no hago nada*/;break;
		}
	}
}

int main() {

	int op;
	bool ejecutando = true;

	while(ejecutando){

		cout << " " << endl;
		cout << MP << endl;
		cout << INGRESO << endl;
		cout << MP_OP1 << endl;
		cout << MP_OP2 << endl;
		cout << MP_OP3 << endl;
		cout << "4) " << SALIR << endl;

		cin >> op;

		while(op<1 || op>4){
			cout<< ERR_RANGO << INF_ERR_RANGO << op << endl;
			cout << INGRESO << endl;
			cin>> op;
		}

		switch(op){
			case 1: menuDiccionario();break;
			case 2: menuOrganizacionArchivo();break;
			case 3: menuComponenteEstadisticas();break;
			case 4: ejecutando = false;break;
			default: /*no hago nada*/;break;
		}

	}

	return 0;
}
