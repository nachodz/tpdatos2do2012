#include "CodigoGamma.h"

CodigoGamma::CodigoGamma() {
	this->numAConvertir = 0;
}
CodigoGamma::CodigoGamma(int numeroAConvertir){
	this->numAConvertir = numeroAConvertir;
}
CodigoGamma::~CodigoGamma() {
}

std::string CodigoGamma::aplicarConversion(){

	std::string retorno;
	retorno.clear();
	// Obtengo primera parte del numero
	std::string unario = obtenerUnario(this->numAConvertir);
	// Obtengo segunda parte del numero
	std::string representacionBinaria = conversionRepresentacion(this->numAConvertir);

	// Obtengo la conversion en Gamma
	retorno = unario + representacionBinaria;
	return retorno;

}

std::string CodigoGamma::obtenerUnario(int numAConvertir){

	std::string retorno;
	std::stringstream ss;
	retorno.clear();
	// Obtengo el logaritmo en base 10 del numero
	double logaritmo = (log10(numAConvertir) / log10(2));

	// Le aplico la funcion piso
	long int valor = (int)floor(logaritmo);
	// Le sumo 1
	++valor;

	// Hago el unario
	for (int i = valor; i > 0 ; --i)
		ss << "1";
	    ss << "0";

	retorno = ss.str();
	return retorno;
}

std::string CodigoGamma::conversionRepresentacion(int numAConvertir){

	std::string retorno;
	retorno.clear();
	// Obtengo el logaritmo en base 10 del numero
	double logaritmo = (log10(numAConvertir) / log10(2));
	// Le aplico la funcion piso
	int cantidadBits = (int)floor(logaritmo);

	// Obtengo la expresion a convertir en binario en "cantidadBits" de bits
	int valorConversion = numAConvertir - (int)pow(2,cantidadBits);

	retorno = obtenerBinarioDeNBits(valorConversion, cantidadBits);
	return retorno;
}

std::string CodigoGamma::obtenerBinarioDeNBits(int valorConversion, int cantidadBits){

	std::stringstream ss;
	ss.clear();
	int i,j,num2,res;
	int * x = new int[cantidadBits+1];

	num2 = valorConversion;

	for (int i = 1; i <= cantidadBits ; i++)
		x[i] = 0;

	switch (valorConversion) {
	case 0:
		break;
	case 1:
		x[1] = 1;
		break;
	default:
		for(i = 1 ; i <= valorConversion ; i++){
			// Determina (i) las divisiones que se harÃ¡n
			num2 = num2 / 2;
			if(num2 == 1)
				break;
		}

		x[i+1] = 1;
		for(j = 1 ; j <= i; j++){
			// Realiza las operaciones para la conversiÃ³n
			res = valorConversion % 2;
			if(res == 1)
				x[j] = 1;
			else if(res == 0)
				x[j] = 0;
			valorConversion = valorConversion / 2;
		}
		break;
	}

	// obtengo el valor final
	for(j = cantidadBits ; j > 0 ; j--)
		ss << x[j];

	delete x;
	return (ss.str());
}

int cantidadUnarios(std::string conversion){
	std::string uno = "1";
	int numeroUnario = 0;
	bool cero = false;

	for (int i = 0 ; ((unsigned int)i < conversion.length()) && (!cero); ++i){
		if (conversion[i] == uno[0])
			++numeroUnario; //numeroUnario == log2(cantDocs)
		else break;
	}

	return numeroUnario;

}

std::list<int> CodigoGamma::decodificarLista(std::string conversion){

	std::string s = "";
	int numeroUnario;
	int cantDocs;
	int posInicio = 0;
	std::list<int> listaDocs;
	std::list<int>::iterator it;
	int nroDoc;


	numeroUnario = cantidadUnarios(conversion);

	//conversion de la cantidad de docs
	for(int i = 0; i < (numeroUnario* 2); i++){
		s += conversion[i];
	}

	cantDocs = interpretarConversion(s);
	listaDocs.push_front(cantDocs);
	s = "";

	// conversion de los nroDocs
	posInicio = (numeroUnario*2);

	while((unsigned int)posInicio < conversion.length()){

		for(int i = posInicio; (unsigned int)i < conversion.length(); i++){
			s += conversion[i];
		}
		numeroUnario = cantidadUnarios(s);
		nroDoc = interpretarConversion(s);

		if (nroDoc == 0) {
			nroDoc = 1;
			numeroUnario = 1;
		}else
		 {
		   if (nroDoc >= cantDocs)
		      nroDoc = nroDoc + cantDocs;
		    else
			   nroDoc = cantDocs - nroDoc ;
		     }
		listaDocs.push_back(nroDoc);
		posInicio += (numeroUnario*2);                                                 /*(floor((int)log2(nroDoc)) * 2) + 1*/
		s = "";

	}

	return listaDocs;

}

int CodigoGamma::interpretarConversion(std::string conversion){
	std::string binarioAInterpretar;
	std::stringstream ss;
	int numeroUnario;
	int retorno = 0;

	// Leo el primer numero en unario
	numeroUnario = cantidadUnarios(conversion);

	// Leo la segunda parte que esta en binario
	ss.clear();
	binarioAInterpretar.clear();
	for (int i = numeroUnario+1; (unsigned int) i < ((numeroUnario*2) /*+ 1*/); ++i){
		ss << conversion[i];
	}
	binarioAInterpretar = ss.str();

	// obtengo el numero interpretado

	retorno = (int)pow(2,(numeroUnario-1)) + interpretarBinario(binarioAInterpretar);

	return retorno;
}

int CodigoGamma::interpretarBinario(std::string binarioAInterpretar){ //convierte un n binario a dec
	int largo = binarioAInterpretar.size();

	int sumatoria = 0;
	int val;
	int exponente;

	for (int a =0; a<largo; a++){
		val = binarioAInterpretar[a];
		exponente = largo - a - 1;
		if ( val == 49){
			sumatoria += pow(2, exponente);
		}
	}

	return sumatoria;
}

std::string CodigoGamma::comprimirLista(std::list<int> listaInvertida, int primero){
	std::list<int>::iterator it = listaInvertida.begin();
	int aux = primero;
	this->numAConvertir = primero;
	std::stringstream ss;
	ss << this->aplicarConversion();
	++it;
	while ( it != listaInvertida.end()){
		if ((*it) <=  primero){
			primero = primero -(*it);
		}else{
			primero = (*it) - primero;
		}
		this->numAConvertir = primero;
		ss << this->aplicarConversion();
		++it;
		primero = aux;
	}
	return (ss.str());
}

std::string CodigoGamma::convertirAString(char* buf){

	int letra;
	std::string bits = "";

	for(int i = 0; (unsigned int)i < sizeof(buf); i++){
		if(buf[i] == '\0') break;
		letra = buf[i];
		for(int j = 7; j >= 0; j--){
			if(letra >= pow(2,j)){
				bits += "1";
				letra -= pow(2,j);
			}
			else
				bits += "0";
		}
	}
	return bits;
}

std::string CodigoGamma::stringABits(std::string cadena){
	char suma;
	int j = 0, i;
	std::string result = "";
	std::string uno = "1";

	while((unsigned int)j < cadena.length()){
		suma = 0;
		for(i = j; i < (j + 8); i++){
			if(cadena[i] == uno[0]){
				suma += pow(2,(7 - i + j));
			}
		}
		result += suma;
		j += i;
	}

	return result;

}

