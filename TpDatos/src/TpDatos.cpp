
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
#include "Booleano/Booleano.h"
#include "DiccionarioFrases/DiccionarioFrases.h"
#include "IdxFirmas/indice.h"
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

void menuTp1(){

	int op;
	bool ejecutando = true;

	while(ejecutando){
		cout << " " << endl;
		cout << MPTP1_TIT << endl;
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

}

void menuIdxBooleano(){
	int op;
	bool ejecutando = true;

	Booleano indice;
	DiccionarioFrases dicc;
	indice.armarIndice();

	cout << IDX_BOOLEANO_CREACION << endl;

	while(ejecutando){
		cout << " " << endl;
		cout << IDX_BOOLEANO_TIT << endl;
		cout << INGRESO << endl;
		cout << IDX_BOOLEANO_ALTA_FRASE << endl;
		cout << IDX_BOOLEANO_BAJA_FRASE << endl;
		cout << IDX_BOOLEANO_MODIFICACION_FRASE << endl;
		cout << IDX_BOOLEANO_BUSQUEDA_FRASE << endl;
		cout << "5) " << SALIR << endl;

		cin >> op;
		cin.ignore();

		while(op<1 || op>5){
			cout<< ERR_RANGO << INF_ERR_RANGO << op << endl;
			cout << INGRESO << endl;
			cin>> op;
			cin.ignore();
		}

		switch(op){
			case 1: {
				cout << IDX_BOOLEANO_ALTA << endl;

				string frase;

				cout << IDX_BOOLEANO_ALTA_OPCION << endl;

				//cin.ignore();
				getline(cin,frase);

				DiccionarioFrases dicc;
				int nroDocumento = dicc.alta(frase);
				indice.agregar_frase(frase,nroDocumento);

				cout << IDX_BOOLEANO_ALTA_OK << endl;
				break;
			}
			case 2: {
				cout << IDX_BOOLEANO_BAJA << endl;

				int registro;
				DiccionarioFrases dicc;

				cout << IDX_BOOLEANO_BAJA_OPCION<< endl;
				cout << " " << endl;
				cin >> registro;
				cin.ignore();

				while(registro >= TAMANIO_REGISTRO_FRASES-1) {
					cout << IDX_BOOLEANO_BAJA_ERROR << endl;
					cout << " " << endl;
					cin >> registro;
					cin.ignore();
				}
				string fraseBaja = dicc.baja(registro);
				if ( fraseBaja != " " ){
					indice.quitar_frase(registro,fraseBaja);
					cout << IDX_BOOLEANO_BAJA_OK << endl;
				}
//				indice.quitar_frase(registro);
//				dicc.baja(registro);
//                cout << IDX_BOOLEANO_BAJA_OK << endl;
				break;
			}
			case 3:{
				int nroReg;
                string frase;

                cout << IDX_BOOLEANO_MODIFICACION << endl;

				cout << IDX_BOOLEANO_MODIFICACION_OPCION1 << endl;

                cin >> nroReg;

                cout << IDX_BOOLEANO_MODIFICACION_OPCION2 << endl;

				//cin.ignore();
				getline (cin,frase);
				dicc.modificacion(nroReg,frase,&indice);
		       break;
			}
			case 4: {
				int cantTerm;

				cout << IDX_BOOLEANO_BUSQUEDA << endl;

				cout << IDX_BOOLEANO_BUSQUEDA_OPCION << endl;
				cin >> cantTerm;
				string *terminos = new string [cantTerm];

				for (int i = 0; i < cantTerm; i++){
				  cout << "Ingrese el termino " <<  (i + 1) << " : " << endl;
				  cin >> terminos[i];
				}

				indice.buscarListaTerminos(terminos,cantTerm);

				break;
			}
			case 5: ejecutando = false;break;
			default: /*no hago nada*/;break;
		}
	}
	//indice.~Booleano();

}

void menuIdxPorcionesFirmas(){

	int op;
	bool ejecutando = true;

	DiccionarioFrases dicc;
	indice *indiceFirmas = new indice(PATH_ARBOL,PATH_TERMINOS,PATH_OCURRENCIAS,PATH_FIRMAS,TAM_PORCION);
	indiceFirmas->recuperarInformacion();

	while(ejecutando){
		cout << " " << endl;
		cout << IDX_FIRMAS_TIT << endl;
		cout << INGRESO << endl;
		cout << IDX_FIRMAS_CARGA_INICIAL << endl;
		cout << IDX_FIRMAS_ALTA_FRASE << endl;
		cout << IDX_FIRMAS_BAJA_FRASE << endl;
		cout << IDX_FIRMAS_MODIFICACION_FRASE << endl;
		cout << IDX_FIRMAS_BUSQUEDA_PALABRAS_FRASE << endl;
		cout << IDX_FIRMAS_MOSTRAR_FRASES << endl;
		cout << IDX_FIRMAS_MOSTRAR_FIRMA_TERMINO << endl;
		cout << "8) " << SALIR << endl;

		cin >> op;
		cin.ignore();

		while(op<1 || op>8){
			cout<< ERR_RANGO << INF_ERR_RANGO << op << endl;
			cout << INGRESO << endl;
			cin>> op;
			cin.ignore();
		}

		switch(op){
			case 1: {
				cout << IDX_FIRMAS_CARGA_INI << endl;
				ifstream arch;
				arch.open(PATH_INDICE,ios::binary);
				if(!arch){
					indiceFirmas->cargaInicialIndice(PATH_ARCHIVO_FRASES);
					indiceFirmas->guardarInformacion();
					cout << IDX_FIRMAS_CARGA_INI_OK << endl;
				}
				else
					cout << "El indice ya esta cargado" << endl;
				break;
			}
			case 2: {
				cout << IDX_FIRMAS_ALTA << endl;

				string frase;

				cout << IDX_FIRMAS_ALTA_OPCION << endl;

				getline(cin,frase);

				int registro = dicc.alta(frase);
				if (registro != -1) {
					indiceFirmas->agregarTerminosAlIndice(frase,registro);
					indiceFirmas->guardarInformacion();
					cout << IDX_FIRMAS_ALTA_OK << endl;
				}
				else
					cout << "La carga no se pudo realizar" << endl;
				break;
			}
			case 3: {
				cout << IDX_FIRMAS_BAJA << endl;

				cout << IDX_FIRMAS_BAJA_OPCION1 << endl;
				cout << IDX_FIRMAS_BAJA_OPCION2 << endl;

				int registro;
				cin >> registro;
				cin.ignore();
				string frase = dicc.baja(registro);
				if (frase != " ") {
					indiceFirmas->eliminarTerminosDelIndice(frase,registro);
					cout << "Baja realizada con exito" << endl;
					indiceFirmas->guardarInformacion();
					cout << IDX_FIRMAS_BAJA_OK << endl;
				}
				else
					cout << "La frase ya esta dada de baja o no se pudo realizar la accion" << endl;

				break;
			}
			case 4:{
				int nroReg;

                string frase;

                cout << IDX_FIRMAS_MODIFICACION << endl;

				cout << IDX_FIRMAS_MODIFICACION_OPCION1 << endl;
				cout << IDX_FIRMAS_MODIFICACION_OPCION2 << endl;

                cin >> nroReg;

    			mapaBits *mapa = new mapaBits(TAMANIO_REGISTRO_FRASES*BYTE);
    			char *serial = new char[TAMANIO_REGISTRO_FRASES];
    			fstream frases;
    			frases.open(PATH_ARCHIVO_FRASES, ios::binary|ios::in|ios::out);

    			if ((mapa)&&(serial)&&(frases)) {

						frases.read(serial,TAMANIO_REGISTRO_FRASES);
						mapa->hidratar(serial);

						if (!mapa->libre(nroReg)){
							cout << IDX_FIRMAS_MODIFICACION_OPCION3 << endl;
				        	cin.ignore();
							getline (cin,frase);
							dicc.modificacionFirmas(nroReg,frase,indiceFirmas);
							cout << IDX_FIRMAS_MODIFICACION_OK << endl;
						}
						else
							cout << "El registro a modificar esta libre" << endl;
    			}
    			else
    				cout << "El archivo de frases no pudo ser abierto, o el programa no encuentra memoria disponible" << endl;
    			break;
			}
			case 5:{
				cout << IDX_FIRMAS_BUSQUEDA_PALABRAS << endl;

				cout << IDX_FIRMAS_BUSQUEDA_PALABRAS_OPCION << endl;

				string palabras;
				getline(cin,palabras);
				if (!palabras.length()>0)
					cout << "No ingrego terminos para buscar" << endl;
				else {
					indiceFirmas->buscarFrases(palabras);
					cout << IDX_FIRMAS_BUSQUEDA_PALABRAS_OK << endl;
				}
				indiceFirmas->guardarInformacion();
				break;
			}
			case 6: {
				cout << IDX_FIRMAS_MOSTRAR_FRASES_TIT << endl;

				dicc.listarEnTexto();

				break;
			}
			case 7: {

				cout << IDX_FIRMAS_MOSTRAR_FIRMA << endl;

				cout << IDX_FIRMAS_MOSTRAR_FIRMA_TERMINOS_OPCION << endl;

				string palabra;
				cin >> palabra;
				cin.ignore();
				if (indiceFirmas->mostrarFirma(palabra))
					cout << IDX_FIRMAS_MOSTRAR_FIRMA_TERMINOS_OK << endl;
				else
					cout << "El termino no se encuentra indexado" << endl;
				;break;
			}
			case 8: ejecutando = false;break;
			default: /*no hago nada*/;break;
		}
	}

}

void menuDiccFrases(){

	int op;
	bool ejecutando = true;

	DiccionarioFrases dicc;

	while(ejecutando){
		cout << " " << endl;
		cout << DICC_FRASES_TIT << endl;
		cout << INGRESO << endl;
		cout << DICC_FRASES_CARGA_INICIAL << endl;
		cout << DICC_FRASES_ALTA << endl;
		cout << DICC_FRASES_BAJA << endl;
		cout << DICC_FRASES_MOSTRAR << endl;
		cout << "5) " << SALIR << endl;

		cin >> op;
		cin.ignore();

		while(op<1 || op>5){
			cout<< ERR_RANGO << INF_ERR_RANGO << op << endl;
			cout << INGRESO << endl;
			cin>> op;
			cin.ignore();
		}

		switch(op){
			case 1: {
				cout << DICC_FRASES_CARGA_INI << endl;

				int archivoCreado = dicc.crearArchivoFrases();
				if (archivoCreado == 0)
					cout << "Archivo de frases creado correctamente" << endl;

				else
					cout << "Error al crear el archivo de frases" << endl;

				int frases;
				cout << " " << endl;
				cout << "Ingrese el numero de frases celebres a importar desde el archivo 'Frases_Celebres.csv'" << endl;
				cout << " " << endl;
				cin >> frases;
				cin.ignore();

				while(frases >= ((TAMANIO_REGISTRO_FRASES-1)*8)) {
					cout << "El numero de frase exede la capacidad total del archivo" << endl;
					cout << " " << endl;
					cin >> frases;
					cin.ignore();
				}

				dicc.cargaInicial(frases);

				cout << DICC_FRASES_CARGA_INI_OK << endl;
				break;
			}
			case 2: {
				cout << DICC_FRASES_ALTA_TIT << endl;

				cout << DICC_FRASES_ALTA_OPCION << endl;

				string frase;
				getline(cin,frase);
				dicc.alta(frase);

				cout << DICC_FRASES_ALTA_OK << endl;
				break;
			}
			case 3: {
				cout << DICC_FRASES_BAJA_TIT << endl;

				cout << DICC_FRASES_BAJA_OPCION << endl;

				int registro;
				cin >> registro;
				cin.ignore();

				while(registro >= ((TAMANIO_REGISTRO_FRASES-1)*8)) {
					cout << "El numero de frase exede la capacidad total del archivo" << endl;
					cout << " " << endl;
					cin >> registro;
					cin.ignore();
				}
				dicc.baja(registro);
				cout << DICC_FRASES_BAJA_OK << endl;
				break;
			}
			case 4:{
				cout << DICC_FRASES_MOSTRAR_TIT << endl;

				dicc.listarEnTexto();

				break;
			}
			case 5: {
				ejecutando = false;break;
			}
			default: /*no hago nada*/;break;
		}
	}
}

void comparacionTamArch(double tiempoB, double tiempoF){

	ifstream archlsB;
	archlsB.open(PATH_ARCHIVO_INVERTIDAS,ios::binary);
	archlsB.seekg(0,ios::end);
	int tamlsB = archlsB.tellg();

	ifstream archterB;
	archterB.open(PATH_ARCHIVO_TERMINOS_BOOLEANO,ios::binary);
	archterB.seekg(0,ios::end);
	int tamterB = archterB.tellg();

	ifstream archfirF;
	archfirF.open(PATH_FIRMAS,ios::binary);
	archfirF.seekg(0,ios::end);
	int tamfirF = archfirF.tellg();

	ifstream archterF;
	archterF.open(PATH_TERMINOS,ios::binary);
	archterF.seekg(0,ios::end);
	int tamterF = archterF.tellg();

	cout << endl;
	cout << "INFORME COMPARATIVO" << endl;
	cout << endl;
	cout << "INDICE BOOLEANO" << endl;
	cout << "Tamaño Archivo Términos: " << tamterB << " bytes" << endl;
	cout << "Tamaño Archivo Listas Invertidas: " << tamlsB << " bytes" << endl;
	cout << "Tiempo de búsqueda: " << tiempoB << " segundos" << endl;
	cout << endl;
	cout << "INDICE PORCIONES DE FIRMAS" << endl;
	cout << "Tamaño Archivo Términos: " << tamterF << " bytes" << endl;
	cout << "Tamaño Archivo de Firmas: " << tamfirF << " bytes" << endl;
	cout << "Tiempo de búsqueda: " << tiempoF << " segundos" << endl;
	cout << endl;

	archlsB.close();
	archterB.close();

	archterF.close();
	archfirF.close();
}

void menuIdxComponenteEstadisticas(){
	int op;
	bool ejecutando = true;

	DiccionarioFrases dicc;

	Booleano idxBooleano;
	idxBooleano.armarIndice();

	indice *indiceFirmas = new indice(PATH_ARBOL,PATH_TERMINOS,PATH_OCURRENCIAS,PATH_FIRMAS,TAM_PORCION);
	indiceFirmas->recuperarInformacion();

	ifstream arch;
	arch.open(PATH_INDICE,ios::binary);
	if(!arch){
		indiceFirmas->cargaInicialIndice(PATH_ARCHIVO_FRASES);
		indiceFirmas->guardarInformacion();
	}

	while(ejecutando){
		cout << " " << endl;
		cout << COMP_ESTAD_TP2_TIT << endl;
		cout << INGRESO << endl;
		cout << COMP_ESTAD_TP2_BUSQ1 << endl;
		cout << COMP_ESTAD_TP2_BUSQ2 << endl;
		cout << COMP_ESTAD_TP2_BUSQ3 << endl;
		cout << "4) " << SALIR << endl;

		cin >> op;
		cin.ignore();

		while(op<1 || op>4){
			cout<< ERR_RANGO << INF_ERR_RANGO << op << endl;
			cout << INGRESO << endl;
			cin>> op;
			cin.ignore();
		}
		// PATH_ARCHIVO_BUSQUEDA resultado booleano
		// PATH_ARCHIVO_INVERTIDAS ls booleano
		// PATH_RESULTADO_BUSQUEDA resultado firmas
		// PATH_FIRMAS firmas firmas
		switch(op){
			case 1: {
				string termino;
				string* terminosArray = new string[1];

				cout << COMP_ESTAD_TP2_BUSQ1_TIT << endl;

				cout << COMP_ESTAD_TP2_BUSQ1_OPCION << endl;

				cin >> termino;

				terminosArray[0] = termino;

				double tiempoF = indiceFirmas->buscarFrases(termino);
				double tiempoB = idxBooleano.buscarListaTerminos(terminosArray,1);

				comparacionTamArch(tiempoB,tiempoF);

				cout << COMP_ESTAD_TP2_BUSQ_OK << endl;
				break;
			}
			case 2: {
				string termino1,termino2,terminos;
				string* terminosArray = new string[2];

				cout << COMP_ESTAD_TP2_BUSQ2_TIT << endl;

				cout << COMP_ESTAD_TP2_BUSQ2_OPCION1 << endl;

				cin >> termino1;

				cout << COMP_ESTAD_TP2_BUSQ2_OPCION2 << endl;

				cin >> termino2;

				terminos = termino1 +" "+ termino2;

				double tiempoF = indiceFirmas->buscarFrases(terminos);

				terminosArray[0] = termino1;
				terminosArray[1] = termino2;

				double tiempoB = idxBooleano.buscarListaTerminos(terminosArray,2);

				comparacionTamArch(tiempoB,tiempoF);

				cout << COMP_ESTAD_TP2_BUSQ_OK << endl;
				break;
			}
			case 3: {
				string termino1,termino2,termino3,terminos;
				string* terminosArray = new string[3];

				cout << COMP_ESTAD_TP2_BUSQ3_TIT << endl;

				cout << COMP_ESTAD_TP2_BUSQ3_OPCION1 << endl;

				cin >> termino1;

				cout << COMP_ESTAD_TP2_BUSQ3_OPCION2 << endl;

				cin >> termino2;

				cout << COMP_ESTAD_TP2_BUSQ3_OPCION3 << endl;

				cin >> termino3;

				terminos = termino1 +" "+ termino2 +" "+ termino3;

				double tiempoF = indiceFirmas->buscarFrases(terminos);

				terminosArray[0] = termino1;
				terminosArray[1] = termino2;
				terminosArray[2] = termino3;

				double tiempoB = idxBooleano.buscarListaTerminos(terminosArray,3);

				comparacionTamArch(tiempoB,tiempoF);

				cout << COMP_ESTAD_TP2_BUSQ_OK << endl;
				break;
			}
			case 4:{
				ejecutando = false;break;
			}
			default: ;break;
		}
	}
}

void menuTp2(){

	int op;
	bool ejecutando = true;

	while(ejecutando){
		cout << " " << endl;
		cout << MPTP2_TIT << endl;
		cout << INGRESO << endl;
		cout << DICC_FRASES << endl;
		cout << IDX_BOOLEANO << endl;
		cout << IDX_PORC_FIRMAS << endl;
		cout << IDX_COMP_ESTAD << endl;
		cout << "5) " << SALIR << endl;

		cin >> op;

		while(op<1 || op>5){
			cout<< ERR_RANGO << INF_ERR_RANGO << op << endl;
			cout << INGRESO << endl;
			cin>> op;
		}

		switch(op){
			case 1: menuDiccFrases();break;
			case 2: menuIdxBooleano();break;
			case 3: menuIdxPorcionesFirmas();break;
			case 4: menuIdxComponenteEstadisticas();break;
			case 5: ejecutando = false;break;
			default: /*no hago nada*/;break;
		}
	}

}

int main() {

	int op;
	bool ejecutando = true;

	while(ejecutando){

		cout << " "<< endl;
		cout << MP << endl;
		cout << INGRESO << endl;
		cout << MPTP1 << endl;
		cout << MPTP2 << endl;
		cout << "3) " << SALIR << endl;

		cin >> op;

		while(op<1 || op>4){
			cout<< ERR_RANGO << INF_ERR_RANGO << op << endl;
			cout << INGRESO << endl;
			cin>> op;
		}

		switch(op){
			case 1: menuTp1();break;
			case 2: menuTp2();break;
			case 3: ejecutando = false;break;
			default: /*no hago nada*/;break;
		}

	}

	return 0;
}
