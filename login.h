#ifndef LOGIN_H
#define LOGIN_H

#include "menuadmin.h"

class Login {
private:
    //Arbol avl;
    Academico academico;
    Usuario usuario;
public:
    Login();
    void menuLogin();
    void buscarUsuario(const std::string& username, const std::string& password);
    void crearArchivosDefecto();
    void pausa();
    virtual ~Login();
};

#endif // LOGIN_H
