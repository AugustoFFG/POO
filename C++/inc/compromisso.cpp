#include "compromisso.h"
#include <sstream>
#include <iomanip>

Compromisso::Compromisso(){}

Compromisso::Compromisso(int id, char tipo, const Data& data, const Hora& hora, int duracao, int prioridade, int prioridade_final, const string& descricao)
    : id(id), tipo(tipo), data(data), hora(hora), duracao(duracao), prioridade(prioridade), prioridade_final(prioridade_final), descricao(descricao){}

int Compromisso::getId() const{ 
    return id; 
}

char Compromisso::getTipo() const{ 
    return tipo; 
}

const Data& Compromisso::getData() const{ 
    return data; 
}

const Hora& Compromisso::getHora() const{
    return hora; 
}

int Compromisso::getDuracao() const{ 
    return duracao; 
}

int Compromisso::getPrioridade() const{ 
    return prioridade; 
}

int Compromisso::getPrioridadeFinal() const{ 
    return prioridade_final; 
}

string Compromisso::getIdFormatado() const{
    ostringstream oss;
    oss << setw(6) << setfill('0') << id;
    return oss.str();
}

string Compromisso::getDescricao() const{
    return descricao;
}

void Compromisso::calcularPrioridadeFinal(){
    prioridade_final = prioridade;
}

bool Compromisso::isAdiavel() const{
    return false;
}

Compromisso::~Compromisso(){}
