#include "Fusionador.h"

#define NO_PATHS -1
#define ERR_ESCRITURA -2
#define OK 1
#define MAX_ID 32000



Fusionador::Fusionador(string filePaths[], int tamBuffer, int cant_arch){

    for(int i = 0; i < cant_arch; i++){ /// chequear
         this->filePaths[i] = filePaths[i];
    }
    this->tamBuffer = tamBuffer;
    this->cant_arch = cant_arch;
    this-> cant_buffers = 11;

}


int Fusionador::inicializarBuffers(Registro* buffers[]){

    int cont = 0; // contador de buffers que no pudieron ser alocados

    for(int i = 0; i < (this->cant_buffers); i++){ //aloco memoria en los buffers
        buffers[i] = new Registro[this->tamBuffer]; //chequear
        if(buffers[i] == NULL)
            cont++;
    }
    return cont; //retorna los que no pudo alocar correctamente

}

void Fusionador::abrirArchivos(string filePaths[], ifstream* archs, int num_archs){
    int i;

    for(i = 0; i < num_archs; i++){
    	//archs[i].open(filePaths[i].c_str(), ios::in | ios::binary);
    }
}

void Fusionador::cerrarArchivos(ifstream archs[], int num_archs){
    int i;

    for(i = 0; i < num_archs; i++){
    	archs[i].close();
    }

}

void Fusionador::cargarBuffers(Registro* buffers[], ifstream archs[], int num_particiones, int tamBuffer){

}

Registro minimo(Registro* buffers[],unsigned short v_pos[], int num_particiones, unsigned short* pos_min){
    unsigned short i,j;
    j = v_pos[0]; // num del registro donde esta parado el buffer 0
    Registro min = buffers[i][j]; //el primero siempre es el minimo
    unsigned short k = 0; //numero del buffer que tenia el registro minimo

    for(i = 1; i < num_particiones; i++){
        j = v_pos[i];

        if(((buffers[i][j]).ID) < min.ID){
            min = buffers[i][j];
            k = i;
        }
    }

    v_pos[i]++; //aumento el puntero a registros de ese buffer
    *pos_min = k;


    return min;

}

bool Fusionador::finFusion(Registro* buffers[], int num_particiones, unsigned short v_pos[]){
    int i;

    for(i = 0; i < num_particiones; i++){
        if (buffers[i][v_pos[i]].ID != MAX_ID){ //si el buffer i en la posicion actual tiene MAX_ID
            return false;
        }
    }
    return true;
}

int Fusionador::fusionar_particiones(ifstream archs[], Registro* buffers[], int num_particiones, int tamBuffer, string path_nuevo_arch){


    unsigned short v_pos[num_particiones]; //vector de posiciones para apuntar en el buffer
    int i;  //indices
    inicializarBuffers(buffers);
    Registro reg_min;
    ofstream nuevo_arch;
    unsigned short pos_min; //numero de buffer minimo

    cargarBuffers(buffers, archs, num_particiones, tamBuffer); //carga buffers con la cantidad de registros que puede de los archivos

    for(i = 0; i < num_particiones; i++){ //inicializo vector de posiciones en 0
        v_pos[i] = 0;
    }

    nuevo_arch.open(path_nuevo_arch.c_str(),ios::out | ios::binary);

    while(!finFusion(buffers, num_particiones, v_pos)){


        reg_min = minimo(buffers, v_pos, num_particiones, &pos_min); // devuelve el registro minimo y avanza el puntero correspondiente

        nuevo_arch->write(reg_min, sizeof(Registro));

        if(bufferVacio(buffers[pos_min]))
            cargarUnBuffer(buffers[pos_min], archs[pos_min]); /// hacer

    }


    return OK;

}

string Fusionador::IntToStr(int n) {

	stringstream result;
	result << n;
	return result.str();
}

int Fusionador::merge(){


    int i = 0; //cantidad de archivos originales ya fusionados
    int j = 0; //indice
    string path_nuevo_arch = "nuevo_arch0.bin";
    int nroPart = 0; //numero en el nombre de la nueva particion
    int cant_buffers = this->cant_buffers;

    ifstream archs[this->cant_buffers] = new ifstream[this->cant_buffers]; // uso una cantidad de archivos igual a la cantidad de buffers
    string filePathsAUsar[this->cant_buffers];
    Registro buffers[this->cant_buffers];

    int cant_nuevas_part = (this->cant_arch/cant_buffers);
    if((this->cant_arch)%(cant_buffers) > 0)
        cant_nuevas_part++;

    string parchs_nuevos[cant_nuevas_part]; // paths de los archivos generados por el merge

    while(i < this->cant_arch){

        if((this->cant_arch - i) < (this->cant_buffers))
            cant_buffers = (this->cant_arch - i); //si hay menos archivos a fusionar que buffers, uso cant_buffers = cant_archs_aFusionar

        for(j = 0; j < cant_buffers; j++){ //esto es para usar de a cant_buffer archivos, mas que nada para la ultima iteracion
        	filePathsAUsar[j] = this->filePaths[i+j];
        }
        abrirArchivos(filePathsAUsar, archs, cant_buffers);

        fusionar_particiones(archs, buffers, cant_buffers, this->tamBuffer, path_nuevo_arch); //fusiona archivos (cantidad == this->cant_buffers

        i = i + cant_buffers; //aumento cantidad de archivos ya fusionados

        parchs_nuevos[nroPart] = path_nuevo_arch; //agrego el path de la nueva particion al array de paths nuevos

        nroPart++;
        path_nuevo_arch = "nuevo_arch" + IntToStr(nroPart) + ".bin";       ///aumento el numero del proximo path

        cerrarArchivos(archs, cant_buffers);

    }

    // Fusionador se "actualiza" cambiandose la cantidad de archivos por la cantidad de nuevas particiones, y los paths anteriores por los nuevos paths
    this->cant_arch = nroPart;
    this->filePaths = parchs_nuevos;

    // DELETES

    if(nroPart == 1) //termino la fusion, resultado es un archivo unico
        return OK;
    else
        merge(); //se llama a si mismo recursivamente


}
