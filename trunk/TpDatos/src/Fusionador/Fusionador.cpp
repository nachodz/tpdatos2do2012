#include "Fusionador.h"

#define NO_PATHS -1
#define ERR_ESCRITURA -2
#define OK 1
#define MAX_ID 999999999



Fusionador::Fusionador(string *filePaths, int tamBuffer, int cant_arch){
	this->filePaths = new string[cant_arch];
    for(int i = 0; i < cant_arch; i++){
         this->filePaths[i] = filePaths[i];
    }
    this->tamBuffer = tamBuffer;
    this->cant_arch = cant_arch;
    this-> cant_buffers = CANTIDAD_BUFFERS_MERGE;
    this->numEtapas = 1;
    this->ultimoPath = "etapa1";
    this->cantRegs = 0;

}

void Fusionador::destruir(){
	delete[] this->filePaths;
}


int Fusionador::inicializarBuffers(Registro** buffers){

    int cont = 0;

    for(int i = 0; i < (this->cant_buffers); i++){
        buffers[i] = new Registro[this->tamBuffer];
        if(buffers[i] == NULL)
            cont++;
    }
    return cont;

}

void Fusionador::destruirBuffers(Registro** buffers){

    int i;

    for(i = 0; i < (this->cant_buffers); i++){
        delete[] buffers[i];
    }


}

void Fusionador::abrirArchivos(string filePathsAUsar[], ifstream* archs, int num_archs){
    int i;

    for(i = 0; i < num_archs; i++){
    	archs[i].open(filePathsAUsar[i].c_str(), ios::in | ios::binary);
    }
}

void Fusionador::cerrarArchivos(ifstream* archs, int num_archs){
    int i;

    for(i = 0; i < num_archs; i++){
    	archs[i].close();
    }

}

void Fusionador::informar(int cant_archivos, int cant_buffers, int numEtapa){
	ofstream informe;
	informe.open("informe.txt", ios::app);
	int cantAInformar =(cant_archivos/cant_buffers);

	if(cant_archivos%cant_buffers > 0) cantAInformar++;
	informe<< endl;
	informe<<"cantidad de archivos de la etapa ";
	informe<< IntToStr(numEtapa).c_str();
	informe<< " es: ";
	informe<< IntToStr(cantAInformar).c_str() << endl;
	informe << "cantidad de registros en la etapa: ";
	informe << this->cantRegs << endl;

	informe.close();

}

int Fusionador::getCantRegs(){
	return this->cantRegs;
}



Registro Fusionador::minimo(Registro** buffers,unsigned short* v_pos, int num_particiones, unsigned short* pos_min){
    unsigned short i = 0, j;
    j = v_pos[0]; // num del registro donde esta parado el buffer 0
    Registro min = buffers[0][j]; //el primero siempre es el minimo
    unsigned short k = 0; //numero del buffer que tenia el registro minimo

    for(i = 1; i < num_particiones; i++){
        j = v_pos[i];

        if(((buffers[i][j]).ID) < min.ID){
            min.ID = buffers[i][j].ID;
            strcpy(min.palabra, buffers[i][j].palabra);
            k = i;
        }
    }

    v_pos[k]++; //aumento el puntero a registros de ese buffer
    *pos_min = k;


    return min;

}

bool Fusionador::finFusion(Registro** buffers, int num_particiones, unsigned short v_pos[]){
    int i;

    for(i = 0; i < num_particiones; i++){
        if (buffers[i][v_pos[i]].ID != MAX_ID){ //si el buffer i en la posicion actual tiene MAX_ID
            return false;
        }
    }
    return true;
}

bool Fusionador::bufferVacio(Registro* buffer, unsigned short pos_actual){
    ///si llega hasta el final y no es MAX_ID

    if((pos_actual == this->tamBuffer)) //si me pase del ult reg del buffer y no es EOF
        return true;
    else
        return false;
}

void Fusionador::cargarUnBuffer(Registro buffer[], ifstream* arch, int tamBuffer){
    unsigned short i = 0;
    Registro reg_inv;
    reg_inv.ID = MAX_ID;


    if (!arch->eof()){
		for(i = 0; i < tamBuffer; i++){
			arch->read((char*)&(buffer[i]), sizeof(Registro));

			if(arch->eof() && (i < tamBuffer - 1)){
				buffer[i].ID = reg_inv.ID;
				break;
			}

		}

    }
    else
    	buffer[0] = reg_inv;

}

void Fusionador::cargarBuffers(Registro* buffers[], ifstream* archs, int num_particiones, int tamBuffer){
    unsigned short i;
    for(i = 0; i < num_particiones; i++){
        cargarUnBuffer(buffers[i], &(archs[i]), tamBuffer);
    }

}

