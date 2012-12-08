
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
#define MPTP1 "1) Menu TP1"
#define MPTP2 "2) Menu TP2"

#define MPTP1_TIT "MENU TP1"
#define MPTP2_TIT "MENU TP2"

#define DICC_FRASES "1) Operaciones sobre diccionario de frases"
#define IDX_BOOLEANO "2) Operaciones sobre Índice Booleano"
#define IDX_PORC_FIRMAS "3) Operaciones sobre Índice de Porciones de Firmas"
#define IDX_COMP_ESTAD "4) Operaciones sobre el Componente de Estadísticas"

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

#define IDX_BOOLEANO_TIT "MENU INDICE BOOLEANO"
#define IDX_BOOLEANO_CREACION "Se ha creado el índice booleano"
#define IDX_BOOLEANO_ALTA_FRASE "1) Realizar un alta de una frase"
#define IDX_BOOLEANO_BAJA_FRASE "2) Realizar una baja de una frase"
#define IDX_BOOLEANO_MODIFICACION_FRASE "3) Realizar una modificación de una frase"
#define IDX_BOOLEANO_BUSQUEDA_FRASE "4) Realizar la búsqueda de una lista de términos"
#define IDX_BOOLEANO_ALTA "ALTA DE UNA FRASE"
#define IDX_BOOLEANO_ALTA_OK "El alta de la frase se ha realizado correctamente"
#define IDX_BOOLEANO_ALTA_OPCION "Ingrese la frase, anteponiendo su autor, en caso de no conocerlo poner Anonimo"
#define IDX_BOOLEANO_BAJA "BAJA DE UNA FRASE"
#define IDX_BOOLEANO_BAJA_OK "El baja de la frase se ha realizado correctamente"
#define IDX_BOOLEANO_BAJA_OPCION "Ingrese el numero de registro de la frase a eliminar (Guiarse por el archivo de texto)"
#define IDX_BOOLEANO_BAJA_ERROR "El numero de frase exede la capacidad total del archivo"
#define IDX_BOOLEANO_BUSQUEDA "BUSQUEDA DE LISTA DE TERMINOS"
#define IDX_BOOLEANO_BUSQUEDA_OPCION "Ingrese la cantidad (mayor a 0): "
#define IDX_BOOLEANO_MODIFICACION "MODIFICACION DE UNA FRASE"
#define IDX_BOOLEANO_MODIFICACION_OPCION1 "Ingrese Nro de Registro a modificar: "
#define IDX_BOOLEANO_MODIFICACION_OPCION2 "Ingrese la frase, anteponiendo su autor, en caso de no conocerlo poner Anonimo: "

#define IDX_FIRMAS_TIT "MENU INDICE DE PORCIONES DE FIRMAS"
#define IDX_FIRMAS_CREACION "Se ha creado el índice de porciones de firmas"
#define IDX_FIRMAS_CARGA_INICIAL "1) Realizar la carga inicial"
#define IDX_FIRMAS_ALTA_FRASE "2) Realizar el alta de una frase"
#define IDX_FIRMAS_BAJA_FRASE "3) Realizar la baja de una frase"
#define IDX_FIRMAS_MODIFICACION_FRASE "4) Realizar la modificaci�n de una frase"
#define IDX_FIRMAS_BUSQUEDA_PALABRAS_FRASE "5) Buscar términos en frases"
#define IDX_FIRMAS_MOSTRAR_FRASES "6) Mostrar frases en archivo de texto"
#define IDX_FIRMAS_MOSTRAR_FIRMA_TERMINO "7) Mostrar firma de un término"

