/*
 * Constantes.h
 *
 *  Created on: 13/09/2012
 *      Author: nacho
 */

#ifndef CONSTANTES_H_
#define CONSTANTES_H_

//******************** Path de Archivos ***************************
#define PATH_ARCHIVO_NORMALIZADO "normalizado.txt"
#define PATH_ARCHIVO_A_ALEATORIZAR "diccionario.dat"
#define PATH_DICCIONARIO "diccionario.txt"
#define PATH_STOPWORDS "stopwords.txt"
#define PATH_ARCHIVO_TABULADO "tabulado.txt"
#define PATH_PARTICION "Particiones/particion"
#define DIRECTORIO_PARTICIONES "Particiones"

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
#define MOAA_OP1 "1) Crear arbol B+"
#define MOAA_OP2 "2) Operaciones sobre arbol B+"
#define MOAA_OP3 "3) Operaciones Dispersion Extensible"

#define MA "MENU ARBOL B+"
#define MA_OP1 "1) Buscar termino"
#define MA_OP2 "2) Reportar contenido del arbol B+"

#define MDE "MENU DISPERSION EXTENSIBLE"
#define MDE_OP1 "1) Incorporar un registro"
#define MDE_OP2 "2) Eliminar un registro con identificador n"
#define MDE_OP3 "3) Modificar un registro"
#define MDE_OP4 "4) Listar contenido del archivo"

#define MCE "MENU COMPONENTE ESTADISTICAS"
#define MCE_OP1 "1) Cantidad de terminos promedio por frase"
#define MCE_OP2 "2) Tasa de fallos de términos"
#define MCE_OP3 "3) Lista de terminos no encontrados"
#define MCE_OP4 "4) Ranking de los N terminos mas populares"

#define ERR_RANGO "ERROR: Ingrese un numero válido"
#define INF_ERR_RANGO "Usted ingreso: "

/**********************Arbol B+ ***************************/
#define POTENCIA 0
#define TAM_LONG_REGISTRO sizeof(int)
#define TAM_LONG_CLAVE sizeof(char)
#define TAM_LONG_DATO sizeof(int)
#define CONST_VACIO 0x00
#define PORC_TAMANIO_NODO 50
#define TAM_TOTAL_NODO 256
#define TAM_CONTROL_NODO 24
#define TAM_CONTROL_OVERFLOW 20
#define TAM_EFECTIVO_NODO (TAM_TOTAL_NODO - TAM_CONTROL_NODO)
#define PORCENTAJE_NODO 50
//#define BUFFER_NODOS_LIBRES 256
#define TAM_CONTROL_REGISTRO 10

/************************ Hash ************************/
#define TAM_CUBO 4096
#define NOM_TEMP "Temp"

/***********************Comunes************************/
#define ERROR -1
#define TAM_BUFFER_LECT_ESC 1000
#define CANT_PARTICIONES 400
#define BUFFER_LEC_ESC_SORT 50

/***********************Avisos*************************/
#define MSJ_PROCESANDO "Procesando"

#endif /* CONSTANTES_H_ */