#include "evento.h"

Evento::Evento(){}

Evento::Evento(int id, const Data& data, const Hora& hora, int duracao, int prioridade, const string& descricao, const string& local)
    : Compromisso(id, 'E', data, hora, duracao, prioridade, prioridade, descricao),
      local(local){}

string Evento::getDescricao() const{
    return descricao;
}

string Evento::getLocal() const{
    return local;
}

void Evento::calcularPrioridadeFinal(){
    prioridade_final = prioridade * 3;
}