#define IDX_FIRMAS_CARGA_INI "CARGA INICIAL DEL INDICE DE FIRMAS"
#define IDX_FIRMAS_CARGA_INI_OK "La carga inicial se ha realizado correctamente"
#define IDX_FIRMAS_ALTA "ALTA DE UNA FRASE"
#define IDX_FIRMAS_ALTA_OPCION "Insertar la frase a indexar anteponiendo su autor:"
#define IDX_FIRMAS_ALTA_OK "El alta de la frase se ha realizado correctamente"
#define IDX_FIRMAS_BAJA "BAJA DE UNA FRASE"
#define IDX_FIRMAS_BAJA_OPCION1 "Inserte el número de frase que desea dar de baja:"
#define IDX_FIRMAS_BAJA_OPCION2 "(Número que aparece al final de cada frase en el archivo de texto)"
#define IDX_FIRMAS_BAJA_OK "La baja de la frase se ha realizado correctamente"

#define IDX_FIRMAS_MODIFICACION "MODIFICACI�N DE UNA FRASE"
#define IDX_FIRMAS_MODIFICACION_OPCION1 "Inserte el n�mero de frase que desea modificar:"
#define IDX_FIRMAS_MODIFICACION_OPCION2 "(Número que aparece al final de cada frase en el archivo de texto)"
#define IDX_FIRMAS_MODIFICACION_OPCION3 "Ingrese la frase, anteponiendo su autor, en caso de no conocerlo poner Anonimo: "
#define IDX_FIRMAS_MODIFICACION_OK "La baja de la frase se ha realizado correctamente"

#define IDX_FIRMAS_BUSQUEDA_PALABRAS "BUSQUEDA DE TERMINOS EN FRASE"
#define IDX_FIRMAS_BUSQUEDA_PALABRAS_OPCION "Ingrese la lista de términos a buscar separadas por espacio: "
#define IDX_FIRMAS_BUSQUEDA_PALABRAS_OK "La búsqueda se ha realizado correctamente"
#define IDX_FIRMAS_MOSTRAR_FRASES_TIT "EXPORTAR FRASES A .TXT"
#define IDX_FIRMAS_MOSTRAR_FRASES_OK "Las frases se han exportado correctamente"
#define IDX_FIRMAS_MOSTRAR_FIRMA "MOSTRAR LA FIRMA DE UN TERMINO"
#define IDX_FIRMAS_MOSTRAR_FIRMA_TERMINOS_OPCION "Ingrese un término: "
#define IDX_FIRMAS_MOSTRAR_FIRMA_TERMINOS_OK "La firma se ha mostrado correctamente"

#define DICC_FRASES_TIT "DICCIONARIO DE FRASES"
#define DICC_FRASES_CARGA_INICIAL "1) Realizar carga inicial del diccionario de frases"
#define DICC_FRASES_ALTA "2) Realizar alta de una frase"
#define DICC_FRASES_BAJA "3) Realizar baja de una frase"
#define DICC_FRASES_MOSTRAR "4) Exportar el diccionario a un .txt"
#define DICC_FRASES_CARGA_INI "CARGA INICIAL DICCIONARIO FRASES"
#define DICC_FRASES_CARGA_INI_OK "La carga inicial se ha realizado correctamente"
#define DICC_FRASES_ALTA_TIT "ALTA DE UNA FRASE"
#define DICC_FRASES_ALTA_OPCION "Ingrese la frase, anteponiendo su autor, en caso de no conocerlo poner Anonimo"
#define DICC_FRASES_ALTA_OK "El alta de la frase se ha realizado correctamente"
#define DICC_FRASES_BAJA_TIT "BAJA DE UNA FRASE"
#define DICC_FRASES_BAJA_OPCION "Ingrese el numero de registro de la frase a eliminar (Guiarse por el archivo de texto)"
#define DICC_FRASES_BAJA_OK "La baja de la frase se ha realizado correctamente"
#define DICC_FRASES_MOSTRAR_TIT "EXPORTAR EL DICCIONARIO DE FRASES A UN .TXT"
#define DICC_FRASES_MOSTRAR_OK "Se ha exportado el diccionario correctamente a un .txt"

