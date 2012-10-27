
#include "Hash.h"
#include "../Constantes.h"

Hash::Hash(const string& ruta_arch_bloques, const string& ruta_arch_esp_libre,
		const string& ruta_arch_tabla) {
	HandlerEspLibre handler_esp_libre(ruta_arch_esp_libre);
	this->persistor.set_handler_bloques(ruta_arch_bloques, handler_esp_libre);

	this->handler_tabla.set_ruta_arch_tabla(ruta_arch_tabla);

	this->crear_condiciones_iniciales();
}

void Hash::crear_condiciones_iniciales() {
	HandlerBloques& handler_bloques = this->persistor.get_handler_bloques();
	handler_bloques.crear_arch_vacio();
	handler_bloques.get_handler_esp_libre().crear_arch_inicial();
	this->handler_tabla.crear_tabla_inicial();

	if (this->handler_tabla.tabla_vacia() == true) {
		Cubo bloque;

		int num_bloque = this->persistor.guardar_bloque(bloque.Serializar());
		this->handler_tabla.insertar_primer_referencia(num_bloque);
	}
}

void Hash::insertar_reg(RegistroHash& reg) {
	Persistencia cadena;
	Cubo bloque;

	int pos_tabla_bloque = this->handler_tabla.get_pos_tabla(reg.getClave());
	int num_bloque = this->handler_tabla.get_num_bloque(reg.getClave());
	this->persistor.recuperar_bloque(num_bloque, cadena);
	bloque.Hidratar(cadena);

	if (bloque.entra_en_bloque(reg) == true) {
		bloque.agregar_nuevo_reg(reg);
		this->persistor.guardar_bloque(bloque.Serializar(), num_bloque);
	}
	else {
		int tam_disp_inicial = bloque.get_tam_disp();
		bloque.duplicar_tam_disp();
		Cubo nuevo_bloque(bloque.get_tam_disp());
		int num_nuevo_bloque = this->persistor.guardar_bloque(nuevo_bloque.Serializar());

		if (tam_disp_inicial == this->handler_tabla.get_tam_tabla()) {
			this->handler_tabla.duplicar_tabla();
			this->handler_tabla.reemplazar_referencia(num_bloque, num_nuevo_bloque);
		}
		else this->handler_tabla.reemplazar_referencias(pos_tabla_bloque, num_nuevo_bloque, nuevo_bloque);

		list < RegistroHash > regs_desactualizados = bloque.actualizar_regs(num_bloque, this->handler_tabla);

		if (regs_desactualizados.empty() == false) {
			nuevo_bloque.incorporar_regs(regs_desactualizados);
			this->persistor.guardar_bloque(nuevo_bloque.Serializar(), num_nuevo_bloque);
		}

		this->persistor.guardar_bloque(bloque.Serializar(), num_bloque);
		this->insertar_reg(reg);
	}
}

void Hash::actualizar(Cubo& bloque, int num_bloque, RegistroHash& reg, Autor* autor,string frase) {

	int nuevoEspLibre = bloque.getEspLibre() + reg.getTamanio();
	int nuevoTamReg = reg.getTamanio() - reg.getAutor()->getTamanio() - reg.getFrase().length() + autor->getTamanio() + frase.length();

	if (nuevoEspLibre > nuevoTamReg) {
		reg.actualizar(autor,frase);
		bloque.disminuir_esp_libre(autor->getTamanio() + frase.length());
		this->persistor.guardar_bloque(bloque.Serializar(), num_bloque);
	}
	else {
		Cubo bloque_sig;

		if (reg.getBloqueSiguiente() == -1) {
			RegistroHash reg_aux(reg.getClave());
			reg.actualizar(autor,frase);
			bloque_sig.agregar_nuevo_reg(reg_aux);
			int num_bloque_sig = this->persistor.guardar_bloque(bloque_sig.Serializar());
			reg.setBloqueSiguiente(num_bloque_sig);
			this->persistor.guardar_bloque(bloque.Serializar(), num_bloque);
		}
		else {
			Persistencia cadena;
			this->persistor.recuperar_bloque(reg.getBloqueSiguiente(), cadena);
			bloque_sig.Hidratar(cadena);
			RegistroHash& reg_aux = bloque_sig.buscar_reg(reg.getClave());
			this->actualizar(bloque_sig, reg.getBloqueSiguiente(), reg_aux, autor,frase);
		}
	}
}


