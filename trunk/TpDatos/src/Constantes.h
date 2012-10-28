
#ifndef CONSTANTES_H_
#define CONSTANTES_H_

//******************** Path de Archivos ***************
#define PATH_ARCHIVO_NORMALIZADO "normalizado.txt"
#define PATH_ARCHIVO_A_ALEATORIZAR "diccionario.dat"
#define PATH_DICCIONARIO "diccionario.txt"
#define PATH_STOPWORDS "stopwords.txt"
#define PATH_ARCHIVO_TABULADO "tabulado.txt"
#define PATH_PARTICION "Particiones/particion"
#define PATH_FRASES "Frases_Celebres.csv"
#define DIRECTORIO_PARTICIONES "Particiones"
#define PATH_ARBOL "ARBOLB+"
#define PATH_TERM_NO_ENCONTRADOS "TerminosNoEncontrados.txt"
#define PATH_INFORMES "informe.txt"
#define PATH_METADATA "metadata.dat"
#define PATH_ALEATORIO "archivoFinal.bin"

//******************** Avisos *************************
#define MSJ_PROCESANDO "..procesando.."


//******************** Menu ***************************
#define MP "MENU PRINCIPAL"
#define MP_OP1 "1) Operaciones sobre Diccionario"
#define MP_OP2 "2) Organizacion de Archivo"
#define MP_OP3 "3) Componente de Estadísticas"

#define SALIR "Salir"
#define INGRESO "Por favor, ingresar una opcion: "

#define MD "MENU DICCIONARIO"
#define MD_OP1 "1) Normalizar Diccionario"
#define MD_OP2 "2) Aleatorizar Diccionario"

#define MOAA "MENU ORGANIZACION DE ARCHIVO"
#define MOAA_OP1 "1) Operaciones sobre arbol B+"
#define MOAA_OP2 "2) Operaciones Dispersion Extensible"

#define MA "MENU ARBOL B+"
#define MA_OP1 "1) Carga inicial Árbol B+"
#define MA_OP2 "2) Buscar termino"
#define MA_OP3 "3) Reportar contenido del Árbol B+"
#define MA_OP4 "4) Listar todos los términos del Árbol B+ en un archivo de texto."

#define MDE "MENU DISPERSION EXTENSIBLE"
#define MDE_OP1 "1) Crear archivo directo con archivo de Frases Célebres"
#define MDE_OP2 "2) Incorporar un registro"
#define MDE_OP3 "3) Eliminar un registro con identificador n"
#define MDE_OP4 "4) Modificar un registro"
#define MDE_OP5 "5) Listar contenido del archivo"

#define MCE "MENU COMPONENTE ESTADISTICAS"
#define MCE_OP1 "1) Recorrer secuencialmente el archivo directo"
#define MCE_OP2 "2) Cantidad de terminos promedio por frase"
#define MCE_OP3 "3) Tasa de fallos de términos"
#define MCE_OP4 "4) Lista de terminos no encontrados"
#define MCE_OP5 "5) Ranking de los N terminos mas populares"

#define ERR_RANGO "ERROR: Ingrese un numero válido"
#define INF_ERR_RANGO "Usted ingreso: "

/**********************Arbol B+ ***************************/
#define ARBOLBMAS_POTENCIA 0
#define ARBOLBMAS_TAM_LONG_REGISTRO sizeof(int)
#define ARBOLBMAS_TAM_LONG_CLAVE sizeof(char)
#define ARBOLBMAS_TAM_LONG_DATO sizeof(int)
#define ARBOLBMAS_CONST_VACIO 0x00
#define ARBOLBMAS_PORC_TAMANIO_NODO 50
#define ARBOLBMAS_TAM_TOTAL_NODO 256
#define ARBOLBMAS_TAM_CONTROL_NODO 24
#define ARBOLBMAS_TAM_CONTROL_OVERFLOW 20
#define ARBOLBMAS_TAM_EFECTIVO_NODO (ARBOLBMAS_TAM_TOTAL_NODO - ARBOLBMAS_TAM_CONTROL_NODO)
#define ARBOLBMAS_PORCENTAJE_NODO 50
//#define BUFFER_NODOS_LIBRES 256
#define ARBOLBMAS_TAM_CONTROL_REGISTRO 10


