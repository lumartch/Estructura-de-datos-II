#include "fecha.h"

Fecha::Fecha() {
    dia = 0;
    mes = 0;
    anio = 0;
}

Fecha::Fecha(const Fecha &f) : Fecha() {
    dia = f.dia;
    mes = f.mes;
    anio = f.anio;
}

int Fecha::getDia() {
    return dia;
}

void Fecha::setDia(const int &value) {
    dia = value;
}

int Fecha::getMes() {
    return mes;
}

void Fecha::setMes(const int &value) {
    mes = value;
}

int Fecha::getAnio() {
    return anio;
}

void Fecha::setAnio(const int &value) {
    anio = value;
}

std::string Fecha::toString() {
    std::string day = std::to_string(dia);
    std::string month = std::to_string(mes);
    std::string year = std::to_string(anio);
    return day + '/' + month + '/' + year;
}

int Fecha::toInt() {
    return anio*10000 + mes*1000 + dia;
}

Fecha& Fecha::operator=(const Fecha& f) {
    dia = f.dia;
    mes = f.mes;
    anio = f.anio;
    return *this;
}

bool Fecha::operator ==(Fecha &f) {
    return this->toInt() == f.toInt();
}

bool Fecha::operator !=(Fecha &f) {
    return this->toInt() != f.toInt();
}

bool Fecha::operator <(Fecha &f) {
    return this->toInt() < f.toInt();
}

bool Fecha::operator <=(Fecha &f) {
    return this->toInt() <= f.toInt();
}

bool Fecha::operator >(Fecha &f) {
    return this->toInt() > f.toInt();
}

bool Fecha::operator >=(Fecha &f) {
    return this->toInt() >= f.toInt();
}


