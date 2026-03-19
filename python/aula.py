from compromisso import Compromisso

class Aula(Compromisso):
    def __init__(self, id, data, hora, duracao, prioridade, disciplina, nivel):
        super().__init__(id, 'A', data, hora, duracao, prioridade, disciplina)
        
        self.nivel = nivel
        self.calcularPrioridadeFinal()
    
    def calcularPrioridadeFinal(self):
        self.prioridadeFinal = self.prioridade * 2
    
    def getDescricao(self):
        return f"Aula de {self.descricao}"
    
    def isAdiavel(self):
        return False
    
    def getNivel(self):
        return self.nivel
