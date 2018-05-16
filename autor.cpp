#include "autor.h"

Autor::Autor() {
    strcpy(this->noRegistro, "");
    strcpy(this->nombre, "");
}

void Autor::setNoRegistro(const std::string& noRegistro) {
    strcpy(this->noRegistro, noRegistro.c_str());
}

void Autor::setNombre(const std::string& nombre) {
    strcpy(this->nombre, nombre.c_str());
}

char* Autor::getNoRegistro() {
    return noRegistro;
}

char* Autor::getNombre() {
    return nombre;
}

Autor::~Autor() {
    //dtor
}
