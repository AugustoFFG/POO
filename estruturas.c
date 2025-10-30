#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include "estruturas.h"

// Lista global
Lista* lista = NULL;

typedef struct tempo{
    char data[20];
    char hora[10];
} Tempo;

typedef struct prioridade{         
    int prioridade;      
    int multiplicador;     
    char adiavel[6]; 
    int prioridade_final;                            
} Prioridade;

typedef struct aula{
    Prioridade a;
    char id[10];
    Tempo data;
    Tempo hora;
    int duracao;
    char nome[50];
    char grau[20];
} Aula;

typedef struct orientacao{
    Prioridade o;
    char id[10];
    Tempo data;
    Tempo hora;
    int duracao; 
    char nome_orientando[50];
    char grau[20];
    Tempo data_defesa;
} Orientacao;

typedef struct reuniao{
    Prioridade r;
    char id[10];
    Tempo data;
    Tempo hora; 
    int duracao;    
    char assunto[50];
} Reuniao;

typedef struct evento{
    Prioridade e;
    char id[10];
    Tempo data;
    Tempo hora;
    int duracao;  
    char nome_evento[53];
    char local[50];
} Evento;

typedef struct compromisso{
    Prioridade p;
    char id[10];
    Tempo data;
    Tempo hora; 
    int duracao;   
    char motivo[50];
    char local[50];
} Compromisso;

typedef struct item{
    Aula aula;
    Orientacao orientacao;
    Reuniao reuniao;
    Evento evento;
    Compromisso compromisso;
} Item;

typedef struct no{
    char tipo;  // 'A', 'O', 'R', 'E' ou 'P'
    Item item;
    struct no* next;
} No;

typedef struct lista{
    No* head;
    int size;
} Lista;

// Função para criar uma nova lista
Lista* criarLista() {
    Lista* novaLista = (Lista*)malloc(sizeof(Lista));
    if (novaLista != NULL) {
        novaLista->head = NULL;
        novaLista->size = 0;
    }
    return novaLista;
}

// Função para inserir um item na lista
void inserirItem(Lista* lista, char tipo, Item item) {
    if (lista == NULL) return;

    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) return;

    novoNo->tipo = tipo;
    novoNo->item = item;
    novoNo->next = NULL;

    if (lista->head == NULL) {
        lista->head = novoNo;
    } else {
        No* atual = lista->head;
        while (atual->next != NULL) {
            atual = atual->next;
        }
        atual->next = novoNo;
    }
    lista->size++;
}

