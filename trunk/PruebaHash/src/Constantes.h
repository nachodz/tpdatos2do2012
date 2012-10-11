#ifndef CONSTANTES_H_
#define CONSTANTES_H_

/**********************Arbol B+ ***************************/
#define POTENCIA 0
#define TAM_LONG_REGISTRO sizeof(int)
//#define TAM_LONG_CLAVE sizeof(char)
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
#define PATH_IDS "Ids_Terminos.txt"
#define PATH_IDS_BORRAR "No_sirve.txt"

//********************Hash******************************
#define TAM_CUBO 4096
#define TAM_LONG_REGISTRO sizeof(int)
#define TAM_LONG_CLAVE sizeof(int)
#define NOM_TEMP "Temp"
#define NOM_TABLA "TablaHash"
#define NOM_ESP_LIBRE "EspLibreHash"
#define NOM_BLOQUES "BloquesHash"
#define NOM_SALIDA "SalidaHash"


//******************** Menu ***************************
#define MP "MENU PRINCIPAL"
#define MP_OP1 "1) Operaciones sobre Diccionario"
#define MP_OP2 "2) Organización de Archivo"
#define MP_OP3 "3) Componente de Estadísticas"

#define SALIR "Salir"
#define INGRESO "Por favor, ingresar una opción: "

#define MD "MENU DICCIONARIO"
#define MD_OP1 "1) Normalizar Diccionario"
#define MD_OP2 "2) Aleatorizar Diccionario"

#define MOAA "MENU ORGANIZACION DE ARCHIVO"
#define MOAA_OP1 "1) Crear Árbol B+"
#define MOAA_OP2 "2) Operaciones sobre Árbol B+"
#define MOAA_OP3 "3) Operaciones Dispersión Extensible"

#define MA "MENU ARBOL B+"
#define MA_OP1 "1) Buscar término"
#define MA_OP2 "2) Reportar contenido del Árbol B+"

#define MDE "MENU DISPERSION EXTENSIBLE"
#define MDE_OP1 "1) Incorporar un registro"
#define MDE_OP2 "2) Eliminar un registro con identificador n"
#define MDE_OP3 "3) Modificar un registro"
#define MDE_OP4 "4) Listar contenido del archivo"

#define MCE "MENU COMPONENTE ESTADISTICAS"
#define MCE_OP1 "1) Cantidad de términos promedio por frase"
#define MCE_OP2 "2) Tasa de fallos de términos"
#define MCE_OP3 "3) Lista de términos no encontrados"
#define MCE_OP4 "4) Ranking de los N términos más populares"

#define ERR_RANGO "ERROR: Ingrese un número válido"
#define INF_ERR_RANGO "Usted ingresó: "


#endif /* CONSTANTES_H_ */
