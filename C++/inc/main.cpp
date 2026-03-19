#include <iostream>
#include <fstream>
#include <sstream>
#include "../inc/lista.h"
#include "../inc/orientacao.h"
#include "../inc/reuniao.h"
#include "../inc/evento.h"
#include "../inc/pessoal.h"
#include "../inc/aula.h"
#include "../inc/mergesort.h"

using namespace std;

//Função de comparação para ordenação(por data e hora)
bool comparaPorDataHora(Compromisso* a, Compromisso* b){
    if(a->getData() == b->getData()){
        return a->getHora() < b->getHora();
    }
    
    return a->getData() < b->getData();
}

//Verifica se dois compromissos conflitam
bool conflita(Compromisso* c1, Compromisso* c2){
    int inicio1 = c1->getData().toDias() * 24 * 60 + c1->getHora().toMinutos();
    int fim1 = inicio1 + c1->getDuracao();
    int inicio2 = c2->getData().toDias() * 24 * 60 + c2->getHora().toMinutos();
    int fim2 = inicio2 + c2->getDuracao();

    bool haConflito = true;
    
    if(fim1 <= inicio2){
        haConflito = false;
    }
    
    if(fim2 <= inicio1){
        haConflito = false;
    }
    
    return haConflito;
}

//Retorna 1 se c1 é mais importante, -1 se c2 é, 0 se empate
int compararPrioridade(Compromisso* c1, Compromisso* c2){
    //Compara prioridade final
    if(c1->getPrioridadeFinal() > c2->getPrioridadeFinal()) return 1;
    if(c1->getPrioridadeFinal() < c2->getPrioridadeFinal()) return -1;

    //Desempate por tipo
    const string ordem = "REAPO"; //reunião, evento, aula, pessoal, orientação
    int p1 = ordem.find(c1->getTipo());
    int p2 = ordem.find(c2->getTipo());
    if(p1 != p2){
        if(p1 < p2){
            return 1;
        } 
        else{
            return -1;
        }
    }

    //Desempate por hora
    if(c1->getHora() < c2->getHora()){
        return 1;
    }

    if(c2->getHora() < c1->getHora()){ 
        return -1;
    }

    //Desempate por descrição alfabética
    if(c1->getDescricao() < c2->getDescricao()){
        return 1;
    }

    if(c2->getDescricao() < c1->getDescricao()){
        return -1;
    }

    return 0; //Empate total
}

