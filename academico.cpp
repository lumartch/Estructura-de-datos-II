#include "academico.h"

Academico::Academico() {
    this->noReg = 0;
    strcpy(this->nombre, "N/A");
    strcpy(this->domicilio, "N/A");
    strcpy(this->ciudad, "N/A");
    strcpy(this->telefono, "N/A");
    strcpy(this->email, "N/A");
    strcpy(this->estadoCivil, "N/A");
}

Academico::Academico(const int & noReg, const std::string& nombre, const std::string& domicilio, const std::string& ciudad, const std::string& telefono, const std::string& email, const std::string& estadoCivil) {
    this->noReg = noReg;
    strcpy(this->nombre, nombre.c_str());
    strcpy(this->domicilio, domicilio.c_str());
    strcpy(this->ciudad, ciudad.c_str());
    strcpy(this->telefono, telefono.c_str());
    strcpy(this->email, email.c_str());
    strcpy(this->estadoCivil, estadoCivil.c_str());
}

void Academico::setNoReg(const int& noReg) {
    this->noReg = noReg;
}

void Academico::setNombre(const std::string& nombre) {
    strcpy(this->nombre, nombre.c_str());
}

void Academico::setDomicilio(const std::string& domicilio) {

    strcpy(this->domicilio, domicilio.c_str());
}

void Academico::setCiudad(const std::string& ciudad) {
    strcpy(this->ciudad, ciudad.c_str());

}

void Academico::setTelefono(const std::string& telefono) {
    strcpy(this->telefono, telefono.c_str());

}

void Academico::setEmail(const std::string& email) {
    strcpy(this->email, email.c_str());

}

void Academico::setEstadoCivil(const std::string& estadoCivil) {
    strcpy(this->estadoCivil, estadoCivil.c_str());

}

int Academico::getNoReg() {
    return noReg;
}

char* Academico::getNombre() {
    return nombre;
}

char* Academico::getDomicilio() {
    return domicilio;
}

char* Academico::getCiudad() {
    return ciudad;
}

char* Academico::getTelefono() {
    return telefono;
}

char* Academico::getEmail() {
    return email;
}

char* Academico::getEstadoCivil() {
    return estadoCivil;
}

std::string Academico::toString() {
    std::string res = "Nombre: " + std::string(nombre) + " -> Email: " + std::string(email) + "\n";
    res += "Ciudad: "+ std::string(ciudad) + " -> Domicilio: " + std::string(domicilio) + "\n";
    res += "Telefono: "+ std::string(telefono) + " -> Estado Civil: " + std::string(estadoCivil);
    return res;
}


Academico::~Academico() {
    //dtor
}
