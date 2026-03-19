# Sistema de Gerenciamento de Compromissos

## Estrutura do Projeto
```
TRAB4
|
├── main.py
├── compromisso.py
├── aula.py
├── reuniao.py
├── orientacao.py
├── evento.py
├── pessoal.py
├── data.py
├── hora.py
├── lista.py
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

**Compromisso** tem os campos: ID, tipo data e hora, duração, prioridade e prioridade final(campo para armazenar a prioridade após a multiplicação) e descrição

Todas as classes herdam essas características de `Compromisso` além de terem outras características únicas:

- **Aula** tem os campo: nível (Gradução | Especialização | Mestrado)
- **Orientação** tem os campos: Adiável, nome do orientando, nível (Gradução | Especialização | Mestrado) e assunto
- **Reunião** tem os campos: Adiável e assunto
- **Evento** tem os campo: Local
- **Pessoal** (compromissos particulares) tem os campos: Adiável, motivo e local

## Funcionalidades Principais

### 1. Leitura e Processamento de Dados

O sistema lê um arquivo `agenda.txt` e, de acordo com o identificador retornado pela leitura (A, O, R, E, P), classifica o compromisso como aula, orientação, reunião, evento ou compromisso pessoal.

Cada tipo de compromisso tem uma leitura diferente, pois possuem campos distintos:

**Exemplo de leitura no main.py:**
```python
elif tipo == 'A':
    if i + 3 > len(linhas):
        continue
    disciplina = linhas[i]; i += 1
    nivel = linhas[i]; i += 1
    prioridade = int(linhas[i]); i += 1
    compromissos.inserir(Aula(idNum, data, hora, duracao, prioridade, disciplina, nivel))

elif tipo == 'O':
    if i + 5 > len(linhas):
        continue
    adiavel = linhas[i].lower() == 'true'; i += 1
    nomeOrientado = linhas[i]; i += 1
    nivel = linhas[i]; i += 1
    assunto = linhas[i]; i += 1
    prioridade = int(linhas[i]); i += 1
    compromissos.inserir(Orientacao(idNum, data, hora, duracao, prioridade, adiavel, nomeOrientado, nivel, assunto))
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

A prioridade final é calculada em cada classe específica. Exemplo em reuniao.py

```python
def calcularPrioridadeFinal(self):
    multiplicador = 4
    if not self.adiavel:
        multiplicador += 1
    self.prioridadeFinal = self.prioridade * multiplicador
```
### 3. Detecção e Resolução de Conflitos
A função TemConflito verifica se dois compromissos se sobrepõem no tempo:

```python
def temConflito(c1, c2):
    inicio1 = c1.getData().converteMin() + c1.getHora().toMinutos()
    fim1 = inicio1 + c1.getDuracao()
    
    inicio2 = c2.getData().converteMin() + c2.getHora().toMinutos()
    fim2 = inicio2 + c2.getDuracao()
    
    if fim1 <= inicio2 or fim2 <= inicio1:
        return False
    
    else:
        return True
```

Quando compromissos conflitam, o sistema aplica uma hierarquia de desempate:

1. Data mais antiga tem prioridade

2. Hora mais cedo em caso de mesma data

3. Tipo do compromisso na ordem "REAPO" (Reunião, Evento, Aula, Pessoal, Orientação)

4. Ordem alfabética da descrição como último critério

## Implementação do Quicksort

Optei por mudar o método de ordenação, pelo fato do quicsort ser mais simples e eficaz em lista encadeadas.

```python
def ordenar(self, comparador):
    if self.inicio is None or self.inicio.prox is None:
        return
    
    array = self.toArray()
    self._quicksort(array, 0, len(array) - 1, comparador)
    self.fromArray(array)

def _quicksort(self, array, esquerda, direita, comparador):
    if esquerda < direita:
        indice_pivo = self._particionar(array, esquerda, direita, comparador)
        self._quicksort(array, esquerda, indice_pivo - 1, comparador)
        self._quicksort(array, indice_pivo + 1, direita, comparador)
```

Aplicações no Sistema:
O Quicksort é utilizado para ordenar compromissos por:

* Data e Hora (para relatório de confirmados)

* Prioridade Final (para resolução de conflitos)

* Duração (para relatório de cancelados)

* ID (para relatório completo)

## Lista Encadeada

```python
class Lista:
    class Node:
        def __init__(self, dado):
            self.dado = dado
            self.prox = None
    
    def __init__(self):
        self.inicio = None
        self.tamanho = 0
    
    # Métodos: inserir, ordenar, get, getTamanho, etc.
```

A lista é usada para armazenar todos os tipos de compromissos e oferece operações de ordenação através da classe abstrata Comparador

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