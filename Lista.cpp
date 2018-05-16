#include "Lista.h"

Nodo::Nodo() {
    siguiente = nullptr;
    anterior = nullptr;
}

Nodo::Nodo(const Academico& dato) : Nodo() {
    this->dato = dato;
}

void Nodo::setDato(const Academico& dato) {
    this->dato = dato;
}

void Nodo::setSiguiente(Nodo* sig) {
    siguiente = sig;
}

void Nodo::setAnterior(Nodo* ant) {
    anterior = ant;
}

Academico& Nodo::getDato() {
    return dato;
}

Nodo* Nodo::getSiguiente() {
    return siguiente;
}

Nodo* Nodo::getAnterior() {
    return anterior;
}

Lista::Lista() {
    ancla = nullptr;
    cont = 1;
}

Lista::~Lista() {
    eliminarNodos();
}

bool Lista::estaVacia() {
    return ancla == nullptr;
}

void Lista::insertar(Nodo* nodo, Academico& dato) {
    Nodo* aux(new Nodo(dato));
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

Nodo* Lista::primerPos() {
    return ancla;
}

Nodo* Lista::ultimaPos() {
    if(estaVacia()) {
        return nullptr;
    }
    Nodo* aux(ancla);
    while(aux->getSiguiente() != nullptr) {
        aux = aux->getSiguiente();
    }
    return aux;
}

Nodo* Lista::posSiguiente(Nodo* nodo) {
    if(estaVacia() or nodo == nullptr) {
        return nullptr;
    }
    return nodo->getSiguiente();
}

Nodo* Lista::posAnterior(Nodo* nodo) {
    if(estaVacia() or nodo == ancla) {
        return nullptr;
    }
    return nodo->getAnterior();
}

Academico& Lista::operator[](const int& pos) {
    Nodo* aux(ancla);
    int i = 1;
    while(i < pos) {
        aux = aux->getSiguiente();
        i++;
    }
    return aux->getDato();
}

bool Lista::posValida(Nodo* nodo) {
    Nodo* aux(ancla);
    while(aux != nullptr) {
        if(aux == nodo) {
            return true;
        }
        aux = aux->getSiguiente();
    }
    return false;
}

void Lista::eliminarNodos() {
    Nodo* aux(ancla);
    while(ancla!= nullptr) {
        aux = ancla;
        ancla = ancla->getSiguiente();
        delete aux;
    }
}

int Lista::datosTotales() {
    return cont;
}

std::string Lista::toString() {
    std::string res;
    Nodo* aux(ancla);
    int i = 1;
    while(aux != nullptr) {
        res += std::to_string(i) + "-> " + std::string(aux->getDato().getNombre()) + "\n";
        aux = aux->getSiguiente();
        i++;
    }
    return res;
}