//Gera os relatórios conforme especificado
void gerarRelatorios(Lista<Compromisso*>& lista){
    ofstream fConfirm("relatconfirmados.txt");
    ofstream fAdiados("relatadiados.txt");
    ofstream fCancel("relatcancelados.txt");
    ofstream fCompleto("relatcompromissos.txt");

    if(!fConfirm || !fAdiados || !fCancel || !fCompleto){
        cerr << "Erro ao criar arquivos de relatório\n";
        return;
    }

    Lista<Compromisso*> confirmados;
    Lista<Compromisso*> adiados;
    Lista<Compromisso*> cancelados;

    // Ordena por prioridade
    lista.ordenar([](Compromisso* a, Compromisso* b){
        return compararPrioridade(a, b) > 0;
    });

    // Percorre por prioridade e confirma se não conflitar com confirmados
    for(auto n = lista.getInicio(); n; n = n->prox){
        Compromisso* c = n->dado;
        bool conflito = false;

        for(auto conf = confirmados.getInicio(); conf; conf = conf->prox){
            if(conflita(c, conf->dado)){
                conflito = true;
                break;
            }
        }

        if(!conflito){
            confirmados.inserir(c);
        } else{
            if(c->isAdiavel()){
                adiados.inserir(c);
            } else{
                cancelados.inserir(c);
            }
        }
    }

    // Ordena confirmados por data e hora
    confirmados.ordenar(comparaPorDataHora);
    
    // Ordena adiados por prioridade decrescente
    adiados.ordenar([](Compromisso* a, Compromisso* b){
        if(a->getPrioridadeFinal() != b->getPrioridadeFinal()){
            return a->getPrioridadeFinal() > b->getPrioridadeFinal();
        }
        int resultadoDesempate = compararPrioridade(a, b);
        return resultadoDesempate > 0;
    });
    
    // Ordena cancelados por duração crescente
    cancelados.ordenar([](Compromisso* a, Compromisso* b){
        if(a->getDuracao() != b->getDuracao()){
            return a->getDuracao() < b->getDuracao();
        }
        int resultadoDesempate = compararPrioridade(a, b);
        return resultadoDesempate > 0;
    });

    // relatconfirmados.txt (por data e hora)
    for(auto n = confirmados.getInicio(); n; n = n->prox){
        Compromisso* c = n->dado;
        fConfirm << c->getData().toString() << " " << c->getHora().toString() << "\n" << c->getIdFormatado() << "\n" << c->getDescricao() << "\n\n";
    }

    // relatadiados.txt
    for(auto n = adiados.getInicio(); n; n = n->prox){
        Compromisso* c = n->dado;
        Compromisso* conflito = nullptr;
        for(auto n2 = confirmados.getInicio(); n2; n2 = n2->prox){
            if(conflita(c, n2->dado)){
                if(conflito == nullptr || compararPrioridade(n2->dado, conflito) > 0){
                    conflito = n2->dado;
                }
            }
        }
        
        fAdiados << c->getIdFormatado() << "\n" << c->getDescricao() << "\n" << c->getPrioridadeFinal() << "\n";
        
        if(conflito){
            fAdiados << conflito->getIdFormatado();
        } else{
            fAdiados << "N/A";
        }
        
        fAdiados << "\n\n";
    }

    // relatcancelados.txt
    for(auto n = cancelados.getInicio(); n; n = n->prox){
        Compromisso* c = n->dado;
        Compromisso* conflito = nullptr;
        for(auto n2 = confirmados.getInicio(); n2; n2 = n2->prox){
            if(conflita(c, n2->dado)){
                if(conflito == nullptr || compararPrioridade(n2->dado, conflito) > 0){
                    conflito = n2->dado;
                }
            }
        }
        
        fCancel << c->getIdFormatado() << "\n" << c->getDescricao() << "\n" << c->getPrioridadeFinal() << "\n";
        
        if(conflito){
            fCancel << conflito->getIdFormatado();
        } else{
            fCancel << "N/A";
        }
        
        fCancel << "\n\n";
    }

    // relatcompromissos.txt (detalhado)
    lista.ordenar([](Compromisso* a, Compromisso* b){
        return a->getId() < b->getId();
    });

    for(auto n = lista.getInicio(); n; n = n->prox){
        Compromisso* c = n->dado;

        fCompleto << c->getIdFormatado() << ": " << c->getDescricao() << "\n";
        fCompleto << "Início: " << c->getData().toString() << " " << c->getHora().toString() << "\n";
        
        // Cálculo correto da data/hora final
        int minutosTotais = c->getHora().toMinutos() + c->getDuracao();
        int diasExtras = minutosTotais / (24 * 60);
        int minutosRestantes = minutosTotais % (24 * 60);
        
        Data dataFim = c->getData().addDias(diasExtras);
        Hora horaFim = Hora(minutosRestantes / 60, minutosRestantes % 60);
        
        fCompleto << "Fim: " << dataFim.toString() << " "
                  << horaFim.toString() << "\n";
        
        fCompleto << "Prioridade: " << c->getPrioridadeFinal() << "\n";

        // Específicos por tipo
        if(c->getTipo() == 'A'){
            Aula* a = (Aula*)c;
            fCompleto << "Nível: " << a->getNivel() << "\n";
        }
        
        else if(c->getTipo() == 'R'){
            Reuniao* r = (Reuniao*)c;
            fCompleto << "Assunto: " << r->getAssunto() << "\n";
        }

        else if(c->getTipo() == 'O'){
            Orientacao* o = (Orientacao*)c;
            fCompleto << "Nível: " << o->getNivel() << "\n";
            fCompleto << "Assunto: " << o->getAssunto() << "\n";
        } 
        
        else if(c->getTipo() == 'E'){
            Evento* e = (Evento*)c;
            fCompleto << "Local: " << e->getLocal() << "\n";
        } 
        
        else if(c->getTipo() == 'P'){
            Pessoal* p = (Pessoal*)c;
            fCompleto << "Local: " << p->getLocal() << "\n";
        }

        fCompleto << "\n";
    }

    fConfirm.close();
    fAdiados.close();
    fCancel.close();
    fCompleto.close();

    // resultado.txt (a partir de posicoes.txt)
    ifstream fpos("posicoes.txt");
    ofstream fres("resultado.txt");
    if(!fpos || !fres){
        cerr << "Erro ao abrir posicoes.txt\n";
        return;
    }

    int i, j, k, m;
    fpos >> i >> j >> k >> m;
    int soma = 0;

    auto somaDuracao = [&](Lista<Compromisso*>& L, int pos){
        int contador = 1;
        for(auto n = L.getInicio(); n; n = n->prox){
            if(contador == pos){
                soma += n->dado->getDuracao();
                break;
            }
            contador++;
        }
    };

    somaDuracao(confirmados, i);
    somaDuracao(adiados, j);
    somaDuracao(cancelados, k);
    somaDuracao(lista, m);

    fres << soma << endl;
}

