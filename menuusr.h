#ifndef MENUUSR_H
#define MENUUSR_H

//Objetos
#include "usuario.h"
#include "academico.h"
#include "dependiente.h"
#include "formacion.h"
#include "docencia.h"
#include "tutoria.h"
#include "produccion.h"
#include "autor.h"
#include "Lista.h"
#include "listaproduccion.h"

//Dependencias de librerias
#include <fstream>
#include <iostream>
#include <regex>

//Definicion del nombre de archivos
#define ARCH_USR "Usuarios.txt"
#define ARCH_AC "Academicos.txt"
#define ARCH_NO_REG "No_Registro.txt"
#define ARCH_DEPENDIENTE "Dependiente_Academico.txt"
#define ARCH_FORMACION "Formacion_Academica.txt"
#define ARCH_PRODUCCION "Produccion_Academica.txt"
#define ARCH_AUTOR "Autor_Produccion.txt"
#define ARCH_DOCENCIA "Docencia_Academica.txt"
#define ARCH_TUTORIA "Tutoria_academica.txt"

//Definicion del clear o cls junto con el Slash para cada tipo de OS
#ifndef _WIN32
#define CLEAR "clear"
#define MKDIR "mkdir Archivos/"
#define DIR "Archivos/"
#define DIRREP "Reportes/"
#else
#define CLEAR "cls"
#define MKDIR "mkdir Archivos\\"
#define DIR "Archivos\\"
#define DIRREP "Reportes\\"
#endif

using namespace std;

class MenuUsr {
private:
    Academico academico;
    Usuario usuario;
    void pausa();
    void guardaDependiente(Dependiente& dep, const std::string& archivo);
    bool existeDependiente(const std::string& nombre);
    void guardaFormacion(Formacion& form, const std::string& archivo);
    bool existeFormacion(const std::string &tipo, const std::string &nombre);
    void guardaDocencia(Docencia& doc, const std::string& archivo);
    bool existeDocencia(const std::string& nombre);
    void guardaTutoria(Tutoria &tut, const std::string& archivo);
    bool existeTutoria(const std::string& nombreTutorado);
    void guardaProduccion(Produccion &pro, const std::string& archivo);
    bool existeProduccion(const std::string& tipo, const std::string& nombre);
    bool existeNoRegProduccion(const std::string& noRegistro);
    void guardaAutor(Autor& aut, const std::string& archivo);
    bool existeAutor(const std::string& nombre, const std::string& noRegistro);
    bool fechaCorrecta(const std::string& fecha);
    Fecha regresaFecha(std::string& fecha);
    bool formatoNumero(const std::string& numero);
    bool formatoEmail(const std::string& email);
    void creaReporte(Academico& ac);
public:
    MenuUsr();
    MenuUsr(const Academico & academico, const Usuario & usuario);
    void menuPrincipal();
    void infoPersonal();
    void dependientesEconomicos();
    void formacion();
    void produccion();
    void docencia();
    void tutoria();
    void configuracion();
    virtual ~MenuUsr();
};

#endif // MENUUSR_H
