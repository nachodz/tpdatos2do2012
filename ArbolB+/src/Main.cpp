//============================================================================
// Name        : ArbolB+.cpp
// Author      : Nacho
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Constante.h"
#include "Log.h"

using namespace std;

int main() {
	Log::getInstancia()->setFilePath(ARCHIVOLOG);
	return 0;
}
