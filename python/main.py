# main.py
from data import Data
from hora import Hora
from compromisso import Compromisso
from aula import Aula
from evento import Evento
from reuniao import Reuniao
from orientacao import Orientacao
from pessoal import Pessoal
from lista import Lista, ComparadorDataHora, ComparadorId, ComparadorPrioridadeComDesempate, ComparadorDuracaoComDesempate


class Conflito:
    def __init__(self, compromisso, conflitante):
        self.compromisso = compromisso
        self.conflitante = conflitante


def temConflito(c1, c2):
    inicio1 = c1.getData().converteMin() + c1.getHora().toMinutos()
    fim1 = inicio1 + c1.getDuracao()
    
    inicio2 = c2.getData().converteMin() + c2.getHora().toMinutos()
    fim2 = inicio2 + c2.getDuracao()
    
    if fim1 <= inicio2 or fim2 <= inicio1:
        return False
    
    else:
        return True


def lerCompromissos(arquivo):
    compromissos = Lista()
    
    try:
        with open(arquivo, 'r') as f:
            linhas = []
            for linha in f:
                linha = linha.strip()
                linhas.append(linha)
                
    except FileNotFoundError:
        print(f"Erro: Arquivo '{arquivo}' nao encontrado.")
        return compromissos
    
    i = 0
    while i < len(linhas):
        linha = linhas[i]
        i += 1
        
        if len(linha) >= 7 and linha[0] in 'AEORP' and linha[1:].isdigit():
            tipo = linha[0]
            idNum = int(linha[1:])
            
            if i >= len(linhas):
                break
                
            dataHora = linhas[i].split()
            i += 1
            
            if len(dataHora) != 2:
                continue
                
            data = Data.fromString(dataHora[0])
            hora = Hora.fromString(dataHora[1])
            
            if i >= len(linhas):
                break
                
            duracaoStr = linhas[i]
            i += 1
            
            duracaoStr = ''.join(c for c in duracaoStr if c.isdigit())
            if not duracaoStr:
                continue
                
            duracao = int(duracaoStr)
            
            if 1 <= duracao <= 9:
                duracao *= 1440
            
            try:
                if tipo == 'A':
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
                
                elif tipo == 'R':
                    if i + 3 > len(linhas):
                        continue
                    adiavel = linhas[i].lower() == 'true'; i += 1
                    assunto = linhas[i]; i += 1
                    prioridade = int(linhas[i]); i += 1
                    compromissos.inserir(Reuniao(idNum, data, hora, duracao, prioridade, adiavel, assunto))
                
                elif tipo == 'E':
                    if i + 3 > len(linhas):
                        continue
                    nomeEvento = linhas[i]; i += 1
                    local = linhas[i]; i += 1
                    prioridade = int(linhas[i]); i += 1
                    compromissos.inserir(Evento(idNum, data, hora, duracao, prioridade, nomeEvento, local))
                
                elif tipo == 'P':
                    if i + 4 > len(linhas):
                        continue
                    adiavel = linhas[i].lower() == 'true'; i += 1
                    motivo = linhas[i]; i += 1
                    local = linhas[i]; i += 1
                    prioridade = int(linhas[i]); i += 1
                    compromissos.inserir(Pessoal(idNum, data, hora, duracao, prioridade, adiavel, motivo, local))
            except (ValueError, IndexError):
                continue
            
            while i < len(linhas) and not linhas[i]:
                i += 1
    
    return compromissos


def processarCompromissos(todosCompromissos):
    confirmados = Lista()
    adiados = Lista()
    cancelados = Lista()
    
    comparadorPrioridade = ComparadorPrioridadeComDesempate()
    todosCompromissos.ordenar(comparadorPrioridade)
    
    node = todosCompromissos.getInicio()
    while node is not None:
        atual = node.dado
        conflitou = False
        conflitanteMaisImportante = None
        
        confNode = confirmados.getInicio()
        while confNode is not None:
            confirmado = confNode.dado
            
            if temConflito(atual, confirmado):
                conflitou = True
                
                if conflitanteMaisImportante is None:
                    conflitanteMaisImportante = confirmado
                else:
                    if comparadorPrioridade.comparar(confirmado, conflitanteMaisImportante) < 0:
                        conflitanteMaisImportante = confirmado
            
            confNode = confNode.prox
        
        if not conflitou:
            confirmados.inserir(atual)
        else:
            if atual.isAdiavel():
                adiados.inserir(Conflito(atual, conflitanteMaisImportante))
            else:
                cancelados.inserir(Conflito(atual, conflitanteMaisImportante))
        
        node = node.prox
    
    return confirmados, adiados, cancelados


