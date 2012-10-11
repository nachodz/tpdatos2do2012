#ifndef CONSTANTES_H_
#define CONSTANTES_H_


//********************Hash******************************
#define TAM_CUBO 4096
#define TAM_LONG_REGISTRO sizeof(int)
#define TAM_LONG_CLAVE sizeof(int)
#define NOM_TEMP "Temp"
#define NOM_TABLA_PALABRA "TablaHash"
#define NOM_ESP_LIBRE_PALABRA "EspLibreHash"
#define NOM_BLOQUES_PALABRA "BloquesHash"
#define NOM_SALIDA_PALABRA "SalidaHash"


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
