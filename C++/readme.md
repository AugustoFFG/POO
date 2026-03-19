# Sistema de Gerenciamento de Compromissos

## Estrutura do Projeto
````
TRAB2
├── inc
|├── aula.h
|├── compromisso.h
|├── data.h
|├── evento.h
|├── hora.h
|├── lista.h
|├── mergesort.h
|├── orientacao.h
|├── pessoal.h
|└── reuniao.h
|
├── src
|├── aula.
|├── compromisso.
|├── data.
|├── evento.
|├── hora.
|├── main.
|├── orientacao.
|├── pessoal.
|└── reuniao.
|
├── agenda.txt
├── Makefile
├── posicoes.txt
└── readme.md
````

## Hierarquia de Classes
````
Compromisso
├── Aula
├── Reuniao
├── Orientacao
├── Evento
└── Pessoal
````
Compromisso tem os campos: ID, data e hora, duração, multiplicador, prioridade e prioridade final(campo para armazenar a prioridade após a multiplicação)

todas as classes heradam essas características de "Compromisso" além de terem outras carácterísticas únicas

Aula tem os campos: Nome da disciplina, nível (Gradução | Especialização | Mestrado)

Orientação tem os campos: Adiável, nome do orientando, nível (Gradução | Especialização | Mestrado) e assunto

Reunião tem os campos: Adiável e assunto

Evento tem os campos: Nome do evento e local

Pessoal (compromissos particulares) tem os campos: Adiável, motivo e local

## Funcionalidades Principais

### 1.Leitura e Processamento de Dados

O sistema lê um arquivo agenda.txt e e acordo com o identificador retornado pela leitura (A, O, R, E, P), ele classifica o compromisso como aula, orientação, reunião, evento ou compromissos particulares.

Cada tipo de compromisso tem um tipo diferente de leitura, pelo fato de terem campos diferentes e em posições diferentes.

Exemplo:

Aula:
````
Aula* aula = new Aula(id, data, hora, duracao, prioridade, disciplina, nivel);
aula->calcularPrioridadeFinal();
compromissos.inserir(aula);
````

Orientação:
````
Orientacao* orient = new Orientacao(id, data, hora, duracao, prioridade, adiavel, nomeOrientado, nivel, assunto);
orient->calcularPrioridadeFinal();
compromissos.inserir(orient);
````
Como pode-se observar, orientação tem alguns campos distintos de Aula.


### 2.Cálculo de Prioridades
Cada tipo de compromisso possui um fator de prioridade diferente:

| Tipo de Compromisso | Multiplicador | +1 se Inadiável |
|---------------------|---------------|-----------------|
| Aula                | 2x            | -               |
| Orientação          | 1x            | +1x             |
| Reunião             | 4x            | +1x             |
| Evento              | 3x            | -               |
| Pessoal             | 2x            | +1x             |

Esse fator de prioridade é utilizado na função "compararPrioridade", ela funciona da seguinte forma:
````
void tipoDoCompromisso::calcularPrioridadeFinal(){
    int fator = x; // relativo ao tipo do compromisso
    if(!adiavel) fator += 1; // se adiável for igual a false, aumenta o multplicador
    prioridade_final = prioridade * fator; // calculo da priridade final do compromisso
}
````

### 3. Detecção e Resolução de Conflitos
A função conflita verifica se dois compromissos se sobrepõem no tempo:

````
bool conflita(Compromisso* c1, Compromisso* c2){
    int inicio1 = c1->getData().toDias() * 24 * 60 + c1->getHora().toMinutos(); //transforma em minutos  e oma com os minutos da hora
    int fim1 = inicio1 + c1->getDuracao();// calcula instante final do c1
    int inicio2 = c2->getData().toDias() * 24 * 60 + c2->getHora().toMinutos(); //transforma em minutos  e oma com os minutos da hora
    int fim2 = inicio2 + c2->getDuracao(); //calcula instante final do c2

    bool haConflito = true; // assume o caso padrão como conflituoso
    
    if(fim1 <= inicio2){
      haConflito = false; 
    }

    if(fim2 <= inicio1){
      haConflito = false;  
    } 

    // se o fim de um compromisso n coincidir com o inicio do outro, altera a flag de haconflito

    return haConflito;
}
````