/*void Hash::agregar_nuevo_offset(Cubo& bloque, int num_bloque, RegistroHash& reg, int offset) {
	if (bloque.entra_en_bloque(offset) == true) {
		reg.agregar_nuevo_offset(offset);
		bloque.disminuir_esp_libre(offset);
		this->persistor.guardar_bloque(bloque.Serializar(), num_bloque);
	}
	else {
		Cubo bloque_sig;

		if (reg.get_bloque_sig() == -1) {
			RegistroHash reg_aux(reg.getClave());
			reg_aux.agregar_nuevo_offset(offset);
			bloque_sig.agregar_nuevo_reg(reg_aux);
			int num_bloque_sig = this->persistor.guardar_bloque(bloque_sig.Serializar());
			reg.set_bloque_sig(num_bloque_sig);
			this->persistor.guardar_bloque(bloque.Serializar(), num_bloque);
		}
		else {
			Persistencia cadena;
			this->persistor.recuperar_bloque(reg.get_bloque_sig(), cadena);
			bloque_sig.Hidratar(cadena);
			RegistroHash& reg_aux = bloque_sig.buscar_reg(reg.getClave());
			this->agregar_nuevo_offset(bloque_sig, reg.get_bloque_sig(), reg_aux, offset);
		}
	}
}*/

void Hash::alta(int clave, Autor* autor,string frase) {
	Persistencia cadena;
	Cubo bloque;

//	int num_bloque = this->handler_tabla.get_num_bloque(clave);
//	this->persistor.recuperar_bloque(num_bloque, cadena);
//	bloque.Hidratar(cadena);

//	if (bloque.existe_reg(clave) == true)
//		this->agregar_nuevo_offset(bloque, num_bloque, bloque.buscar_reg(clave), offset);
//	else {
		RegistroHash reg(clave,autor,frase);
		//reg.agregar_nuevo_offset(offset);
		this->insertar_reg(reg);
	//}

}

void Hash::modificar(int clave, Autor* autor,string frase) {
	Persistencia cadena;
	Cubo bloque;

	int num_bloque = this->handler_tabla.get_num_bloque(clave);
	this->persistor.recuperar_bloque(num_bloque, cadena);
	bloque.Hidratar(cadena);

	if (bloque.existe_reg(clave) == true)
		this->actualizar(bloque, num_bloque, bloque.buscar_reg(clave), autor,frase);
	else {
		//TODO: generalizar errores
		cout << "MODIFICACION: Registro no existe!!" << endl;
	}

}


bool Hash::eliminar_reg(int clave) {
	Persistencia cadena;
	Cubo bloque;

	int pos_tabla_bloque = this->handler_tabla.get_pos_tabla(clave);
	int num_bloque = this->handler_tabla.get_num_bloque(clave);
	this->persistor.recuperar_bloque(num_bloque, cadena);
	bloque.Hidratar(cadena);

	if (!bloque.eliminar_reg(clave))
		return false;

	if (bloque.esta_vacio() == true) {
		int num_otro_bloque = this->handler_tabla.puedo_liberar_bloque(bloque, pos_tabla_bloque);
		if (num_otro_bloque != -1) {
			Cubo otro_bloque;

			this->persistor.recuperar_bloque(num_otro_bloque, cadena);
			otro_bloque.Hidratar(cadena);
			this->handler_tabla.liberar_referencias(pos_tabla_bloque, num_otro_bloque, otro_bloque);
			otro_bloque.truncar_tam_disp();
			this->persistor.guardar_bloque(otro_bloque.Serializar(), num_otro_bloque);
			this->persistor.get_handler_bloques().eliminar_bloque(num_bloque);

			if (this->handler_tabla.mitades_iguales() == true)
				this->handler_tabla.truncar_tabla();
		}
		else {
			bloque.get_regs().clear();
			this->persistor.guardar_bloque(bloque.Serializar(), num_bloque);
		}
	}
	else this->persistor.guardar_bloque(bloque.Serializar(), num_bloque);

	return true;
}

