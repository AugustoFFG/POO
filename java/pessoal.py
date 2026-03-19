from compromisso import Compromisso

class Pessoal(Compromisso):
    def __init__(self, id, data, hora, duracao, prioridade, adiavel, motivo, local):
        super().__init__(id, 'P', data, hora, duracao, prioridade, motivo)
        self.adiavel = adiavel
        self.local = local
        self.calcularPrioridadeFinal()
    
    def calcularPrioridadeFinal(self):
        multiplicador = 2
        if not self.adiavel:
            multiplicador += 1
        self.prioridadeFinal = self.prioridade * multiplicador
    
    def getDescricao(self):
        return self.descricao
    
    def isAdiavel(self):
        return self.adiavel
    
    def getLocal(self):
        return self.local