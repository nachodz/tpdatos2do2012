
#ifndef HASHPALABRA_H_
#define HASHPALABRA_H_

#include "../Persistencia/PersistidorHash.h"
#include "../Comun/Cubo.h"
#include "RegistroHash.h"
#include <string>

using namespace std;

class Hash {

private :

	HandlerTabla handler_tabla;
	PersistidorHash persistor;

	void insertar_reg(RegistroHash& reg);

	void obtener_reg(RegistroHash& reg, Cubo& bloque_sig ,list < int > & bloques_sigs, int clave);

	void eliminar_reg_y_bloques_sigs(Cubo& bloque, int num_bloque, int clave);

	bool eliminar_reg(int clave);

	list < int > consultar_offsets(Cubo& bloque, int num_bloque, int clave);

	void mostrar(ostream& os);

	void crear_condiciones_iniciales();

	void actualizar(Cubo& bloque, int num_bloque, RegistroHash& reg, Autor* autor,string frase);

public:

	Hash(const string& ruta_arch_bloques, const string& ruta_arch_esp_libre,
			const string& ruta_arch_tabla);

	virtual ~Hash() {};

	void alta(int clave, Autor* autor, string frase);

	void baja(int clave);

	list < int > consultar(int clave);
	RegistroHash consultar(int clave,int sacar);

	void mostrar(const string& nombre_arch);

	void mostrar();

	void modificar(int clave, Autor* autor,string frase);

	void cargaInicial();

	int getCantidadBloques();

	list<RegistroHash> getRegistrosPorBloque(int nroBloque);

};

#endif /* HASH_H_ */
