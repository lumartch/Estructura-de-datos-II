#ifndef TUTORIA_H
#define TUTORIA_H

#include<string>
#include<cstring>
#include "fecha.h"

class Tutoria {
private:
    int noReg;
    char nombreTutorado[30];
    Fecha fechaInicio;
    Fecha fechaFin;
    char cantidadHoras[20];
public:
    Tutoria();
    void setNoReg(const int &noReg);
    void setNombreTutorado(const std::string &nombreTutorado);
    void setFechaInicio(const Fecha &fechaInicio);
    void setFechaFin(const Fecha &fechaFin);
    void setCantidadHoras(const std::string &cantidadHoras);
    int getNoReg();
    char* getNombreTutorado();
    Fecha getFechaInicio();
    Fecha getFechaFin();
    char* getCantidadHoras();
    virtual ~Tutoria();

};

#endif // TUTORIA_H
