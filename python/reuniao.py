from compromisso import Compromisso

class Reuniao(Compromisso):
    def __init__(self, id, data, hora, duracao, prioridade, adiavel, assunto):
        super().__init__(id, 'R', data, hora, duracao, prioridade, assunto)
        self.adiavel = adiavel
        self.assunto = assunto
        self.calcularPrioridadeFinal()
    
    def calcularPrioridadeFinal(self):
        multiplicador = 4
        if not self.adiavel:
            multiplicador += 1
        self.prioridadeFinal = self.prioridade * multiplicador
    
    def getDescricao(self):
        return "Reunião de Departamento"
    
    def isAdiavel(self):
        return self.adiavel
    
    def getAssunto(self):
        return self.assunto