void lerArquivo(char* Arquivo) {
    if(lista == NULL) {
        lista = criarLista();
    }

    FILE *arq = fopen(Arquivo, "r");
    if(arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[100];

    while(fgets(linha, sizeof(linha), arq)) {
        linha[strcspn(linha, "\r\n")] = 0;

        if (strlen(linha) == 0){
            continue;
        }

        char tipo = linha[0];
        if(tipo == 'A'){
            Item novoItem;
            Aula aula;
            //id    
            strcpy(aula.id, &linha[0]);
            aula.id[strcspn(aula.id, "\r\n")] = 0;

            //data e hora
            char data[20], hora[10];
            linha[strcspn(linha, "\r\n")] = 0;
            fgets(linha, sizeof(linha), arq);
            linha[strcspn(linha, "\r\n")] = 0;
            sscanf(linha, "%s %s", data, hora);
            strcpy(aula.data.data, data);
            strcpy(aula.data.hora, hora);

            //duracao
            fgets(linha, sizeof(linha), arq);
            linha[strcspn(linha, "\r\n")] = 0;
            aula.duracao = atoi(linha);
            
            //nome
            fgets(aula.nome, sizeof(aula.nome), arq);   
            aula.nome[strcspn(aula.nome, "\r\n")] = 0;

            //grau
            fgets(aula.grau, sizeof(aula.grau), arq);
            aula.grau[strcspn(aula.grau, "\r\n")] = 0;

            //prioridade
            fgets(linha, sizeof(linha), arq);
            linha[strcspn(linha, "\r\n")] = 0;
            aula.a.prioridade = atoi(linha);
            aula.a.multiplicador = 2;
            aula.a.prioridade_final = aula.a.multiplicador * aula.a.prioridade;

            // Adicionar à lista
            novoItem.aula = aula;
            inserirItem(lista, 'A', novoItem);

            printf("ID: %s\nData: %s %s\nDuração: %d\nNome: %s\nGrau: %s\nPrioridade: %d\nPrioridade Final: %d\n\n", aula.id,  aula.data.data, aula.data.hora, aula.duracao, aula.nome, aula.grau, aula.a.prioridade, aula.a.prioridade_final);
        }

        else if(tipo == 'O'){
            Item novoItem;
            Orientacao orientacao;
            //id
            strcpy(orientacao.id, &linha[0]);
            orientacao.id[strcspn(orientacao.id, "\r\n")] = 0;

            //data e hora
            char data[20], hora[10];
            fgets(linha, sizeof(linha), arq);
            linha[strcspn(linha, "\r\n")] = 0;
            sscanf(linha, "%s %s", data, hora);
            strcpy(orientacao.data.data, data);
            strcpy(orientacao.data.hora, hora);

            //duracao
            fgets(linha, sizeof(linha), arq);
            linha[strcspn(linha, "\r\n")] = 0;
            orientacao.duracao = atoi(linha);

            //adiavel
            fgets(linha, sizeof(linha), arq);
            linha[strcspn(linha, "\r\n")] = 0;
            strcpy(orientacao.o.adiavel, linha);

            //nome orientando
            fgets(orientacao.nome_orientando, sizeof(orientacao.nome_orientando), arq);   
            orientacao.nome_orientando[strcspn(orientacao.nome_orientando, "\r\n")] = 0;

            //grau
            fgets(orientacao.grau, sizeof(orientacao.grau), arq);
            orientacao.grau[strcspn(orientacao.grau, "\r\n")] = 0;

            //data defesa
            fgets(linha, sizeof(linha), arq); 
            linha[strcspn(linha, "\r\n")] = 0;
            strcpy(orientacao.data_defesa.data, linha);

            //prioridade
            fgets(linha, sizeof(linha), arq);
            linha[strcspn(linha, "\r\n")] = 0;
            if(strcmp(orientacao.o.adiavel, "true") == 0){
                orientacao.o.multiplicador = 1;    
            }
            else{
                orientacao.o.multiplicador = 2;
            }
            orientacao.o.prioridade = atoi(linha);    
            
            orientacao.o.prioridade_final = orientacao.o.multiplicador * orientacao.o.prioridade;

            // Adicionar à lista
            novoItem.orientacao = orientacao;
            inserirItem(lista, 'O', novoItem);

            printf("ID: %s\nData: %s %s\nDuração: %d\nAdiável: %s\nOrientando: %s\nGrau: %s\nData Defesa: %s\nPrioridade: %d\nPrioridade Final: %d\n\n",orientacao.id, orientacao.data.data, orientacao.data.hora, orientacao.duracao, orientacao.o.adiavel, orientacao.nome_orientando, orientacao.grau, orientacao.data_defesa.data, orientacao.o.prioridade, orientacao.o.prioridade_final);
        }

        else if(tipo == 'R'){
            Item novoItem;
            Reuniao reuniao;
            //id
            strcpy(reuniao.id, &linha[0]);
            reuniao.id[strcspn(reuniao.id, "\r\n")] = 0;

            //data e hora
            char data[20], hora[10];
            fgets(linha, sizeof(linha), arq);
            linha[strcspn(linha, "\r\n")] = 0;
            sscanf(linha, "%s %s", data, hora);
            strcpy(reuniao.data.data, data);
            strcpy(reuniao.data.hora, hora);
            
            //duracao
            fgets(linha, sizeof(linha), arq);
            linha[strcspn(linha, "\r\n")] = 0;
            reuniao.duracao = atoi(linha);

            //adiavel
            fgets(linha, sizeof(linha), arq);
            linha[strcspn(linha, "\r\n")] = 0;
            strcpy(reuniao.r.adiavel, linha);

            //assunto
            fgets(reuniao.assunto, sizeof(reuniao.assunto), arq);
            reuniao.assunto[strcspn(reuniao.assunto, "\r\n")] = 0;
            
            //prioridade
            fgets(linha, sizeof(linha), arq);
            linha[strcspn(linha, "\r\n")] = 0;
            if(strcmp(reuniao.r.adiavel, "true") == 0){
                reuniao.r.multiplicador = 4;    
            }
            else{
                reuniao.r.multiplicador = 5;
            }
            reuniao.r.prioridade = atoi(linha);
            reuniao.r.prioridade_final = reuniao.r.multiplicador * reuniao.r.prioridade;

            // Adicionar à lista
            novoItem.reuniao = reuniao;
            inserirItem(lista, 'R', novoItem);

            printf("ID: %s\nData: %s %s\nDuração: %d\nAdiável: %s\nAssunto: %s\nPrioridade: %d\nPrioridade Final: %d\n\n", reuniao.id,  reuniao.data.data, reuniao.data.hora, reuniao.duracao, reuniao.r.adiavel, reuniao.assunto,reuniao.r.prioridade, reuniao.r.prioridade_final);
        }
        
        else if(tipo == 'E'){
            Item novoItem;
            Evento evento;
            // id
            strcpy(evento.id, &linha[0]);
            evento.id[strcspn(evento.id, "\r\n")] = 0;

            // data e hora
            char data[20], hora[10];
            fgets(linha, sizeof(linha), arq);
            linha[strcspn(linha, "\r\n")] = 0;
            sscanf(linha, "%s %s", data, hora);
            strcpy(evento.data.data, data);
            strcpy(evento.data.hora, hora);
            
            // duração
            fgets(linha, sizeof(linha), arq);
            linha[strcspn(linha, "\r\n")] = 0;
            evento.duracao = atoi(linha);

            // nome evento
            fgets(evento.nome_evento, sizeof(evento.nome_evento), arq);
            evento.nome_evento[strcspn(evento.nome_evento, "\r\n")] = 0;

            // local
            fgets(evento.local, sizeof(evento.local), arq);
            evento.local[strcspn(evento.local, "\r\n")] = 0;

            // prioridade
            fgets(linha, sizeof(linha), arq);
            linha[strcspn(linha, "\r\n")] = 0;
            evento.e.prioridade = atoi(linha);
            evento.e.multiplicador = 3;
            evento.e.prioridade_final = evento.e.multiplicador * evento.e.prioridade;

            // Adicionar à lista
            novoItem.evento = evento;
            inserirItem(lista, 'E', novoItem);

            printf("ID: %s\nData: %s %s\nDuração: %d\nEvento: %s\nLocal: %s\nPrioridade: %d\nPrioridade Final: %d\n\n", evento.id,  evento.data.data, evento.data.hora, evento.duracao, evento.nome_evento, evento.local, evento.e.prioridade, evento.e.prioridade_final);
       }
     
        else if(tipo == 'P'){
            Item novoItem;
            Compromisso compromisso;
            //id
            strcpy(compromisso.id, &linha[0]);
            compromisso.id[strcspn(compromisso.id, "\r\n")] = 0;

            //data e hora
            char data[20], hora[10];
            fgets(linha, sizeof(linha), arq);
            linha[strcspn(linha, "\r\n")] = 0;
            sscanf(linha, "%s %s", data, hora);
            strcpy(compromisso.data.data, data);
            strcpy(compromisso.data.hora, hora);
            
            //duracao
            fgets(linha, sizeof(linha), arq);
            linha[strcspn(linha, "\r\n")] = 0;
            compromisso.duracao = atoi(linha);

            //adiavel
            fgets(linha, sizeof(linha), arq);
            linha[strcspn(linha, "\r\n")] = 0;
            strcpy(compromisso.p.adiavel, linha);

            //motivo
            fgets(compromisso.motivo, sizeof(compromisso.motivo), arq);
            compromisso.motivo[strcspn(compromisso.motivo, "\r\n")] = 0;

            //local
            fgets(compromisso.local, sizeof(compromisso.local), arq);
            compromisso.local[strcspn(compromisso.local, "\r\n")] = 0;

            //prioridade
            fgets(linha, sizeof(linha), arq);
            linha[strcspn(linha, "\r\n")] = 0;
            if(strcmp(compromisso.p.adiavel, "true") == 0){
                compromisso.p.multiplicador = 2;    
            }
            else{
                compromisso.p.multiplicador = 3;
            }
            compromisso.p.prioridade = atoi(linha);
            compromisso.p.prioridade_final = compromisso.p.multiplicador * compromisso.p.prioridade;

            // Adicionar à lista
            novoItem.compromisso = compromisso;
            inserirItem(lista, 'P', novoItem);

            printf("ID: %s\nData: %s %s\nDuração: %d\nAdiável: %s\nMotivo: %s\nLocal: %s\nPrioridade: %d\nPrioridade Final: %d\n\n", compromisso.id,  compromisso.data.data, compromisso.data.hora, compromisso.duracao, compromisso.p.adiavel, compromisso.motivo, compromisso.local, compromisso.p.prioridade, compromisso.p.prioridade_final);
        }
    }
}

void somarDuracoes(const char* arquivo) {
    if(lista == NULL || lista->head == NULL) {
        printf("Lista vazia ou inválida\n");
        return;
    }

    FILE* arq = fopen(arquivo, "r");
    if(!arq){
        printf("Erro ao abrir o arquivo de posições: %s\n", arquivo);
        return;
    }

    char linha[100];
    int totalMinutos = 0;

    while(fgets(linha, sizeof(linha), arq)){
        linha[strcspn(linha, "\r\n")] = 0;

        int pos = atoi(linha);

        // navegar até a posição
        No* atual = lista->head;
        int i = 1;
        while(atual != NULL && i < pos){
            atual = atual->next;
            i++;
        }
        if (atual == NULL) {
            printf("Posição %d fora do intervalo (ignorada)\n", pos);
            continue;
        }

        int dur = 0;
        switch (atual->tipo) {
            case 'A': dur = atual->item.aula.duracao; break;
            case 'O': dur = atual->item.orientacao.duracao; break;
            case 'R': dur = atual->item.reuniao.duracao; break;
            case 'E': dur = atual->item.evento.duracao; break;
            case 'P': dur = atual->item.compromisso.duracao; break;
            default: dur = 0; break;
        }

        // Se a duração for apenas um algarismo, tratar como horas -> converter em minutos
        if (dur >= 0 && dur <= 9) {
            dur = dur * 60;
        }

        totalMinutos += dur;
    }

    fclose(arq);

    // Imprime total em minutos e também em horas:minutos
    printf("\nSoma das durações = %d minutos\n", totalMinutos);
}