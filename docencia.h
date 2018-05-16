#ifndef DOCENCIA_H
#define DOCENCIA_H

#include<string>
#include<cstring>
#include "fecha.h"

class Docencia {
private:
    int noReg;
    char nombre[50];
    Fecha fechaInicio;
    Fecha fechaFin;
    char cantidadHoras[10];
public:
    Docencia();
    void setNoReg(const int& noReg);
    void setNombre(const std::string &nombre);
    void setFechaInicio(const Fecha &fechaInicio);
    void setFechaFin(const Fecha &fechaFin);
    void setCantidadHoras(const std::string &cantidadHoras);
    int getNoReg();
    char* getNombre();
    Fecha getFechaInicio();
    Fecha getFechaFin();
    char* getCantidadHoras();
    virtual ~Docencia();

};

#endif // DOCENCIA_H