def gerarRelatorios(confirmados, adiados, cancelados, todos):
    comparadorDataHora = ComparadorDataHora()
    confirmados.ordenar(comparadorDataHora)
    
    with open('relatconfirmados.txt', 'w') as f:
        node = confirmados.getInicio()
        while node is not None:
            c = node.dado
            f.write(f"{c.getData()} {c.getHora()}\n")
            f.write(f"{c.getIdFormatado()}\n")
            f.write(f"{c.getDescricao()}\n")
            f.write("\n")
            node = node.prox
    
    adiadosComp = Lista()
    adNode = adiados.getInicio()
    while adNode is not None:
        adiadosComp.inserir(adNode.dado.compromisso)
        adNode = adNode.prox
    
    comparadorAdiados = ComparadorPrioridadeComDesempate()
    adiadosComp.ordenar(comparadorAdiados)
    
    with open('relatadiados.txt', 'w') as f:
        node = adiadosComp.getInicio()
        while node is not None:
            c = node.dado
            
            conflitante = None
            confNode = adiados.getInicio()
            while confNode is not None:
                if confNode.dado.compromisso == c:
                    conflitante = confNode.dado.conflitante
                    break
                confNode = confNode.prox
            
            f.write(f"{c.getIdFormatado()}\n")
            f.write(f"{c.getDescricao()}\n")
            f.write(f"{c.getPrioridadeFinal()}\n")
            
            if conflitante is not None:
                f.write(f"{conflitante.getIdFormatado()}\n")
            else:
                f.write("N/A\n")
            
            f.write("\n")
            node = node.prox
    
    canceladosComp = Lista()
    canNode = cancelados.getInicio()
    while canNode is not None:
        canceladosComp.inserir(canNode.dado.compromisso)
        canNode = canNode.prox
    
    comparadorCancelados = ComparadorDuracaoComDesempate()
    canceladosComp.ordenar(comparadorCancelados)
    
    with open('relatcancelados.txt', 'w') as f:
        node = canceladosComp.getInicio()
        while node is not None:
            c = node.dado
            
            conflitante = None
            confNode = cancelados.getInicio()
            while confNode is not None:
                if confNode.dado.compromisso == c:
                    conflitante = confNode.dado.conflitante
                    break
                confNode = confNode.prox
            
            f.write(f"{c.getIdFormatado()}\n")
            f.write(f"{c.getDescricao()}\n")
            f.write(f"{c.getPrioridadeFinal()}\n")
            
            if conflitante is not None:
                f.write(f"{conflitante.getIdFormatado()}\n")
            else:
                f.write("N/A\n")
            
            f.write("\n")
            node = node.prox
    
    comparadorId = ComparadorId()
    todos.ordenar(comparadorId)
    
    with open('relatcompromissos.txt', 'w') as f:
        node = todos.getInicio()
        while node is not None:
            c = node.dado
            f.write(f"{c.getIdFormatado()}: {c.getDescricao()}\n")
            
            minutosTotais = c.getHora().toMinutos() + c.getDuracao()
            diasExtras = minutosTotais // (24 * 60)
            minutosRestantes = minutosTotais % (24 * 60)
            dataFim = c.getData().addDias(diasExtras)
            horaFim = Hora(minutosRestantes // 60, minutosRestantes % 60)
            
            f.write(f"Início: {c.getData()} {c.getHora()}\n")
            f.write(f"Fim: {dataFim} {horaFim}\n")
            f.write(f"Prioridade: {c.getPrioridadeFinal()}\n")
            
            if c.getTipo() == 'A':
                f.write(f"Nível: {c.getNivel()}\n")
            elif c.getTipo() == 'R':
                f.write(f"Assunto: {c.getAssunto()}\n")
            elif c.getTipo() == 'O':
                f.write(f"Nível: {c.getNivel()}\n")
                f.write(f"Assunto: {c.getAssunto()}\n")
            elif c.getTipo() == 'E':
                f.write(f"Local: {c.getLocal()}\n")
            elif c.getTipo() == 'P':
                f.write(f"Local: {c.getLocal()}\n")
            
            f.write("\n")
            node = node.prox
    
    try:
        with open('posicoes.txt', 'r') as f:
            linhas = f.readlines()
            if len(linhas) >= 4:
                i = int(linhas[0].strip())
                j = int(linhas[1].strip())
                k = int(linhas[2].strip())
                m = int(linhas[3].strip())
            else:
                i = j = k = m = 0
    except FileNotFoundError:
        i = j = k = m = 0
    except ValueError:
        i = j = k = m = 0
    
    soma = 0
    
    if 0 < i <= confirmados.getTamanho():
        c = confirmados.get(i - 1)
        if c is not None:
            soma += c.getDuracao()
    
    if 0 < j <= adiadosComp.getTamanho():
        c = adiadosComp.get(j - 1)
        if c is not None:
            soma += c.getDuracao()
    
    if 0 < k <= canceladosComp.getTamanho():
        c = canceladosComp.get(k - 1)
        if c is not None:
            soma += c.getDuracao()
    
    if 0 < m <= todos.getTamanho():
        c = todos.get(m - 1)
        if c is not None:
            soma += c.getDuracao()
    
    with open('resultado.txt', 'w') as f:
        f.write(f"{soma}\n")


def main():
    try:
        compromissos = lerCompromissos('agenda.txt')
        if compromissos.getTamanho() == 0:
            print("Nenhum compromisso foi carregado. Verifique o arquivo 'agenda.txt'.")
            return
            
        confirmados, adiados, cancelados = processarCompromissos(compromissos)
        gerarRelatorios(confirmados, adiados, cancelados, compromissos)
        print("Processamento concluido. Relatorios gerados com sucesso.")
        print(f"Arquivos gerados: relatconfirmados.txt, relatadiados.txt, relatcancelados.txt, relatcompromissos.txt, resultado.txt")
    except Exception as e:
        print(f"Erro durante o processamento: {e}")


if __name__ == "__main__":
    main()