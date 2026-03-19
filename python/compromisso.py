class Compromisso:
    def __init__(self, id, tipo, data, hora, duracao, prioridade, descricao):
        self.id = id
        self.tipo = tipo
        self.data = data
        self.hora = hora
        self.duracao = duracao
        self.prioridade = prioridade
        self.descricao = descricao
        self.prioridadeFinal = prioridade
    
    def calcularPrioridadeFinal(self):
        raise NotImplementedError
    
    def getDescricao(self):
        raise NotImplementedError
    
    def isAdiavel(self):
        raise NotImplementedError
    
    def getIdFormatado(self):
        return f"{self.id:06d}"
    
    def getId(self):
        return self.id
    
    def getTipo(self):
        return self.tipo
    
    def getData(self):
        return self.data
    
    def getHora(self):
        return self.hora
    
    def getDuracao(self):
        return self.duracao
    
    def getPrioridade(self):
        return self.prioridade
    
    def getPrioridadeFinal(self):
        return self.prioridadeFinal
    
    def antes(self, outro):
        if not self.data.iguais(outro.data):
            return self.data.antes(outro.data)
        return self.hora.antes(outro.hora)
    
    def maiorPrioridade(self, outro):
        return self.prioridadeFinal > outro.prioridadeFinal
    
    def menorId(self, outro):
        return self.id < outro.id
    
    def menorDuracao(self, outro):
        return self.duracao < outro.duracao