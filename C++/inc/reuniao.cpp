#include "reuniao.h"

Reuniao::Reuniao(){}

Reuniao::Reuniao(int id, const Data& data, const Hora& hora, int duracao, int prioridade, bool adiavel, const string& assunto)
    : Compromisso(id, 'R', data, hora, duracao, prioridade, prioridade, assunto), adiavel(adiavel), assunto(assunto){}

string Reuniao::getDescricao() const{
    return "Reunião de Departamento";
}

void Reuniao::calcularPrioridadeFinal(){
    int fator = 4;
    if (!adiavel) fator += 1;
    prioridade_final = prioridade * fator;
}

string Reuniao::getAssunto() const{
    return assunto;
}