Quando compromissos conflitam, o sistema aplica uma hierarquia de desempate:

````
//Retorna 1 se c1 é mais importante, -1 se c2 é, 0 se empatam
int compararPrioridade(Compromisso* c1, Compromisso* c2){
    //Compara prioridade final
    if(c1->getPrioridadeFinal() > c2->getPrioridadeFinal()) return 1;
    if(c1->getPrioridadeFinal() < c2->getPrioridadeFinal()) return -1;
    // o códogo acima compara a prioridade dos eventos e vê qual a maior, o compromisso com a maior prioridade ganha

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
    // p1 e p2 indicam o indice do tipo de c1 e c2 na string, quanto mais pra trás estiver na string, menor a orioridade

    //Desempate por hora
    if(c1->getHora() < c2->getHora()){
        return 1;
    }

    if(c2->getHora() < c1->getHora()){ 
        return -1;
    }
    //recebe a hora que cada compromisso inicia e vê qual começa primeiro

    //Desempate por ordem alfabética
    if(c1->getDescricao() < c2->getDescricao()){
        return 1;
    }

    if(c2->getDescricao() < c1->getDescricao()){
        return -1;
    }
    // compara a ordem alfabética da descrição de ambos os eventos


    return 0; //Empate total
}
````

## Implementação do Merge Sort

O Merge Sort foi escolhido por ser ideal para listas encadeadas

Implementação:
````

template <typename NoTipo, typename T>
NoTipo* mergeSort(NoTipo* head, bool (*comp)(T, T)){
    if(!head || !head->prox) return head; // caso base
    
    NoTipo* meio = dividir<NoTipo, T>(head); // chama a função de dividir e retorna o primeiro ponteiro da segunda metade da lista
    NoTipo* esq = mergeSort<NoTipo, T>(head, comp);
    NoTipo* dir = mergeSort<NoTipo, T>(meio, comp);
    //recursão para ordenar esquerda e direita
    
    return mesclar<NoTipo, T>(esq, dir, comp);
    //junta as duas partes
}

//Divisão da Lista
template <typename NoTipo, typename T>
NoTipo* dividir(NoTipo* head){
    NoTipo* slow = head;
    NoTipo* fast = head->prox;
    
    while(fast && fast->prox){
        slow = slow->prox;
        fast = fast->prox->prox;
    }
    // quando fast está no final, slow está no meio da lista
    
    NoTipo* meio = slow->prox;
    slow->prox = nullptr;
    return meio;
    //a lista é quebrada ao meio no proximo depois de slow
}

//Mesclagem
template <typename NoTipo, typename T>
NoTipo* mesclar(NoTipo* esq, NoTipo* dir, bool (*comp)(T, T)){
    if(!esq) return dir;
    if(!dir) return esq;
    //Se uma das listas acabar, retorna a outra inteira.

    if(comp(esq->dado, dir->dado)){
        esq->prox = mesclar<NoTipo, T>(esq->prox, dir, comp);
        return esq;
    } 
    else{
        dir->prox = mesclar<NoTipo, T>(esq, dir->prox, comp);
        return dir;
    }
    // se comp for true, o elemento da esquerda é maior, então coloca ele na frente, se não, coloca o elemento da direita na frente
}
````
Aplicações no Sistema
O Merge Sort é utilizado para ordenar compromissos por:

Data e Hora (para relatório de confirmados)

Prioridade Final (para resolução de conflitos)

Duração (para relatório de cancelados)

ID (para relatório completo)

