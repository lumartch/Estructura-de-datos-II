#include "formacion.h"

Formacion::Formacion() {
    this->noReg = 0;
    strcpy(this->tipo, "");
    strcpy(this->nombre, "");
    strcpy(this->institucion, "");
    strcpy(this->cedula, "");
}

void Formacion::setNoReg(const int& noReg) {
    this->noReg = noReg;
}

void Formacion::setTipo(const std::string& tipo) {
    strcpy(this->tipo, tipo.c_str());
}

void Formacion::setNombre(const std::string& nombre) {
    strcpy(this->nombre, nombre.c_str());
}

void Formacion::setInstitucion(const std::string& institucion) {
    strcpy(this->institucion, institucion.c_str());
}

void Formacion::setFechaInicio(const Fecha& fechaInicio) {
    this->fechaInicio = fechaInicio;
}

void Formacion::setFechaFinal(const Fecha& fechaFinal) {
    this->fechaFinal = fechaFinal;
}

void Formacion::setFechaObtencion(const Fecha& fechaObtencion) {
    this->fechaObtencion = fechaObtencion;
}

void Formacion::setCedula(const std::string& cedula) {
    strcpy(this->cedula, cedula.c_str());
}

int Formacion::getNoReg() {
    return noReg;
}

char* Formacion::getTipo() {
    return tipo;
}

char* Formacion::getNombre() {
    return nombre;
}

char* Formacion::getInstitucion() {
    return institucion;
}

Fecha Formacion::getFechaInicio() {
    return fechaInicio;
}

Fecha Formacion::getFechaFinal() {
    return fechaFinal;
}

Fecha Formacion::getFechaObtencion() {
    return fechaObtencion;
}

char* Formacion::getCedula() {
    return cedula;
}


Formacion::~Formacion() {
    //dtor
}
