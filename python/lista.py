class Lista:
    #classe interna Node representa cada elemento da lista ligada
    class Node:
        def __init__(self, dado):
            self.dado = dado
            self.prox = None
    
    def __init__(self):
        self.inicio = None
        self.tamanho = 0
    
    def inserir(self, dado):
        #cria um novo no com o dado informado
        novo = self.Node(dado)
        if self.inicio is None:
            self.inicio = novo
        
        else:
            atual = self.inicio
            while atual.prox is not None:
                atual = atual.prox
            atual.prox = novo
        self.tamanho += 1
    
    def toArray(self):
        array = []
        atual = self.inicio
        while atual is not None:
            array.append(atual.dado)
            atual = atual.prox
        return array
    
    def fromArray(self, array):
        self.inicio = None
        self.tamanho = 0
        for dado in array:
            self.inserir(dado)
    
    def ordenar(self, comparador):
        if self.inicio is None or self.inicio.prox is None:
            return
        
        array = self.toArray()
        self.quicksort(array, 0, len(array) - 1, comparador)
        self.fromArray(array)
    
    def quicksort(self, array, esquerda, direita, comparador):
        if esquerda < direita:
            indicePivo = self.particionar(array, esquerda, direita, comparador)
            self.quicksort(array, esquerda, indicePivo - 1, comparador)
            self.quicksort(array, indicePivo + 1, direita, comparador)
    
    def particionar(self, array, esquerda, direita, comparador):
        #define o pivo como o ultimo elemento
        pivo = array[direita]
        i = esquerda - 1
        
        #percorre o array comparando os elementos com o pivo
        for j in range(esquerda, direita):
            if comparador.comparar(array[j], pivo) < 0:
                i += 1
                array[i], array[j] = array[j], array[i]
        
        
        #coloca o pivo na posicao correta
        array[i + 1], array[direita] = array[direita], array[i + 1]
        return i + 1
    
    def getInicio(self):
        #retorna o no inicial da lista
        return self.inicio
    
    def getTamanho(self):
        #retorna o tamanho da lista
        return self.tamanho
    
    def get(self, index):
        if index < 0 or index >= self.tamanho:
            return None
        
        atual = self.inicio
        for _ in range(index):
            atual = atual.prox
        return atual.dado


class Comparador:
    #classe base para comparadores
    def comparar(self, a, b):
        raise NotImplementedError


class ComparadorDataHora(Comparador):
    def comparar(self, c1, c2):
        if c1.getData().iguais(c2.getData()):
            if c1.getHora().iguais(c2.getHora()):
                return 0
            if c1.getHora().antes(c2.getHora()):
                return -1
            else:
                return 1
        
        if c1.getData().antes(c2.getData()):
            return -1
        else:
            return 1


class ComparadorPrioridade(Comparador):
    def comparar(self, c1, c2):
        if c1.getPrioridadeFinal() > c2.getPrioridadeFinal():
            return -1
        elif c1.getPrioridadeFinal() < c2.getPrioridadeFinal():
            return 1
        else:
            return 0


class ComparadorId(Comparador):
    def comparar(self, c1, c2):
        if c1.getId() < c2.getId():
            return -1
        elif c1.getId() > c2.getId():
            return 1
        else:
            return 0


class ComparadorDuracao(Comparador):
    def comparar(self, c1, c2):
        if c1.getDuracao() < c2.getDuracao():
            return -1
        elif c1.getDuracao() > c2.getDuracao():
            return 1
        else:
            return 0


def compararParaDesempate(c1, c2):
    #criterio de desempate por data, hora, tipo e descricao
    if not c1.getData().iguais(c2.getData()):
        if c1.getData().antes(c2.getData()):
            return 1
        else:
            return -1
    
    if not c1.getHora().iguais(c2.getHora()):
        if c1.getHora().antes(c2.getHora()):
            return 1
        else:
            return -1
    
    ordemTipos = "REAPO"
    p1 = ordemTipos.find(c1.getTipo())
    p2 = ordemTipos.find(c2.getTipo())
    
    if p1 != p2:
        if p2 < p1:
            return -1
        else:
            return 1
    
    if c1.getDescricao() < c2.getDescricao():
        return 1
    elif c1.getDescricao() > c2.getDescricao():
        return -1
    return 0


class ComparadorPrioridadeComDesempate(Comparador):
    #compara por prioridade e usa desempate quando necessario
    def comparar(self, c1, c2):
        if c1.getPrioridadeFinal() > c2.getPrioridadeFinal():
            return -1
        elif c1.getPrioridadeFinal() < c2.getPrioridadeFinal():
            return 1
        else:
            return -compararParaDesempate(c1, c2)


class ComparadorDuracaoComDesempate(Comparador):
    #compara por duracao e usa desempate quando necessario
    def comparar(self, c1, c2):
        if c1.getDuracao() < c2.getDuracao():
            return -1
        elif c1.getDuracao() > c2.getDuracao():
            return 1
        else:
            return compararParaDesempate(c1, c2)