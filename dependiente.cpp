#include "dependiente.h"

Dependiente::Dependiente() {
    this->noReg = 0;
    strcpy(this->nombre, "");
    this->edad = 0;
}

void Dependiente::setNoReg(const int& noReg) {
    this->noReg = noReg;
}

void Dependiente::setNombre(const std::string& nombre) {
    strcpy(this->nombre, nombre.c_str());
}

void Dependiente::setEdad(const int& edad) {
    this->edad = edad;
}

int Dependiente::getNoReg() {
    return noReg;
}

char* Dependiente::getNombre() {
    return nombre;
}

int Dependiente::getEdad() {
    return edad;
}


Dependiente::~Dependiente() {
    //dtor
}
