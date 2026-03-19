class Hora:
    def __init__(self, hora=0, minuto=0):
        self.hora = hora
        self.minuto = minuto
    
    @staticmethod
    def fromString(s):
        partes = s.split(':')
        return Hora(int(partes[0]), int(partes[1]))
    
    def __str__(self):
        return f"{self.hora:02d}:{self.minuto:02d}"
    
    def toMinutos(self):
        return self.hora * 60 + self.minuto
    
    def antes(self, other):
        return self.toMinutos() < other.toMinutos()
    
    def iguais(self, other):
        return self.hora == other.hora and self.minuto == other.minuto