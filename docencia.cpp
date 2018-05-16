#include "docencia.h"

Docencia::Docencia() {
    this->noReg = 0;
    strcpy(this->nombre, "");
    strcpy(this->cantidadHoras, "");
}

void Docencia::setNoReg(const int& noReg) {
    this->noReg = noReg;
}


void Docencia::setNombre(const std::string& nombre) {
    strcpy(this->nombre, nombre.c_str());

}

void Docencia::setFechaInicio(const Fecha& fechaInicio) {
    this->fechaInicio = fechaInicio;
}

void Docencia::setFechaFin(const Fecha& fechaFin) {
    this->fechaFin = fechaFin;
}

void Docencia::setCantidadHoras(const std::string& cantidadHoras) {
    strcpy(this->cantidadHoras, cantidadHoras.c_str());

}

int Docencia::getNoReg() {
    return noReg;
}

char* Docencia::getNombre() {
    return nombre;
}

Fecha Docencia::getFechaInicio() {
    return fechaInicio;
}

Fecha Docencia::getFechaFin() {
    return fechaFin;
}

char* Docencia::getCantidadHoras() {
    return cantidadHoras;
}

Docencia::~Docencia() {
    //dtor
}
