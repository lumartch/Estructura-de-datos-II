#ifndef LISTAPRODUCCION_H
#define LISTAPRODUCCION_H

#include <string>
#include <cstring>
#include "produccion.h"

class NodoProduccion {
private:
    Produccion dato;
    NodoProduccion* siguiente;
    NodoProduccion* anterior;
public:
    NodoProduccion();
    NodoProduccion(const Produccion &dato);
    void setDato(const Produccion &dato);
    void setSiguiente(NodoProduccion* sig);
    void setAnterior(NodoProduccion* ant);
    Produccion& getDato();
    NodoProduccion* getSiguiente();
    NodoProduccion* getAnterior();
};

class ListaProduccion {
public:
    ListaProduccion();
    virtual ~ListaProduccion();
    bool estaVacia();
    void insertar(NodoProduccion* nodo, Produccion &dato);
    NodoProduccion* primerPos();
    NodoProduccion* ultimaPos();
    NodoProduccion* posSiguiente(NodoProduccion* nodo);
    NodoProduccion* posAnterior(NodoProduccion* nodo);
    Produccion& operator[](const int &pos);
    void eliminarNodos();
    int datosTotales();
    std::string toString();
private:
    NodoProduccion* ancla;
    int cont;
    bool posValida(NodoProduccion* nodo);
};
#endif // LISTAPRODUCCION_H
