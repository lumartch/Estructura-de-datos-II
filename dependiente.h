#ifndef DEPENDIENTE_H
#define DEPENDIENTE_H

#include <string>
#include <cstring>

class Dependiente
{
private:
    int noReg;
    char nombre[100];
    int edad;
public:
    Dependiente();
    void setNoReg(const int& noReg);
    void setNombre(const std::string& nombre);
    void setEdad(const int& edad);
    int getNoReg();
    char* getNombre();
    int getEdad();
    virtual ~Dependiente();
};

#endif // DEPENDIENTE_H
