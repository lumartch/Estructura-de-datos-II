#ifndef LISTA_H
#define LISTA_H

#include <string>
#include <cstring>
#include "academico.h"

class Nodo {
private:
    Academico dato;
    Nodo* siguiente;
    Nodo* anterior;
public:
    Nodo();
    Nodo(const Academico &dato);
    void setDato(const Academico &dato);
    void setSiguiente(Nodo* sig);
    void setAnterior(Nodo* ant);
    Academico& getDato();
    Nodo* getSiguiente();
    Nodo* getAnterior();
};

class Lista {
public:
    Lista();
    virtual ~Lista();
    bool estaVacia();
    void insertar(Nodo*, Academico &dato);
    Nodo* primerPos();
    Nodo* ultimaPos();
    Nodo* posSiguiente(Nodo* nodo);
    Nodo* posAnterior(Nodo* nodo);
    Academico& operator[](const int &pos);
    void eliminarNodos();
    int datosTotales();
    std::string toString();
private:
    Nodo* ancla;
    int cont;
    bool posValida(Nodo* nodo);
};

#endif // LISTA_H
