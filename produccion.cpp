#include "produccion.h"

Produccion::Produccion() {
    //ctor
}

Produccion::~Produccion() {
    //dtor
}

void Produccion::setNoReg(const int& noReg) {
    this->noReg = noReg;
}


void Produccion::setTipo(const std::string& tipo) {
    strcpy(this->tipo, tipo.c_str());

}

void Produccion::setNombre(const std::string& nombre) {
    strcpy(this->nombre, nombre.c_str());

}

void Produccion::setFechaElaboracion(const Fecha& fechaElaboracion) {
    this->fechaElaboracion = fechaElaboracion;
}

void Produccion::setNoRegistro(const std::string& noRegistro) {
    strcpy(this->noRegistro, noRegistro.c_str());

}

void Produccion::setStatus(const std::string& status) {
    strcpy(this->status, status.c_str());
}

int Produccion::getNoReg() {
    return noReg;
}

char* Produccion::getTipo() {
    return tipo;
}

char* Produccion::getNombre() {
    return nombre;
}

Fecha Produccion::getFechaElaboracion() {
    return fechaElaboracion;
}

char* Produccion::getNoRegistro() {
    return noRegistro;
}

char* Produccion::getStatus() {
    return status;
}
