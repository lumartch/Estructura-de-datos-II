#ifndef AUTOR_H
#define AUTOR_H

#include <string>
#include <cstring>

class Autor {
private:
    char noRegistro[50];
    char nombre[100];
public:
    Autor();
    void setNoRegistro(const std::string&noRegistro);
    void setNombre(const std::string& nombre);
    char* getNoRegistro();
    char* getNombre();
    virtual ~Autor();
};

#endif // AUTOR_H
