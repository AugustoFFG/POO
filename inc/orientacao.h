#ifndef ORIENTACAO_H
#define ORIENTACAO_H

#include "compromisso.h"

class Orientacao : public Compromisso{
private:
    bool adiavel;
    string nivel;
    string assunto;

public:
    Orientacao();
    Orientacao(int id, const Data& data, const Hora& hora, int duracao, int prioridade,
               bool adiavel, const string& descricao, const string& nivel,
               const string& assunto);  // 🔹 Remove dataDefesa e horaDefesa

    string getDescricao() const override;
    void calcularPrioridadeFinal() override;
    bool isAdiavel() const override{
        return adiavel; 
    }

    string getNivel() const;
    string getAssunto() const;
};

#endif