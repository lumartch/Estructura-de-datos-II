#include "listaproduccion.h"

NodoProduccion::NodoProduccion() {
    siguiente = nullptr;
    anterior = nullptr;
}

NodoProduccion::NodoProduccion(const Produccion& dato) : NodoProduccion() {
    this->dato = dato;
}

void NodoProduccion::setDato(const Produccion& dato) {
    this->dato = dato;
}

void NodoProduccion::setSiguiente(NodoProduccion* sig) {
    siguiente = sig;
}

void NodoProduccion::setAnterior(NodoProduccion* ant) {
    anterior = ant;
}

Produccion& NodoProduccion::getDato() {
    return dato;
}

NodoProduccion* NodoProduccion::getSiguiente() {
    return siguiente;
}

NodoProduccion* NodoProduccion::getAnterior() {
    return anterior;
}

ListaProduccion::ListaProduccion() {
    ancla = nullptr;
    cont = 1;
}

ListaProduccion::~ListaProduccion() {
    eliminarNodos();
}

bool ListaProduccion::estaVacia() {
    return ancla == nullptr;
}

void ListaProduccion::insertar(NodoProduccion* nodo, Produccion& dato) {
    NodoProduccion* aux(new NodoProduccion(dato));
    if(nodo == nullptr) {
        aux->setAnterior(nullptr);
        aux->setSiguiente(ancla);
        if(ancla != nullptr) {
            ancla->setAnterior(aux);
        }
        ancla = aux;
    } else {
        aux->setAnterior(nodo);
        if(nodo->getSiguiente() != nullptr) {
            nodo->getSiguiente()->setSiguiente(aux);
        }
        nodo->setSiguiente(aux);
    }
    cont++;
}

NodoProduccion* ListaProduccion::primerPos() {
    return ancla;
}

NodoProduccion* ListaProduccion::ultimaPos() {
    if(estaVacia()) {
        return nullptr;
    }
    NodoProduccion* aux(ancla);
    while(aux->getSiguiente() != nullptr) {
        aux = aux->getSiguiente();
    }
    return aux;
}

NodoProduccion* ListaProduccion::posSiguiente(NodoProduccion* nodo) {
    if(estaVacia() or nodo == nullptr) {
        return nullptr;
    }
    return nodo->getSiguiente();
}

NodoProduccion* ListaProduccion::posAnterior(NodoProduccion* nodo) {
    if(estaVacia() or nodo == ancla) {
        return nullptr;
    }
    return nodo->getAnterior();
}

Produccion& ListaProduccion::operator[](const int& pos) {
    NodoProduccion* aux(ancla);
    int i = 1;
    while(i < pos) {
        aux = aux->getSiguiente();
        i++;
    }
    return aux->getDato();
}

bool ListaProduccion::posValida(NodoProduccion* nodo) {
    NodoProduccion* aux = ancla;
    while(aux != nullptr) {
        if(aux == nodo) {
            return true;
        }
        aux = aux->getSiguiente();
    }
    return false;
}

void ListaProduccion::eliminarNodos() {
    NodoProduccion* aux(ancla);
    while(ancla!= nullptr) {
        aux = ancla;
        ancla = ancla->getSiguiente();
        delete aux;
    }
}

int ListaProduccion::datosTotales() {
    return cont;
}

std::string ListaProduccion::toString() {
    std::string res;
    NodoProduccion* aux(ancla);
    int i = 1;
    while(aux != nullptr) {
        res += std::to_string(i) + "-> " + std::string(aux->getDato().getNombre()) + "\n";
        aux = aux->getSiguiente();
        i++;
    }
    return res;
}
