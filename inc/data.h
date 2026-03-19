#ifndef DATA_H
#define DATA_H

#include <string>
using namespace std;

class Data{
private:
    int dia, mes, ano;

public:
    Data();
    Data(int d, int m, int a);

    static Data fromString(const string& s);
    string toString() const;
    Data addDias(int dias) const; 

    bool operator == (const Data& o) const;
    bool operator < (const Data& o) const;
    
    int toDias() const;
};

#endif