int main(){
    ifstream arq("agenda.txt");
    if(!arq){
        cerr << "Erro ao abrir agenda.txt\n";
        return 1;
    }

    Lista<Compromisso*> compromissos;
    string linha;

    while(getline(arq, linha)){
        if(linha.empty()) continue;

        if(linha.size() < 2 || !isalpha(linha[0]) || !isdigit(linha[1])){
            cerr << "Linha inválida ignorada: " << linha << endl;
            continue;
        }

        char tipo = linha[0];
        int id = stoi(linha.substr(1));

        string dataStr, horaStr;
        if(!(arq >> dataStr >> horaStr)){
            cerr << "Erro lendo data/hora para " << linha << endl;
            continue;
        }

        Data data = Data::fromString(dataStr);
        Hora hora = Hora::fromString(horaStr);

        int duracao, prioridade;
        string temp;

        try{
            switch(tipo){
                case 'A':{
                    string disciplina, nivel;
                    arq >> duracao;
                    
                    if(duracao >= 1 && duracao <= 9){ 
                    duracao *= 1440;
                    }

                    arq.ignore();
                    getline(arq, disciplina);
                    getline(arq, nivel);
                    arq >> prioridade;

                    Aula* aula = new Aula(id, data, hora, duracao, prioridade, disciplina, nivel);
                    aula->calcularPrioridadeFinal();
                    compromissos.inserir(aula);
                    break;
                }

                case 'O':{
                    string nomeOrientado, nivel, assunto;
                    bool adiavel;
                    arq >> duracao >> boolalpha >> adiavel;
                    
                    if(duracao >= 1 && duracao <= 9){ 
                    duracao *= 1440;
                    }

                    arq.ignore();
                    getline(arq, nomeOrientado);
                    getline(arq, nivel);
                    getline(arq, assunto);
                    arq >> prioridade;

                    Orientacao* orient = new Orientacao(id, data, hora, duracao, prioridade, adiavel, nomeOrientado, nivel, assunto);
                    orient->calcularPrioridadeFinal();
                    compromissos.inserir(orient);
                    break;
                }

                case 'R':{
                    string assunto;
                    bool adiavel;
                    arq >> duracao >> boolalpha >> adiavel;

                    if(duracao >= 1 && duracao <= 9){ 
                    duracao *= 1440;
                    }

                    arq.ignore();
                    getline(arq, assunto);
                    arq >> prioridade;

                    Reuniao* reuniao = new Reuniao(id, data, hora, duracao, prioridade, adiavel, assunto);
                    reuniao->calcularPrioridadeFinal();
                    compromissos.inserir(reuniao);
                    break;
                }

                case 'E':{
                    string nomeEvento, local;
                    arq >> duracao;

                    if(duracao >= 1 && duracao <= 9){ 
                    duracao *= 1440;
                    }

                    arq.ignore();
                    getline(arq, nomeEvento);
                    getline(arq, local);
                    arq >> prioridade;

                    Evento* evento = new Evento(id, data, hora, duracao, prioridade, nomeEvento, local);
                    evento->calcularPrioridadeFinal();
                    compromissos.inserir(evento);
                    break;
                }

                case 'P':{
                    string motivo, local;
                    bool adiavel;
                    arq >> duracao >> boolalpha >> adiavel;

                    if(duracao >= 1 && duracao <= 9){ 
                    duracao *= 1440;
                    }

                    arq.ignore();
                    getline(arq, motivo);
                    getline(arq, local);
                    arq >> prioridade;

                    Pessoal* pessoal = new Pessoal(id, data, hora, duracao, prioridade, adiavel, motivo, local);
                    pessoal->calcularPrioridadeFinal();
                    compromissos.inserir(pessoal);
                    break;
                }

                default:
                    cerr << "Tipo de compromisso desconhecido: " << tipo << endl;
                    continue;
            }
        } catch(const exception& e){
            cerr << "Erro processando " << tipo << id << ": " << e.what() << endl;
            continue;
        }

        string resto;
        getline(arq, resto); //Limpa a linha restante
    }

    arq.close();

    compromissos.ordenar(comparaPorDataHora);

    gerarRelatorios(compromissos);

    // Libera memória
    for(auto n = compromissos.getInicio(); n; n = n->prox){
        delete n->dado;
    }

    return 0;
}