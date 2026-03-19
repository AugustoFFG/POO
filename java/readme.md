# Sistema de Gerenciamento de Compromissos

## Estrutura do Projeto
```
TRAB3
|
├── Main.java
├── Compromisso.java
├── Aula.java
├── Reuniao.java
├── Orientacao.java
├── Evento.java
├── Pessoal.java
├── Data.java
├── Hora.java
├── Lista.java
├── agenda.txt
├── posicoes.txt
├── readme.md
└── Arquivos gerados
```

## Hierarquia de Classes
```
Compromisso
├── Aula
├── Reuniao
├── Orientacao
├── Evento
└── Pessoal
```

**Compromisso** tem os campos: ID, data e hora, duração, multiplicador, prioridade e prioridade final(campo para armazenar a prioridade após a multiplicação)

Todas as classes herdam essas características de `Compromisso` além de terem outras características únicas:

- **Aula** tem os campos: Nome da disciplina, nível (Gradução | Especialização | Mestrado)
- **Orientação** tem os campos: Adiável, nome do orientando, nível (Gradução | Especialização | Mestrado) e assunto
- **Reunião** tem os campos: Adiável e assunto
- **Evento** tem os campos: Nome do evento e local
- **Pessoal** (compromissos particulares) tem os campos: Adiável, motivo e local

## Funcionalidades Principais

### 1. Leitura e Processamento de Dados

O sistema lê um arquivo `agenda.txt` e, de acordo com o identificador retornado pela leitura (A, O, R, E, P), classifica o compromisso como aula, orientação, reunião, evento ou compromisso pessoal.

Cada tipo de compromisso tem uma leitura diferente, pois possuem campos distintos:

**Exemplo de leitura no Main.java:**
```java
case 'A': {
    String disciplina = br.readLine().trim();
    String nivel = br.readLine().trim();
    int prioridade = Integer.parseInt(br.readLine().trim());
    compromissos.inserir(new Aula(id, data, hora, duracao, prioridade, disciplina, nivel));
    break;
}

case 'O':{
    boolean adiavel = Boolean.parseBoolean(br.readLine().trim());
    String nomeOrientado = br.readLine().trim();
    String nivel = br.readLine().trim();
    String assunto = br.readLine().trim();
    int prioridade = Integer.parseInt(br.readLine().trim());
    compromissos.inserir(new Orientacao(id, data, hora, duracao, prioridade, adiavel, nomeOrientado, nivel, assunto));
    break;
}
```
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

```java
@Override
public void calcularPrioridadeFinal(){
    int multiplicador = 4;
    if(!adiavel){
        multiplicador += 1;
    }
    this.prioridadeFinal = this.prioridade * multiplicador;
}
```
### 3. Detecção e Resolução de Conflitos
A função TemConflito verifica se dois compromissos se sobrepõem no tempo:

```java
static boolean TemConflito(Compromisso c1, Compromisso c2){
    long inicio1 = c1.getData().ConverteMin() + c1.getHora().toMinutos();
    long fim1 = inicio1 + c1.getDuracao();
    long inicio2 = c2.getData().ConverteMin() + c2.getHora().toMinutos();
    long fim2 = inicio2 + c2.getDuracao();
    
    if(fim1 <= inicio2 || fim2 <= inicio1){
        return false;
    } else {
        return true;
    }
}
```

Quando compromissos conflitam, o sistema aplica uma hierarquia de desempate:

1. Data mais antiga tem prioridade

2. Hora mais cedo em caso de mesma data

3. Tipo do compromisso na ordem "REAPO" (Reunião, Evento, Aula, Pessoal, Orientação)

4. Ordem alfabética da descrição como último critério

## Implementação do Quicksort

Optei por mudar o método de ordenação, pelo fato do quicsort ser mais simples e eficaz em lista encadeadas.

```java
public void ordenar(Comparador<T> comparador){
    if (inicio == null || inicio.prox == null) return;
    
    Object[] array = toArray();
    quicksort(array, 0, tamanho - 1, comparador);
    fromArray(array);
}

private void quicksort(Object[] array, int esquerda, int direita, Comparador<T> comparador){
    if (esquerda < direita){
        int indicePivo = particionar(array, esquerda, direita, comparador);
        quicksort(array, esquerda, indicePivo - 1, comparador);
        quicksort(array, indicePivo + 1, direita, comparador);
    }
}
```

Aplicações no Sistema:
O Quicksort é utilizado para ordenar compromissos por:

* Data e Hora (para relatório de confirmados)

* Prioridade Final (para resolução de conflitos)

* Duração (para relatório de cancelados)

* ID (para relatório completo)

## Lista Encadeada

```java
public class Lista<T> {
    public class Node {
        public T dado;
        public Node prox;
        //...
    }
    
    private Node inicio;
    private int tamanho;
    
    //metodos: inserir, ordenar, get, getTamanho, etc.
}
```

A lista é usada para armazenar todos os tipos de compromissos e oferece operações de ordenação através da interface Comparador<T>.

## Geração de arquivos

Compromissos são ordenados por prioridade

Para cada compromisso:

* Se não conflita com nenhum confirmado → adiciona aos confirmados

* Se conflita:

    * Se adiável → adiciona aos adiados

    * Se não adiável → adiciona aos cancelados

Arquivos Gerados:

1. relatconfirmados.txt: Compromissos confirmados, ordenados por data e hora

2. relatadiados.txt: Compromissos adiáveis que tiveram conflitos, ordenados por prioridade decrescente

3. relatcancelados.txt: Compromissos não-adiáveis cancelados, ordenados por duração crescente

4. relatcompromissos.txt: Relatório completo de todos os compromissos ordenados por ID

5. resultado.txt: Soma das durações de compromissos em posições específicas (definidas em posicoes.txt)

## Como usar

Dentro do arquivo está implementado um Makefile, para rodar, basta rodar o comando

```
make run
```
mas para que o arquivo rode corretamente, exige que os aquivos "agenda.txt" e "posicoes.txt" estejam no mesmo diretório.

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

Ordenação: Os compromissos são ordenados por prioridade usando quicksort

Confirmação: Compromissos são confirmados se não houver conflito

Classificação: Compromissos em conflito são adiados ou cancelados

Relatórios: São gerados os 5 arquivos de saída

Este sistema é ideal para instituições educacionais ou empresas que precisam gerenciar múltiplos tipos de compromissos com diferentes níveis de prioridade e restrições de tempo.