## Lista Encadeada
Implementação da Lista Template
```
template <typename T>
class Lista{
public:
    struct No{
        T dado;
        No* prox;
        No(const T& val) : dado(val), prox(nullptr){}
    };
    //estrutura do no

private:
    No* inicio;
    //atributo inicio aponta para o primeiro nó da lista.

public:
    Lista() : inicio(nullptr){}
    ~Lista();
    
    void inserir(const T& val);
    void ordenar(bool (*comp)(T, T));
    No* getInicio(){ return inicio; }
};
Operações Principais
Inserção no Início:


template <typename T>
void Lista<T>::inserir(const T& val){
    No* novo = new No(val); // cria novono
    novo->prox = inicio; //novo no aponta para o antigo inicio
    inicio = novo; // atualiza o inicio
}
Ordenação:


template <typename T>
void Lista<T>::ordenar(bool (*comp)(T, T)){
    inicio = mergeSort<No, T>(inicio, comp);
}
//comp é uma função de comparação, se retornar true, é pq o item que é passado como parametro a esquerda vem antes do item passado a direita
```

## Sistema de Geração de Arquivos
Lógica de Separação dos Relatórios
```
void gerarRelatorios(Lista<Compromisso*>& lista){
    Lista<Compromisso*> confirmados;
    Lista<Compromisso*> adiados;
    Lista<Compromisso*> cancelados;
    //cria as listas

    //ordena por prioridade para processamento
    lista.ordenar([](Compromisso* a, Compromisso* b){
        return compararPrioridade(a, b) > 0;
    });

    //separa em confirmados, adiados e cancelados
    for(auto n = lista.getInicio(); n; n = n->prox){
        Compromisso* c = n->dado;
        bool conflito = false;

        //verifica conflito com confirmados
        for(auto conf = confirmados.getInicio(); conf; conf = conf->prox){
            if(conflita(c, conf->dado)){
                conflito = true;
                break;
            }
        }

        if(!conflito){
            confirmados.inserir(c);  // se tem não tem conflito, é um compromisso confirmado
        } else{
            if(c->isAdiavel()){
                adiados.inserir(c);  //se tem  tem conflito, mas pode ser adiado, é um compromisso adiado
            } else{
                cancelados.inserir(c); // se tem tem conflito e não pode ser adiado, é um compromisso cancelado
            }
        }
    }
}
```
Arquivos Gerados

1. relatconfirmados.txt
Compromissos que não tiveram conflitos de horário, ordenados por data e hora.

2. relatadiados.txt
Compromissos adiáveis que tiveram conflitos, ordenados por prioridade decrescente.

3. relatcancelados.txt
Compromissos não-adiáveis cancelados por conflito, ordenados por duração crescente.

4. relatcompromissos.txt
Relatório completo de todos os compromissos ordenados por ID, com informações detalhadas.

5. resultado.txt
Soma das durações de compromissos em posições específicas definidas no arquivo posicoes.txt.

## Como Usar
Dentro do arquivo está implementado um Makefile, para rodar, basta rodar o comando
```
make run
```
mas para que o arquivo rode corretamente, exige que os aquivos "agenda.txt" e "posicoes.txt" estejam no mesmo diretório, dessa forma:
```
TRAB2
├── inc
| ...
├── src
| ...
├── agenda.txt
├── Makefile
├── posicoes.txt
└── readme.md
```
Os relatórios serão gerados automaticamente

Formato do Arquivo de entrada agenda.txt deve seguir este padrão:
```
[Tipo][ID]
[Data] [Hora]
[Duração]
[Campo 1]
[Campo 2]
[Campo 3]
[Prioridade]
```
Formato do Arquivo de entrada posicoes.txt deve seguir este padrão:
```
[i-ésimo elemento do relatconfirmados.txt]
[j-ésimo elemento do relatadiados.txt]
[k-ésimo elemento do relatcacelados.txt]
[m-ésimo elemento do relatcompromissos.txt]
```


#### Lógica de Processamento
Leitura: Os compromissos são lidos e instanciados conforme seu tipo

Cálculo de Prioridade: Cada compromisso calcula sua prioridade final

Ordenação: Os compromissos são ordenados por prioridade usando Merge Sort

Confirmação: Compromissos são confirmados se não houver conflito

Classificação: Compromissos em conflito são adiados ou cancelados

Relatórios: São gerados os 5 arquivos de saída

Este sistema é ideal para instituições educacionais ou empresas que precisam gerenciar múltiplos tipos de compromissos com diferentes níveis de prioridade e restrições de tempo.