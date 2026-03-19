#ifndef PESSOAL_H
#define PESSOAL_H

#include "compromisso.h"

class Pessoal : public Compromisso{
private:
    bool adiavel;
    string local;

public:
    Pessoal();
    Pessoal(int id, const Data& data, const Hora& hora, int duracao, int prioridade,
            bool adiavel, const string& descricao, const string& local);

    string getDescricao() const override;
    void calcularPrioridadeFinal() override;
    bool isAdiavel() const override{
        return adiavel;
    }


    string getLocal() const;
};

#endif
