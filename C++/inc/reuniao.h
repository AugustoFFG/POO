#ifndef REUNIAO_H
#define REUNIAO_H

#include "compromisso.h"

class Reuniao : public Compromisso{
private:
    bool adiavel;
    string assunto;

public:
    Reuniao();
    Reuniao(int id, const Data& data, const Hora& hora, int duracao, int prioridade,
            bool adiavel, const string& assunto);

    string getDescricao() const override;
    void calcularPrioridadeFinal() override;
    bool isAdiavel() const override{ 
        return adiavel;
    }


    string getAssunto() const;
};

#endif