void Hash::obtener_reg(RegistroHash& reg, Cubo& bloque_sig, list < int > & bloques_sigs, int clave) {
	Persistencia cadena;

	this->persistor.recuperar_bloque(reg.getBloqueSiguiente(), cadena);
	bloque_sig.Hidratar(cadena);
	bloques_sigs.push_back(reg.getBloqueSiguiente());
	reg = bloque_sig.buscar_reg(clave);
}

void Hash::eliminar_reg_y_bloques_sigs(Cubo& bloque, int num_bloque, int clave) {
	if (bloque.existe_reg(clave) == true) {
		RegistroHash& reg = bloque.buscar_reg(clave);

		//TODO: modifique!!
		if (reg.getBloqueSiguiente() != -1) {
			Cubo bloque_sig;
			list < int > bloques_sigs;

			this->obtener_reg(reg, bloque_sig, bloques_sigs, clave);

			while (reg.getBloqueSiguiente() != -1)
				this->obtener_reg(reg, bloque_sig, bloques_sigs, clave);

			if (reg.getBloqueSiguiente() == -1) {
				list < int > ::iterator it;

				for (it = bloques_sigs.begin(); it != bloques_sigs.end(); ++ it)
					this->persistor.get_handler_bloques().eliminar_bloque(*it);

				this->eliminar_reg(clave);
			}
		}
		else
			this->eliminar_reg(clave);

		/*if (reg.vacio() == true)
			this->eliminar_reg(clave);
		else {
			if (reg.getBloqueSiguiente() != -1) {
				Cubo bloque_sig;
				list < int > bloques_sigs;

				this->obtener_reg(reg, bloque_sig, bloques_sigs, clave);

				while (reg.getBloqueSiguiente() != -1)
					this->obtener_reg(reg, bloque_sig, bloques_sigs, clave);

				if (reg.getBloqueSiguiente() == -1) {
					list < int > ::iterator it;

					for (it = bloques_sigs.begin(); it != bloques_sigs.end(); ++ it)
						this->persistor.get_handler_bloques().eliminar_bloque(*it);

					this->eliminar_reg(clave);
				}
			}*/
			/*if (reg.get_offsets().empty() == true && reg.get_bloque_sig() != -1) {
				Cubo bloque_sig;
				list < int > bloques_sigs;

				this->obtener_reg(reg, bloque_sig, bloques_sigs, clave);

				while (reg.get_offsets().empty() == true && reg.get_bloque_sig() != -1)
					this->obtener_reg(reg, bloque_sig, bloques_sigs, clave);

				if (reg.get_offsets().empty() == true && reg.get_bloque_sig() == -1) {
					list < int > ::iterator it;

					for (it = bloques_sigs.begin(); it != bloques_sigs.end(); ++ it)
						this->persistor.get_handler_bloques().eliminar_bloque(*it);

					this->eliminar_reg(clave);
				}
			}*/

	}
}

/*void Hash::eliminar_offset(Cubo& bloque, int num_bloque, int clave, int offset) {
	if (bloque.existe_reg(clave) == true) {
		RegistroHash& reg = bloque.buscar_reg(clave);

		if (reg.eliminar_offset(offset) == false) {
			if (reg.get_bloque_sig() == -1)
				return;
			else {
				Persistencia cadena;
				Cubo bloque_sig;

				this->persistor.recuperar_bloque(reg.get_bloque_sig(), cadena);
				bloque_sig.Hidratar(cadena);
				this->eliminar_offset(bloque_sig, reg.get_bloque_sig(), clave, offset);
			}
		}
		else {
			bloque.aumentar_esp_libre(offset);
			this->persistor.guardar_bloque(bloque.Serializar(), num_bloque);
		}
	}
}*/

void Hash::baja(int clave) {
	Persistencia cadena;
	Cubo bloque;

	int num_bloque = this->handler_tabla.get_num_bloque(clave);
	this->persistor.recuperar_bloque(num_bloque, cadena);
	bloque.Hidratar(cadena);

	//this->eliminar_offset(bloque, num_bloque, clave, offset);
	this->eliminar_reg_y_bloques_sigs(bloque, num_bloque, clave);
}

/*void Hash::concatenar_offsets(list < int > & lista_1, list < int > & lista_2) {
	list < int > ::iterator it;
	for (it = lista_2.begin(); it != lista_2.end(); ++ it)
		lista_1.push_back(*it);
}*/

