#include "usuario.h"

Usuario::Usuario() {
    this->noReg = 0;
    strcpy(this->username, "");
    strcpy(this->password, "");
    strcpy(this->tipo, "");
    this->direccionFisica = 0;
}

Usuario::Usuario(const int& noReg, const std::string& username, const std::string& password, const std::string& tipo, const long int& direccionFisica) {
    this->noReg = noReg;
    strcpy(this->username, username.c_str());
    strcpy(this->password, password.c_str());
    strcpy(this->tipo, tipo.c_str());
    this->direccionFisica = direccionFisica;
}


void Usuario::setNoReg(const int& noReg) {
    this->noReg = noReg;
}

void Usuario::setUsername(const std::string& username) {
    strcpy(this->username, username.c_str());
}

void Usuario::setPassword(const std::string& password) {
    strcpy(this->password, password.c_str());
}

void Usuario::setTipo(const std::string& tipo) {
    strcpy(this->tipo, tipo.c_str());

}

void Usuario::setDireccionFisica(const long int& direccionFisica) {
    this->direccionFisica = direccionFisica;
}

int Usuario::getNoRegistro() {
    return noReg;
}

char* Usuario::getUsername() {
    return username;
}

char* Usuario::getPassword() {
    return password;
}

char* Usuario::getTipo() {
    return tipo;
}

long int Usuario::getDireccionFisica() {
    return direccionFisica;
}

std::string Usuario::toString() {
    std::string res = "Username: " + std::string(username) + " -> Tipo: " + std::string(tipo) + "\n";
    res += "Direccion Física de académico: " + std::to_string(direccionFisica);
    return res;
}


Usuario::~Usuario() {
    //dtor
}


