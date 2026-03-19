#include "../inc/aula.h"

Aula::Aula(){}

Aula::Aula(int id, const Data& data, const Hora& hora, int duracao, int prioridade, const string& descricao, const string& nivel)
    : Compromisso(id, 'A', data, hora, duracao, prioridade, prioridade, descricao), nivel(nivel){}

string Aula::getNivel() const{
    return nivel;
}

string Aula::getDescricao() const{
    return "Aula de " + descricao; 
}

void Aula::calcularPrioridadeFinal(){
    prioridade_final = prioridade * 2;
}
