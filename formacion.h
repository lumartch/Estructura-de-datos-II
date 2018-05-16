#ifndef FORMACION_H
#define FORMACION_H

#include "fecha.h"

class Formacion {
private:
    int noReg;
    char tipo[30];
    char nombre[100];
    char institucion[100];
    Fecha fechaInicio;
    Fecha fechaFinal;
    Fecha fechaObtencion;
    char cedula[50];
public:
    Formacion();
    void setNoReg(const int & noReg);
    void setTipo(const std::string &tipo);
    void setNombre(const std::string &nombre);
    void setInstitucion(const std::string &institucion);
    void setFechaInicio(const Fecha& fechaInicio);
    void setFechaFinal(const Fecha& fechaFinal);
    void setFechaObtencion(const Fecha& fechaObtencion);
    void setCedula(const std::string &cedula);
    int getNoReg();
    char* getTipo();
    char* getNombre();
    char* getInstitucion();
    Fecha getFechaInicio();
    Fecha getFechaFinal();
    Fecha getFechaObtencion();
    char* getCedula();
    virtual ~Formacion();

};

#endif // FORMACION_H
