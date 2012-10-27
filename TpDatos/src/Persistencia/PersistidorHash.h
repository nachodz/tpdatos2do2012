
#ifndef PERSISTIDORHASH_H_
#define PERSISTIDORHASH_H_

#include "Persistencia.h"
#include "../Handler/HandlerBloques.h"
#include <string>

using namespace std;

class PersistidorHash {

private:

	HandlerBloques handler_bloques;

public:

	PersistidorHash() {};
	PersistidorHash(const string& ruta_arch_bloques, const HandlerEspLibre& handler_esp_libre);
	virtual ~PersistidorHash() {};

	void set_handler_bloques(const string& ruta_arch_bloques, const HandlerEspLibre& handler_esp_libre);

	HandlerBloques& get_handler_bloques() { return this->handler_bloques; }

	int guardar_bloque(const Persistencia& cadena);

	void guardar_bloque(const Persistencia& cadena, int num_bloque);

	void recuperar_bloque(int num_bloque, Persistencia& cadena);

};

#endif /* PERSISTIDORHASH_H_ */

