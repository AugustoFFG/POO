from compromisso import Compromisso

class Evento(Compromisso):
    def __init__(self, id, data, hora, duracao, prioridade, nomeEvento, local):
        super().__init__(id, 'E', data, hora, duracao, prioridade, nomeEvento)
        
        self.local = local
        self.calcularPrioridadeFinal()
    
    def calcularPrioridadeFinal(self):
        self.prioridadeFinal = self.prioridade * 3
    
    def getDescricao(self):
        return self.descricao
    
    def isAdiavel(self):
        return False
    
    def getLocal(self):
        return self.local