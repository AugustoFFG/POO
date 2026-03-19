#ifndef HORA_H
#define HORA_H

#include <string>
using namespace std;

class Hora{
private:
    int hora;
    int minuto;

public:
    Hora();
    Hora(int h, int m);

    static Hora fromString(const string& s);
    string toString() const;
    int toMinutos() const;
    Hora addMinutos(int minutos) const;

    bool operator < (const Hora& other) const;
    bool operator == (const Hora& other) const;
};

#endif
