#include "pessoal.h"

Pessoal::Pessoal(){}

Pessoal::Pessoal(int id, const Data& data, const Hora& hora, int duracao, int prioridade, bool adiavel, const string& descricao, const string& local)
    : Compromisso(id, 'P', data, hora, duracao, prioridade, prioridade, descricao), adiavel(adiavel), local(local){}

string Pessoal::getDescricao() const{
    return descricao;
}

void Pessoal::calcularPrioridadeFinal(){
    int fator = 2; // Pessoal: 2x
    if (!adiavel) fator += 1;
    prioridade_final = prioridade * fator;
}

string Pessoal::getLocal() const{
    return local;
}