/*list < int > Hash::consultar_offsets(Cubo& bloque, int num_bloque, int clave) {
	Persistencia cadena;
	list < int > lista_1;

	if (bloque.existe_reg(clave) == true) {
		bool fin_lista = false;

		while (fin_lista == false) {
			RegistroHash& reg = bloque.buscar_reg(clave);
			list < int > lista_2 = reg.get_offsets();
			this->concatenar_offsets(lista_1, lista_2);
			if (reg.get_bloque_sig() != -1) {
				this->persistor.recuperar_bloque(reg.get_bloque_sig(), cadena);
				bloque.Hidratar(cadena);
			}
			else fin_lista = true;
		}
	}

	return lista_1;
}*/

list < int > Hash::consultar(int clave) {
	Persistencia cadena;
	Cubo bloque;

	int num_bloque = this->handler_tabla.get_num_bloque(clave);
	if (num_bloque != -1) {
		this->persistor.recuperar_bloque(num_bloque, cadena);
		bloque.Hidratar(cadena);
		//TODO: ver!
		//return this->consultar_offsets(bloque, num_bloque, clave);
	}
	list < int > vacia;
	return vacia;
}

RegistroHash Hash::consultar(int clave,int sacar) {
	Persistencia cadena;
	Cubo bloque;

	int num_bloque = this->handler_tabla.get_num_bloque(clave);
	if (num_bloque != -1) {
		this->persistor.recuperar_bloque(num_bloque, cadena);
		bloque.Hidratar(cadena);
		RegistroHash& reg = bloque.buscar_reg(clave);
		return reg;
	}
	//TODO: ver!
	return RegistroHash();
}


void Hash::mostrar(ostream& os) {
	Persistencia cadena;
	Cubo bloque;
	int cant_bloques = this->persistor.get_handler_bloques().get_tam_arch_bloques() / HASH_TAM_CUBO;

	os << "********************************************************************************" << endl;
	os << "		                               Hash                                        " << endl;
	os << "********************************************************************************" << endl;
	os << endl;

	for (int i = 0; i < cant_bloques; ++ i) {
		os << "N° " << i << ":" << endl;
		this->persistor.recuperar_bloque(i, cadena);
		bloque.Hidratar(cadena);
		bloque.toString(os);
		os << endl;
	}
}

void Hash::mostrar(const string& nombre_arch) {
	ofstream arch;

	arch.open(nombre_arch.c_str(), fstream::out);
	this->mostrar(arch);
	arch.close();
}

void Hash::mostrar() {
	this->mostrar(cout);
}

void Hash::cargaInicial(){

	ifstream inFile (PATH_FRASES);
	string line;
	string apellido;
	string nombre;
	string frase;
	Autor* autor;
	int n;

	int cant = 0;
	while (getline (inFile, line))
	{
		istringstream linestream(line);
		string item;
		int contCampos = 1;
		//CSV separado por Tab's
		while (getline (linestream, item, '\t'))
		{
		   if(contCampos==1){
			   apellido = item;
			   contCampos++;
		   }
		   else
			   if(contCampos==2){
					nombre = item;
					contCampos++;
			   }
			   else
				   frase = item;

		}

		//elección del n random
		n = 100000000+rand()%(200000001);

		if ((apellido.length() == 0 && nombre.length() == 0)|| (apellido == "Anonimo"))
			this->alta(n,NULL,frase);
		else
			if(nombre.length() == 0){
				autor = new Autor(apellido,"");
				this->alta(n,autor,frase);
				//delete autor;
			}
			else{
				autor = new Autor(apellido,nombre);
				this->alta(n,autor,frase);
				//delete autor;
			}
		//delete autor;
		cant++;
	}

	//hash.mostrar(NOM_SALIDA);

}

//Métodos para recorrer secuencialmente el archivo directo.

int Hash::getCantidadBloques(){
	return this->handler_tabla.getCantidadBloques();
}

list<RegistroHash> Hash::getRegistrosPorBloque(int num_bloque){
	Persistencia cadena;
	Cubo bloque;

	this->persistor.recuperar_bloque(num_bloque, cadena);
	bloque.Hidratar(cadena);
	return bloque.get_regs();
}