/* Avisos Árbol B+ */
#define ARBOLBMAS_CARGAINICIAL "Se inicia carga inicial del Árbol B+"
#define ARBOLBMAS_CARGAINICIALOK "La carga incial del Árbol B+ ha finalizado correctamente"
#define ARBOLBMAS_INGRESARTERMINO "Ingrese un término: "
#define ARBOLBMAS_INFORMETERMINO "El registro encontrado es el siguiente: "
#define ARBOLBMAS_LISTARENPREORDEN "Se inicia listado en pre orden en un archivo de texto."
#define ARBOLBMAS_LISTARENPREORDENOK "El listado en pre orden ha finalizado correctamente."
#define ARBOLBMAS_LISTARTODOSTERMINOS "Se inicia lista de todos los términos en un archivo de texto."
#define ARBOLBMAS_LISTARTODOSTERMINOSOK "El listado de todos los términos ne un archivo de texto ha finalizado correctamente."

/************************ Hash ************************/
#define HASH_TAM_CUBO 4096
#define HASH_TAM_LONG_REGISTRO sizeof(int)
#define HASH_TAM_LONG_CLAVE sizeof(int)
#define HASH_NOM_TEMP "Temp"
#define HASH_NOM_TABLA "TablaHash"
#define HASH_NOM_ESP_LIBRE "EspLibreHash"
#define HASH_NOM_BLOQUES "BloquesHash"
#define HASH_NOM_SALIDA "SalidaHash"

/* Avisos Hash */
#define HASH_CARGAINICIALCOMIENZO "Comienzo de carga de archivo de Frase Célebres."
#define HASH_CARGAINICIALOK "La carga inicial del Hash se realizo correctamente."
#define HASH_INGRESARN "Ingrese clave n: "
#define HASH_INGRESARAPEAUTOR "Ingrese el apellido del autor: "
#define HASH_INGRESARNOMAUTOR "Ingrese el nombre del autor: "
#define HASH_INGRESARFRASE "Ingrese la frase: "
#define HASH_ALTAOK "El registro se ingreso correctamente."
#define HASH_BAJAOK "El registro se elimino correctamente."
#define HASH_MODIFICAROK "El registro fue eliminado correctamente."
#define HASH_SALIDAOK "El archivo de salida se generó correctamente."

/**********************Estadistico*********************/
#define CANT_STOPW 500

/* Avisos */
#define ESTADISTICO_CARGAINICIALCOMIENZO "Recorriendo secuencialmente el archivo directo de frases."
#define ESTADISTICO_CARGAINICIALOK "La recorrida del archivo directo se ha completado correctamente"
#define ESTADISTICO_TASAFALLOS "La tasa de fallos es igual a: "
#define ESTADISTICO_LISTATERMINOSNOENCONTRADOS "Lista de términos no encontrados"
#define ESTADISTICO_INGRESARN "Ingrese la cantidad de términos que desea ver en el ranking: "
#define ESTADISTICO_RANKING "Ranking de términos más populares"
#define ESTADISTICO_TERMINOSPROMPORFRASE "Cantidad de términos promedio por frase: "


/***********************Comunes************************/
#define ERROR -1
#define TAM_BUFFER_LECT_ESC 1000
#define CANT_PARTICIONES 400
#define BUFFER_LEC_ESC_SORT 50
#define TAM_BUFFER_LEC 1000

/**********************Fusionador**********************/
#define CANTIDAD_BUFFERS_MERGE 11

/**********************Aleatorizador**********************/
#define REGISTROS_POR_BUFFER 11

#endif /* CONSTANTES_H_ */


