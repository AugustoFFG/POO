#ifndef AULA_H
#define AULA_H

#include "compromisso.h"
#include <string>
using namespace std;

class Aula : public Compromisso{
private:
    string nivel;

public:
    Aula();
    Aula(int id, const Data& data, const Hora& hora, int duracao, int prioridade, const string& descricao, const string& nivel);

    string getNivel() const;
    string getDescricao() const override;

    void calcularPrioridadeFinal() override;
    bool isAdiavel() const override{ 
        return false;
    }

    ~Aula() override = default;
};

#endif
