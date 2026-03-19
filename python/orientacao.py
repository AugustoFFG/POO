from compromisso import Compromisso

class Orientacao(Compromisso):
    def __init__(self, id, data, hora, duracao, prioridade, adiavel, nomeOrientado, nivel, assunto):
        super().__init__(id, 'O', data, hora, duracao, prioridade, nomeOrientado)
        self.adiavel = adiavel
        self.nivel = nivel
        self.assunto = assunto
        self.calcularPrioridadeFinal()
    
    def calcularPrioridadeFinal(self):
        multiplicador = 1
        if not self.adiavel:
            multiplicador += 1
        self.prioridadeFinal = self.prioridade * multiplicador
    
    def getDescricao(self):
        return f"Orientação de {self.descricao}"
    
    def isAdiavel(self):
        return self.adiavel
    
    def getNivel(self):
        return self.nivel
    
    def getAssunto(self):
        return self.assunto