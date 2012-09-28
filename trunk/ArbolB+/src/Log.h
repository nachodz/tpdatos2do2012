/*
 * Log.h
 *
 *  Created on: 27/09/2012
 *      Author: nacho
 */

#ifndef LOG_H_
#define LOG_H_
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>

#include "Constante.h"

using namespace std;

class Log{

public:

	void cerrar();
    void informacion (string etiqueta, string detalle);
	void error (string etiqueta, string detalle);
	void warning (string etiqueta, string detalle);
	void lineaNueva ();
	void setFilePath(string path);
	void openFile();


	static Log* getInstancia();

private:
	Log(void);
	static Log* instancia;
	void log(string tipo, string etiqueta, string detalle);
	fstream	logFileStream;
	string	filePath;

	void removeFile();

};

#endif /* LOG_H_ */

