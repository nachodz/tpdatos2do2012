
#include "Aleatorizador.h"


Aleatorizador::Aleatorizador() {
	// TODO Auto-generated constructor stub

}

Aleatorizador::~Aleatorizador() {
	// TODO Auto-generated destructor stub
}

void Aleatorizador::aleatorizarArchivo() {

	srand(time(NULL));

	int i = 0, cantRegistros = 0;

	ifstream diccionarioNormalizado(PATH_ARCHIVO_NORMALIZADO);

	ofstream binario(PATH_ARCHIVO_A_ALEATORIZAR,ios::binary);

	registroNormalizado *bufferEscritura = new registroNormalizado[TAM_BUFFER_LECT_ESC], registro;

	cout<< MSJ_PROCESANDO <<endl;

	if(diccionarioNormalizado && binario){

		diccionarioNormalizado>>registro.termino;

		while (!diccionarioNormalizado.eof()) {

			while ((i < TAM_BUFFER_LECT_ESC) && (!diccionarioNormalizado.eof())) {

				registro.ID = 100000000+rand()%(200000001);
				bufferEscritura[i] = registro;
				diccionarioNormalizado>>registro.termino;
				i++;
			}

			if (i == TAM_BUFFER_LECT_ESC) {

					binario.write((char*)bufferEscritura,(sizeof(registroNormalizado) * TAM_BUFFER_LECT_ESC));
					cantRegistros = cantRegistros + TAM_BUFFER_LECT_ESC;
			}
			else
			{
					binario.write((char*)bufferEscritura,(sizeof(registroNormalizado) * i));
					cantRegistros = cantRegistros + i;
			}
			i = 0;
		}

		delete[] bufferEscritura;
		diccionarioNormalizado.close();
		binario.close();
		this->generarAchivoTabulado(cantRegistros);
		ifstream archivoAordenar(PATH_ARCHIVO_A_ALEATORIZAR,ios::binary);
		this->sortExterno(&archivoAordenar,cantRegistros);
		cout<<"Archivo aleatorizado correctamente"<<endl;
	}
	else
		cout<<"Error al aleatorizar el archivo";
}

void Aleatorizador::generarAchivoTabulado(int cantRegistros) {

	ifstream entrada(PATH_ARCHIVO_A_ALEATORIZAR, ios::binary);
	ofstream salida(PATH_ARCHIVO_TABULADO);

	int i = 0;

	registroNormalizado *bufferLectura = new registroNormalizado[TAM_BUFFER_LECT_ESC];

	salida<<"DICCIONARIO TABULADO"<<endl;
	salida<<" "<<endl;

	while(cantRegistros >= TAM_BUFFER_LECT_ESC){

		entrada.read((char*)bufferLectura,(sizeof(registroNormalizado) * TAM_BUFFER_LECT_ESC));
		cantRegistros = cantRegistros - TAM_BUFFER_LECT_ESC;

		while (i < TAM_BUFFER_LECT_ESC) {

			salida << bufferLectura[i].ID << "  " << bufferLectura[i].termino << endl;
			i++;
	 	}

		i = 0;
	}

	if (cantRegistros != 0) {

		entrada.read((char*)bufferLectura,(sizeof(registroNormalizado) * cantRegistros));

		for (int j=0; j<cantRegistros; j++) {
			salida << bufferLectura[j].ID << "  " << bufferLectura[j].termino << endl;
		}
	}

	delete[] bufferLectura;
}

void Aleatorizador::sortExterno(ifstream *archivoAordenar ,int cantRegistros) {

	int particiones;

	mkdir(DIRECTORIO_PARTICIONES, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	Ordenador unOrdenador(BUFFER_LEC_ESC_SORT);

	particiones = unOrdenador.ordenar(archivoAordenar, cantRegistros);

	string* paths = new string[particiones];
	string raiz = "Particiones/particion";

	for (int i = 0; i < particiones; i++) {

		paths[i] = raiz + intToStr(i);

	}

	Fusionador unFusionador(paths,REGISTROS_POR_BUFFER,particiones);

	unFusionador.merge();

}

string Aleatorizador::intToStr(int n) {

	stringstream result;
	result << n;
	return result.str();
}

//TODO: SACAR!. Método que agrego para llamar al Merge!
void Aleatorizador::merge(int cantRegistros){

	string paths[cantRegistros];

	for(int i=0; i < cantRegistros; i++){
			paths[i] = "Particiones/particion" + intToStr(i);
	}

	Fusionador* unFusionador = new Fusionador(paths, 50, cantRegistros);

	unFusionador->merge();

	cout<<"TODO: Realizo merge"<<endl;
}