#define COMP_ESTAD_TP2_TIT "COMPONENTE ESTADISTICO"
#define COMP_ESTAD_TP2_BUSQ1 "1) Buscar 1 término"
#define COMP_ESTAD_TP2_BUSQ2 "2) Buscar 2 términos"
#define COMP_ESTAD_TP2_BUSQ3 "3) Buscar 3 términos"

#define COMP_ESTAD_TP2_BUSQ1_TIT "BUSQUEDA DE UN TERMINO"
#define COMP_ESTAD_TP2_BUSQ1_OPCION "Ingrese término a buscar: "
#define COMP_ESTAD_TP2_BUSQ_OK "La búsqueda se ha realizado correctamente"

#define COMP_ESTAD_TP2_BUSQ2_TIT "BUSQUEDA DE DOS TERMINOS"
#define COMP_ESTAD_TP2_BUSQ2_OPCION1 "Ingrese el primer término a buscar: "
#define COMP_ESTAD_TP2_BUSQ2_OPCION2 "Ingrese el segundo término a buscar: "

#define COMP_ESTAD_TP2_BUSQ3_TIT "BUSQUEDA DE TRES TERMINOS"
#define COMP_ESTAD_TP2_BUSQ3_OPCION1 "Ingrese el primer término a buscar: "
#define COMP_ESTAD_TP2_BUSQ3_OPCION2 "Ingrese el segundo término a buscar: "
#define COMP_ESTAD_TP2_BUSQ3_OPCION3 "Ingrese el tercer término a buscar: "


#define ERR_RANGO "ERROR: Ingrese un numero válido"
#define INF_ERR_RANGO " Usted ingreso: "

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
#define ARBOLBMAS_CARGAINICIALOK "La carga inicial del Árbol B+ ha finalizado correctamente"
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
#define HASH_OPCIONINGRESARAUTOR "¿Desea ingresar un autor? (1: SI, 2: NO)"
#define HASH_OPCIONINGRESARNOMAUTOR "¿Desea ingresar un nombre para el autor? (1: SI, 2: NO)"

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

/*******************DICCIONARIO DE FRASES**************/
#define TAMANIO_REGISTRO_FRASES 256

/***************IDX BOOLEANO*******************************/
#define TAMANIO_BLOQUE_LISTAS_INV 128
#define TAMANIO_REGISTRO_FRASES 256
#define CANT_STOPW 500
#define UMBRAL 26
#define PATH_ARCHIVO_TERMINOS_BOOLEANO "terminos_booleano.dat"
#define PATH_ARCHIVO_OCURRENCIAS "ocurrencias_booleano.dat"
#define PATH_ARCHIVO_OCURRENCIAS_ORD "Particiones/particion0"
#define PATH_ARCHIVO_INVERTIDAS "ls_invertidas.dat"
#define PATH_ARCHIVO_BUSQUEDA "resultado_busqueda_booleano.txt"

/****************IDX PORCIONES DE FIRMAS*******************/
#define PATH_LEXICO "lexico.dat"
#define PATH_FIRMAS "firmas.dat"
#define PATH_TERMINOS "terminos_porciones_firmas.dat"
#define PATH_OCURRENCIAS "ocurrencias_porciones_firmas.dat"
#define PATH_INDICE "config.dat"
#define PATH_FRASES_EN_TXT "Listado_frases.txt"
#define PATH_RESULTADO_BUSQUEDA "resutado_busqueda_porciones_firmas.txt"
#define PATH_OCURRENCIAS_ORDENADO "ocurrenciasOrdenado.dat"

#define TOPE_CARGA 500
#define TAMANIO_REGISTRO_FRASE 256
#define BYTE 8
#define TOPE_TERMINOS_RELEVANTES 100
#define NUM_STOPWORDS 550
#define TAM_PORCION 256

/**********Comun a ambos idx**********************/
#define PATH_ARCHIVO_FRASES "Frases_celebres.dat"

/******************MAPA DE BITS***************************/
#define TAMANIO_BINARIO 16

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


