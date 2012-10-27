
#include "Normalizador.h"



Normalizador::Normalizador(){
	// TODO Auto-generated constructor stub

}

Normalizador::~Normalizador(){
	// TODO Auto-generated destructor stub
}

void Normalizador::normalizarArchivo() {

	ifstream diccionario(PATH_DICCIONARIO), stopwords(PATH_STOPWORDS);

	ofstream diccionarioNormalizado(PATH_ARCHIVO_NORMALIZADO);
	int numeroTerminos = this->numeroTerminos(&stopwords);
	stopwords.close();
	string *vectorStopwords = new string[numeroTerminos];
	string palabraDiccionario, palabraStopword;

	ifstream stopwords2(PATH_STOPWORDS);

	for(int i = 0; i < numeroTerminos; i++) {
		stopwords2 >> vectorStopwords[i];
	}
	stopwords2.close();

	if ((diccionario) && (diccionarioNormalizado) && (vectorStopwords)){

		int j = 0;
		diccionario>>palabraDiccionario;
		this->normalizarPalabra(&palabraDiccionario);
		palabraStopword = vectorStopwords[j];
		j++;

		cout << MSJ_PROCESANDO << endl;

		while (!diccionario.eof()) {

			if ((palabraDiccionario == palabraStopword) && (j < (numeroTerminos-2))) {
				palabraStopword = vectorStopwords[j];
				j++;
			}
			else
			{
				if (this->esMayor(palabraDiccionario,palabraStopword) && (j < numeroTerminos - 1)){
					palabraStopword = vectorStopwords[j];
					j++;
				}
				else
				{
					if (palabraDiccionario != palabraStopword){

						diccionarioNormalizado<<palabraDiccionario<<endl;
					}
				}
			}

			diccionario>>palabraDiccionario;
			this->normalizarPalabra(&palabraDiccionario);
		}

		diccionario.close();
		diccionarioNormalizado.close();
		cout<<"Diccionario normalizado correctamente"<<endl;
	}
	else
		cout<<"error al normalizar el diccionario"<<endl;
}

void Normalizador::normalizarPalabra(string *unaPalabra){
	this->sacarAcentos(unaPalabra);
	this->sacarMayusculas(unaPalabra);
	this->cortarPalabra(unaPalabra);
}


void Normalizador::cortarPalabra(string *unaPalabra){

	if ((unaPalabra->at(0)) == '-'){
		unaPalabra->erase(0,1);
	}
	else
	{
		if ((unaPalabra->at(unaPalabra->size() - 1) == '-')){
			unaPalabra->erase(unaPalabra->size() - 1);
		}
	}
}


void Normalizador::sacarAcentos(string *unaPalabra){
	char letra;
	int tamanioPalabra, posicion = 0;

	tamanioPalabra = ((unaPalabra->size()) - 1);
	while (posicion <= tamanioPalabra){
		letra = unaPalabra->at(posicion);
		this->cambiarLetra(unaPalabra,letra,posicion);
		posicion++;
	}
}


void Normalizador::sacarMayusculas(string *unaPalabra){
	transform(unaPalabra->begin(), unaPalabra->end(), unaPalabra->begin(), (int( * )(int))std::tolower);
}


void Normalizador::cambiarLetra(string *unaPalabra, char L, int pos){
	int ascii = L;
	switch(ascii){
	case(-31): case(-63): unaPalabra->operator [](pos) = 'a';
					break;
	case(-23): case(-55): unaPalabra->operator [](pos) = 'e';
					break;
	case(-19): case(-51): unaPalabra->operator [](pos) = 'i';
					break;
	case(-13): case(-45):unaPalabra->operator [](pos) = 'o';
					break;
	case(-6): case(-4): case(-38): case(-36): unaPalabra->operator [](pos) = 'u';
					break;
	default: break;
	}
}

bool Normalizador::esMayor(string palabra1,string palabra2) {

	char A,B;

	unsigned int i = 0;

	A = palabra1[i];
	B = palabra2[i];
	i++;

	while ((A == B) && (i < palabra1.size()) && (i < palabra2.size())) {

		A = palabra1[i];
		B = palabra2[i];
		i++;
	}

	if (A > B) {
		return true;
	}
	else
	{
		if (B > A) {
			return false;
		}
		else
		{
			if (palabra1.size() > palabra2.size()){
				return true;
			}
			else
			{
				return false;
			}
		}

	}
}

int Normalizador::numeroTerminos(ifstream *archivo) {

	char auxiliar[25];
	int contador = 0;
	archivo->getline(auxiliar,25);

	while(!archivo->eof()) {
		contador++;
		archivo->getline(auxiliar,25);
	}
	return contador;
}





