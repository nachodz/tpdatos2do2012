
#include "Cubo.h"

Cubo::Cubo(int tam_disp) : Bloque(tam_disp) {
	this->esp_libre = TAM_CUBO - this->get_tam();
}

int Cubo::get_tam() {
	Persistencia cadena_aux = this->Serializar();
	return cadena_aux.getTamanio();
}

bool Cubo::esta_vacio() const {
	if (this->regs.empty() == true)
		return true;
	return false;
}

bool Cubo::entra_en_bloque(RegistroHash& reg) const {
	Persistencia cadena;

	int tam = reg.getTamanio();
	cadena.agregarAlFinal(&tam, sizeof(tam));
	cadena.agregarAlFinal(reg.Serializar());

	if (this->esp_libre > (int)cadena.getTamanio())
		return true;

	return false;
}

bool Cubo::entra_en_bloque(int offset) const {
	Persistencia cadena;

	cadena.agregarAlFinal(&offset, sizeof(offset));

	if (this->esp_libre > (int)cadena.getTamanio())
		return true;

	return false;
}

void Cubo::aumentar_esp_libre(int offset) {
	Persistencia cadena;

	cadena.agregarAlFinal(&offset, sizeof(offset));

	this->esp_libre += cadena.getTamanio();
}

void Cubo::disminuir_esp_libre(int offset) {
	Persistencia cadena;

	cadena.agregarAlFinal(&offset, sizeof(offset));

	this->esp_libre -= cadena.getTamanio();
}

void Cubo::agregar_nuevo_reg(RegistroHash& reg) {
	this->regs.push_back(reg);

	Persistencia cadena;

	int tam = reg.getTamanio();
	cadena.agregarAlFinal(&tam, sizeof(tam));
	cadena.agregarAlFinal(reg.Serializar());

	this->esp_libre -= cadena.getTamanio();
}

bool Cubo::eliminar_reg(int clave) {
	list < RegistroHash > ::iterator it;

	it = this->regs.begin();
	while (it != this->regs.end() && (*it).getClave() != clave)
		++ it;

	if (it != this->regs.end() && (*it).getClave() == clave) {
		Persistencia cadena;

		int tam = (*it).getTamanio();
		cadena.agregarAlFinal(&tam, sizeof(tam));
		cadena.agregarAlFinal((*it).Serializar());

		this->esp_libre += cadena.getTamanio();

		this->regs.erase(it);

		return true;
	}

	return false;
}

bool Cubo::existe_reg(int clave) {
	list < RegistroHash > ::iterator it;

	it = this->regs.begin();
	while (it != this->regs.end() && (*it).getClave() != clave)
		++ it;

	if (it != this->regs.end() && (*it).getClave() == clave)
		return true;

	return false;
}

RegistroHash& Cubo::buscar_reg(int clave) {
	list < RegistroHash > ::iterator it;

	it = this->regs.begin();
	while ((*it).getClave() != clave)
		++ it;

	return (*it);
}

void Cubo::vaciar() {
	this->tam_disp = 1;
	this->regs.clear();
	this->esp_libre = TAM_CUBO - this->get_tam();
}

void Cubo::incorporar_regs(list < RegistroHash > & regs) {
	list < RegistroHash > ::iterator it;
	for (it = regs.begin(); it != regs.end(); ++ it)
		this->agregar_nuevo_reg(*it);
}

list < RegistroHash > Cubo::actualizar_regs(int num_bloque, HandlerTabla& handler) {
	list < RegistroHash > ::iterator it;
	list < RegistroHash > list_aux;
	RegistroHash reg_desact;
	int tam;
	unsigned int tam_regs;
	unsigned int contador = 0;

	tam_regs = this->regs.size();
	it = this->regs.begin();

	while (contador != tam_regs) {
		if (num_bloque != handler.get_num_bloque((*it).getClave())) {
			reg_desact = *it;

			Persistencia cadena;

			tam = reg_desact.getTamanio();
			cadena.agregarAlFinal(&tam, sizeof(tam));
			cadena.agregarAlFinal(reg_desact.Serializar());

			this->esp_libre += cadena.getTamanio();

			it = this->regs.erase(it);

			list_aux.push_back(reg_desact);
		}
		else ++ it;
		++ contador;
	}

	return list_aux;
}

Persistencia Cubo::Serializar() {
	Persistencia cadena;

	cadena.agregarAlFinal(&this->tam_disp, sizeof(this->tam_disp));

	int tam = this->regs.size();
	cadena.agregarAlFinal(&tam, sizeof(tam));

	int tam2;
	list < RegistroHash > ::iterator it;
	for (it = this->regs.begin(); it != this->regs.end(); ++ it) {
		tam2 = (*it).getTamanio();
		cadena.agregarAlFinal(&tam2, sizeof(tam2));
		cadena.agregarAlFinal((*it).Serializar());
	}

	return cadena;
}

bool Cubo::Hidratar(Persistencia& cadena) {
	this->vaciar();

	int offset = 0;

	this->tam_disp = cadena.leerEntero(offset);
	offset += sizeof(this->tam_disp);

	int tam1 = cadena.leerEntero(offset);
	offset += sizeof(tam1);

	int tam2;
	for (int i = 0; i < tam1; ++ i) {
		tam2 = cadena.leerEntero(offset);
		offset += sizeof(tam2);
		Persistencia cadena_aux;
		cadena_aux = cadena.leer(offset, tam2);
		RegistroHash reg;
		reg.Hidratar(cadena_aux);
		this->agregar_nuevo_reg(reg);
		offset += tam2;
	}

	return true;
}

void Cubo::toString(ostream& os) {
	os << "Bloque --> " << endl;
	os << "  Tamaño de dispersión:   " << this->tam_disp << endl;
	os << "  Cantidad de espacio libre:   " << this->esp_libre << endl;

	list < RegistroHash > ::iterator it;
	for (it = this->regs.begin(); it != this->regs.end(); ++ it)
		(*it).toString(os);
}


int Cubo::getEspLibre(){
	return this->esp_libre;
}
