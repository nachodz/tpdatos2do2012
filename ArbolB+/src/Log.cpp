/*
 * Log.cpp
 *
 *  Created on: 27/09/2012
 *      Author: nacho
 */

#include "Log.h"

Log* Log::instancia = NULL;

Log* Log::getInstancia()
{
        if (instancia == NULL){
                instancia = new Log();
        }

        return instancia;
}

void Log::informacion (string label, string detail) {
        log("INFORMACION",label,detail);
}

void Log::error (string label, string detail) {
        log("ERROR",label,detail);
}

void Log::warning (string label, string detail) {
        log("WARNING",label,detail);
}

void Log::setFilePath(string path)
{
        this->filePath = path;
}

void Log::log(string type, string label, string detail) {
        this->openFile();
        time_t now = time(NULL);
        struct tm * ptm = localtime(&now);
        char timestamp[32];
        strftime (timestamp, 32, "%d.%m.%Y %H:%M:%S", ptm);

        logFileStream << timestamp << "\t[" << type << "]\t" << label << "\t\t" << detail << endl;
        logFileStream.flush();
}

void Log::cerrar() {
        logFileStream.flush();
        logFileStream.close();
}

void Log::lineaNueva () {
        logFileStream << endl;
        logFileStream.flush();
}

Log::Log(){
        this->removeFile();
}

void Log::openFile() {
        filePath = this->filePath;
        if (!logFileStream.is_open()){
                logFileStream.open(filePath.c_str(), fstream::in | fstream::out | fstream::app);
                if (!logFileStream.is_open())
                        logFileStream.open(filePath.c_str(), fstream::in | fstream::out | fstream::trunc);
        }
}

void Log::removeFile(){
        remove(ARCHIVOLOG);
}

