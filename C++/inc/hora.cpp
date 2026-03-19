#include "hora.h"
#include <sstream>
#include <iomanip>

Hora::Hora() : hora(0), minuto(0){}
Hora::Hora(int h, int m) : hora(h), minuto(m){}

Hora Hora::fromString(const string& s){
    int h, m;
    char barra;
    istringstream(s) >> h >> barra >> m;
    return Hora(h, m);
}

string Hora::toString() const{
    ostringstream saida;
    saida << setw(2) << setfill('0') << hora << ":"
        << setw(2) << setfill('0') << minuto;
    return saida.str();
}

int Hora::toMinutos() const{
    return hora * 60 + minuto;
}

Hora Hora::addMinutos(int minutos) const{
    int total = toMinutos() + minutos;
    int h = (total / 60) % 24;
    int m = total % 60;
    return Hora(h, m);
}

bool Hora::operator < (const Hora& other) const{
    return toMinutos() < other.toMinutos();
}

bool Hora::operator == (const Hora& other) const{
    return hora == other.hora && minuto == other.minuto;
}
