#include "orientacao.h"

Orientacao::Orientacao(){}

Orientacao::Orientacao(int id, const Data& data, const Hora& hora, int duracao, int prioridade, bool adiavel, const string& descricao, const string& nivel, const string& assunto)
    : Compromisso(id, 'O', data, hora, duracao, prioridade, prioridade, descricao), adiavel(adiavel), nivel(nivel), assunto(assunto){}

string Orientacao::getDescricao() const{
    return "Orientação de " + descricao;
}

void Orientacao::calcularPrioridadeFinal(){
    int fator = 1;
    if(!adiavel) fator += 1;
    prioridade_final = prioridade * fator;
}

string Orientacao::getNivel() const{
    return nivel;
}

string Orientacao::getAssunto() const{
    return assunto;
}