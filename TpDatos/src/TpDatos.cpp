#include <iostream>
#include <fstream>
#include "Normalizador.h"
#include "RegistroNormalizado.h"
#include "Constantes.h"
#include <stdio.h>
#include <stdlib.h>
#include "Aleatorizador.h"

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
					cout << "TODO: " << MD_OP1 << endl;
					char ruta[256];
					cout<<"Ingrese ruta del archivo diccionario";
					cin>>ruta;
					Normalizador unNormalizador;
					unNormalizador.normalizarArchivo(ruta);
					unNormalizador.~Normalizador();
			}
			break;

			case 2: {
					cout << "TODO: " << MD_OP2 << endl;
					char ruta[256];
					cout<<"Ingrese ruta del archivo normalizado";
					cin>>ruta;
					Aleatorizador unAleatorizador;
					unAleatorizador.aleatorizarArchivo(ruta);
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

	while(ejecutando){

		cout << " " << endl;
		cout << MA << endl;
		cout << INGRESO << endl;
		cout << MA_OP1 << endl;
		cout << MA_OP2 << endl;
		cout << "3) " << SALIR << endl;

		cin >> op;

		while(op<1 || op>3){
			cout<< ERR_RANGO << INF_ERR_RANGO << op << endl;
			cout << INGRESO << endl;
			cin>> op;
		}

		switch(op){
			case 1: cout << "TODO: " << MA_OP1 << endl;break;
			case 2: cout << "TODO: " << MA_OP2 << endl;break;
			case 3: ejecutando = false;break;
			default: /*no hago nada*/;break;
		}
	}
}

void menuOperacionesDispersionExtensible(){

	int op;
	bool ejecutando = true;

	while(ejecutando){

		cout << " " << endl;
		cout << MDE << endl;
		cout << INGRESO << endl;
		cout << MDE_OP1 << endl;
		cout << MDE_OP2 << endl;
		cout << MDE_OP3 << endl;
		cout << MDE_OP4 << endl;
		cout << "5) " << SALIR << endl;

		cin >> op;

		while(op<1 || op>5){
			cout<< ERR_RANGO << INF_ERR_RANGO << op << endl;
			cout << INGRESO << endl;
			cin>> op;
		}

		switch(op){
			case 1: cout << "TODO: " << MDE_OP1 << endl;break;
			case 2: cout << "TODO: " << MDE_OP2 << endl;break;
			case 3: cout << "TODO: " << MDE_OP3 << endl;break;
			case 4: cout << "TODO: " << MDE_OP4 << endl;break;
			case 5: ejecutando = false;break;
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
		cout << MOAA_OP3 << endl;
		cout << "4) " << SALIR << endl;

		cin >> op;

		while(op<1 || op>4){
			cout<< ERR_RANGO << INF_ERR_RANGO << op << endl;
			cout << INGRESO << endl;
			cin>> op;
		}

		switch(op){
			case 1: cout << "TODO: " << MOAA_OP1 << endl;break;
			case 2: menuOperacionesArbol();break;
			case 3: menuOperacionesDispersionExtensible();break;
			case 4: ejecutando = false;break;
			default: /*no hago nada*/;break;
		}
	}
}

void menuComponenteEstadisticas(){

	int op;
	bool ejecutando = true;

	while(ejecutando){

		cout << " " << endl;
		cout << MCE << endl;
		cout << INGRESO << endl;
		cout << MCE_OP1 << endl;
		cout << MCE_OP2 << endl;
		cout << MCE_OP3 << endl;
		cout << MCE_OP4 << endl;
		cout << "5) " << SALIR << endl;

		cin >> op;

		while(op<1 || op>5){
			cout<< ERR_RANGO << INF_ERR_RANGO << op << endl;
			cout << INGRESO << endl;
			cin>> op;
		}

		switch(op){
			case 1: cout << "TODO: " << MCE_OP1 << endl;break;
			case 2: cout << "TODO: " << MCE_OP2 << endl;break;
			case 3: cout << "TODO: " << MCE_OP3 << endl;break;
			case 4: cout << "TODO: " << MCE_OP4 << endl;break;
			case 5: ejecutando = false;break;
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
