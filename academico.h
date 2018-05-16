#ifndef ACADEMICO_H
#define ACADEMICO_H

#include<string>
#include<cstring>

class Academico {
private:
    int noReg;
    char nombre[100];
    char domicilio[100];
    char ciudad[100];
    char telefono[15];
    char email[50];
    char estadoCivil[15];
    //char fotografia[50];
public:
    Academico();
    Academico(const int& noReg, const std::string& nombre,
              const std::string& domicilio, const std::string& ciudad, const std::string& telefono,
              const std::string& email, const std::string& estadoCivil);
    void setNoReg(const int &noReg);
    void setNombre(const std::string& nombre);
    void setDomicilio(const std::string& domicilio);
    void setCiudad(const std::string& ciudad);
    void setTelefono(const std::string& telefono);
    void setEmail(const std::string& email);
    void setEstadoCivil(const std::string& estadoCivil);
    //void setFotografia(const std::string& fotografia);
    int getNoReg();
    char* getNombre();
    char* getDomicilio();
    char* getCiudad();
    char* getTelefono();
    char* getEmail();
    char* getEstadoCivil();
    //char* getFotografia();
    std::string toString();
    virtual ~Academico();
};

#endif // ACADEMICO_H