void Fusionador::fusionar_particiones(ifstream* archs, Registro** buffers, int num_archs, int tamBuffer, string path_nuevo_arch){


    unsigned short v_pos[num_archs]; //vector de posiciones para apuntar en el buffer
    unsigned short i;
    inicializarBuffers(buffers);
    Registro reg_min;
    ofstream nuevo_arch;
    unsigned short pos_min; //numero de buffer minimo

    cargarBuffers(buffers, archs, num_archs, tamBuffer);

    for(i = 0; i < num_archs; i++){ //inicializo vector de posiciones en 0
        v_pos[i] = 0;
    }

    nuevo_arch.open(path_nuevo_arch.c_str(),ios::out | ios::binary);

    while(!finFusion(buffers, num_archs, v_pos)){


        reg_min = minimo(buffers, v_pos, num_archs, &pos_min); // devuelve el registro minimo y avanza el puntero correspondiente

        nuevo_arch.write((char*)&reg_min, sizeof(Registro));
        this->cantRegs++;
        nuevo_arch.flush();
        if(bufferVacio(buffers[pos_min], v_pos[pos_min])){
        	cargarUnBuffer(buffers[pos_min], &archs[pos_min], tamBuffer); //el unico que puede llegar a vaciarse es el que tenia el minimo
        	v_pos[pos_min] = 0; //se volvio a llenar el buffer, entonces reseteo el indice de registros
        }



    }

    nuevo_arch.close();

    destruirBuffers(buffers);


}

string Fusionador::IntToStr(int n) {

	stringstream result;
	result << n;
	return result.str();
}

void Fusionador::actualizarPaths(string paths_viejos[], string paths_nuevos[], unsigned short cant_paths){
    unsigned short i;
    for(i = 0; i < cant_paths; i++){
        paths_viejos[i] = paths_nuevos[i];
    }
}

void Fusionador::prepararPaths(string filePathsTotales[],string filePathsAUsar[], int cant, int cant_buffers){

	for(int j = 0; j < cant_buffers; j++){
		filePathsAUsar[j] = this->filePaths[cant+j];
	}

}

int Fusionador::merge(){


    int i = 0; //cantidad de archivos originales ya fusionados
    string path_nuevo_arch = this->ultimoPath + "/" "nuevo_arch0.bin";
    unsigned short nroPart = 0; //numero en el nombre de la nueva particion
    int cant_buffers = this->cant_buffers;
    this->cantRegs = 0;

    int cant_nuevas_part = (this->cant_arch/cant_buffers);
    if((this->cant_arch)%(cant_buffers) > 0)
            cant_nuevas_part++;

    if(cant_nuevas_part == 1){
    	for(int k = 0; k < this->numEtapas;k++)
    		system("cd");
    	path_nuevo_arch = "archivoFinal.bin";
    }

    else
    	mkdir((this->ultimoPath).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    ifstream* archs = new ifstream[this->cant_buffers]; // uso una cantidad de archivos igual a la cantidad de buffers
    string filePathsAUsar[this->cant_buffers];
    Registro* buffers[this->cant_buffers];

    string parchs_nuevos[cant_nuevas_part]; // paths de los archivos generados por el merge

    while(i < this->cant_arch){

        if((this->cant_arch - i) < (this->cant_buffers))
            cant_buffers = (this->cant_arch - i); //si hay menos archivos a fusionar que buffers, uso cant_buffers = cant_archs_aFusionar

        prepararPaths(this->filePaths, filePathsAUsar, i, cant_buffers);
        abrirArchivos(filePathsAUsar, archs, cant_buffers);
        fusionar_particiones(archs, buffers, cant_buffers, this->tamBuffer, path_nuevo_arch); //fusiona archivos (cantidad == cant_buffers)
        i = i + cant_buffers; //aumento cantidad de archivos ya fusionados

        parchs_nuevos[nroPart] = path_nuevo_arch;

        nroPart++;
        path_nuevo_arch = this->ultimoPath + "/" + "nuevo_arch" + IntToStr(nroPart) + ".bin";

        cerrarArchivos(archs, cant_buffers);

    }
    delete[] archs;
    informar(this->cant_arch, this->cant_buffers, this->numEtapas);

    if(nroPart == 1){

    	//termino la fusion, resultado es un archivo unico
    	return OK;
    }

    else{

        // Fusionador se "actualiza" cambiandose la cantidad de archivos por la cantidad de nuevas particiones, y los paths anteriores por los nuevos paths
        this->cant_arch = nroPart;
        actualizarPaths(this->filePaths, parchs_nuevos, nroPart);
        this->numEtapas++;
        this->ultimoPath = this->ultimoPath + "/" + "etapa" + IntToStr(this->numEtapas);
        merge();

        return this->cantRegs;
    }



}
