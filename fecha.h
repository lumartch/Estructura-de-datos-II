#ifndef FECHA_H
#define FECHA_H

#include <string>
#include <cstring>


class Fecha {
    private:
        int dia;
        int mes;
        int anio;
    public:
        Fecha();
        Fecha(const Fecha&);
        int getDia();
        void setDia(const int &);
        int getMes();
        void setMes(const int &);
        int getAnio();
        void setAnio(const int &);
        std::string toString();
        int toInt();
        Fecha &operator=(const Fecha& fecha);
        bool operator ==(Fecha & fecha);
        bool operator !=(Fecha& fecha);
        bool operator <(Fecha& fecha);
        bool operator <=(Fecha& fecha);
        bool operator >(Fecha& fecha);
        bool operator >=(Fecha& fecha);
    };

#endif // FECHA_H
