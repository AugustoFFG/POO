#ifndef EVENTO_H
#define EVENTO_H

#include "compromisso.h"

class Evento : public Compromisso{
private:
    string local;

public:
    Evento();
    Evento(int id, const Data& data, const Hora& hora, int duracao, int prioridade, const string& descricao, const string& local);

    string getDescricao() const override;
    string getLocal() const;

    void calcularPrioridadeFinal() override;
    bool isAdiavel() const override{
        return false; 
    }

};

#endif
