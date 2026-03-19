class Data:
    def __init__(self, dia=1, mes=1, ano=2000):
        self.dia = dia
        self.mes = mes
        self.ano = ano
    
    @staticmethod
    def fromString(s):
        partes = s.split('/')
        return Data(int(partes[0]), int(partes[1]), int(partes[2]))
    
    def __str__(self):
        return f"{self.dia:02d}/{self.mes:02d}/{self.ano:04d}"
    
    def addDias(self, dias):
        d = self.dia
        m = self.mes
        a = self.ano
        
        d += dias
        
        while d > self.diasNoMes(m, a):
            d -= self.diasNoMes(m, a)
            m += 1
            if m > 12:
                m = 1
                a += 1
        
        return Data(d, m, a)
    
    def diasNoMes(self, mes, ano):
        if mes == 2:
            return 29 if (ano % 4 == 0 and (ano % 100 != 0 or ano % 400 == 0)) else 28
        elif mes in [4, 6, 9, 11]:
            return 30
        else:
            return 31
    
    def iguais(self, other):
        return self.dia == other.dia and self.mes == other.mes and self.ano == other.ano
    
    def antes(self, other):
        if self.ano != other.ano:
            return self.ano < other.ano
        if self.mes != other.mes:
            return self.mes < other.mes
        return self.dia < other.dia
    
    def converteMin(self):
        totalDias = 0
        for ano in range(2000, self.ano):
            totalDias += 366 if (ano % 4 == 0 and (ano % 100 != 0 or ano % 400 == 0)) else 365
        
        for mes in range(1, self.mes):
            totalDias += self.diasNoMes(mes, self.ano)
        
        totalDias += self.dia - 1
        return totalDias * 24 * 60