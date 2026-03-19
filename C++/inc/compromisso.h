#ifndef COMPROMISSO_H
#define COMPROMISSO_H

#include "data.h"
#include "hora.h"
#include <string>
using namespace std;

class Compromisso{
protected:
    int id;
    char tipo;
    Data data;
    Hora hora;
    int duracao;
    int prioridade;
    int prioridade_final;
    string descricao;

public:
    Compromisso();
    Compromisso(int id, char tipo, const Data& data, const Hora& hora, int duracao, int prioridade, int prioridade_final, const string& descricao);

    int getId() const;
    char getTipo() const;
    const Data& getData() const;
    const Hora& getHora() const;
    int getDuracao() const;
    int getPrioridade() const;
    int getPrioridadeFinal() const;
    string getIdFormatado() const;

    virtual string getDescricao() const;

    virtual void calcularPrioridadeFinal();
    virtual bool isAdiavel() const;

    virtual ~Compromisso();
};

#endif
