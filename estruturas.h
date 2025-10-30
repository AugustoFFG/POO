#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

typedef struct tempo Tempo;
typedef struct data Data;
typedef struct hora Hora;
typedef struct prioridade Prioridade;
typedef struct aula Aula;
typedef struct orientacao Orientacao;
typedef struct reuniao Reuniao;
typedef struct evento Evento;
typedef struct compromisso Compromisso;
typedef struct item Item;
typedef struct no No;
typedef struct lista Lista;

Lista* criarLista();
void inserirItem(Lista* lista, char tipo, Item item);
void somarDuracoes(const char* arquivo);
void lerArquivo(char* Arquivo);

#endif
