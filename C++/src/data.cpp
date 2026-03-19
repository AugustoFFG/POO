#include "data.h"
#include <sstream>
#include <iomanip>

Data::Data() : dia(1), mes(1), ano(2000){}
Data::Data(int d, int m, int a) : dia(d), mes(m), ano(a){}

Data Data::fromString(const string& s){
    int d, m, a;
    char barra;
    istringstream(s) >> d >> barra >> m >> barra >> a;
    return Data(d, m, a);
}

string Data::toString() const{
    ostringstream saida;
    saida << setw(2) << setfill('0') << dia << "/" << setw(2) << setfill('0') << mes << "/" << setw(4) << setfill('0') << ano;
    return saida.str();
}

Data Data::addDias(int dias) const{
    int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    int d = dia;
    int m = mes;
    int a = ano;
    
    d += dias;
    
    while(d > diasNoMes[m-1]){
        d -= diasNoMes[m-1];
        m++;
        if(m > 12){
            m = 1;
            a++;
        }
    }
    
    return Data(d, m, a);
}

bool Data::operator == (const Data& o) const{
    return dia == o.dia && mes == o.mes && ano == o.ano;
}

bool Data::operator < (const Data& o) const{
    if (ano != o.ano) return ano < o.ano;
    if (mes != o.mes) return mes < o.mes;
    return dia < o.dia;
}

int Data::toDias() const{
    return (ano - 2000) * 365 + (mes - 1) * 30 + (dia - 1);
}