#include "tutoria.h"

Tutoria::Tutoria() {
    this->noReg = 0;
    strcpy(this->nombreTutorado, "");
    strcpy(this->cantidadHoras, "");
}
void Tutoria::setNoReg(const int& noReg) {
    this->noReg = noReg;
}


void Tutoria::setNombreTutorado(const std::string& nombreTutorado) {
    strcpy(this->nombreTutorado, nombreTutorado.c_str());

}

void Tutoria::setFechaInicio(const Fecha& fechaInicio) {
    this->fechaInicio = fechaInicio;
}

void Tutoria::setFechaFin(const Fecha& fechaFin) {
    this->fechaFin = fechaFin;
}

void Tutoria::setCantidadHoras(const std::string& cantidadHoras) {
    strcpy(this->cantidadHoras, cantidadHoras.c_str());

}

int Tutoria::getNoReg() {
    return noReg;
}

char* Tutoria::getNombreTutorado() {
    return nombreTutorado;
}

Fecha Tutoria::getFechaInicio() {
    return fechaInicio;
}

Fecha Tutoria::getFechaFin() {
    return fechaFin;
}

char* Tutoria::getCantidadHoras() {
    return cantidadHoras;
}


Tutoria::~Tutoria() {
    //dtor
}
