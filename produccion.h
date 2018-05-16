#ifndef PRODUCCION_H
#define PRODUCCION_H

#include <string>
#include <cstring>
#include "fecha.h"

class Produccion {
private:
    //No Reg es el valor con el que se identifica con el academico
    int noReg;
    char tipo[50];
    char nombre[100];
    Fecha fechaElaboracion;
    //NoRegistro es el valor propio de la produccion
    char noRegistro[50];
    char status[50];
public:
    Produccion();
    void setNoReg(const int& noReg);
    void setTipo(const std::string& tipo);
    void setNombre(const std::string& nombre);
    void setFechaElaboracion(const Fecha & fechaElaboracion);
    void setNoRegistro(const std::string& noRegistro);
    void setStatus(const std::string& status);
    int getNoReg();
    char* getTipo();
    char* getNombre();
    Fecha getFechaElaboracion();
    char* getNoRegistro();
    char* getStatus();
    virtual ~Produccion();

};

#endif // PRODUCCION_H
