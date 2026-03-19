import java.io.*;
import java.util.*;

public class Main{
    
    static class Conflito{
        Compromisso compromisso;
        Compromisso conflitante;
        
        Conflito(Compromisso c, Compromisso confl){
            this.compromisso = c;
            this.conflitante = confl;
        }
    }
    
    static boolean TemConflito(Compromisso c1, Compromisso c2){
        long inicio1 = c1.getData().ConverteMin() + c1.getHora().toMinutos();
        long fim1 = inicio1 + c1.getDuracao();
        
        long inicio2 = c2.getData().ConverteMin() + c2.getHora().toMinutos();
        long fim2 = inicio2 + c2.getDuracao();
        
        if(fim1 <= inicio2 || fim2 <= inicio1){
            return false;
        } 
        
        else{
            return true;
        }
    }
    
    static int CompararParaDesempate(Compromisso c1, Compromisso c2){
        if(!c1.getData().iguais(c2.getData())){
            if(c1.getData().antes(c2.getData())){
                return 1;
            }
            
            else{
                return -1;
            }
        }
        
        if(!c1.getHora().iguais(c2.getHora())){
            if(c1.getHora().antes(c2.getHora())){
                return 1;
            } 
            
            else{
                return -1;
            }
        }
        
        String ordemTipos = "REAPO";
        int p1 = ordemTipos.indexOf(c1.getTipo());
        int p2 = ordemTipos.indexOf(c2.getTipo());
        
        if(p1!=p2){
            if(p2 < p1){
                return -1;
            } 
            
            else{
                return 1;
            }
        }
        
        return c1.getDescricao().compareTo(c2.getDescricao());
    }
    
    //compara por data
    static class ComparadorDataHora implements Lista.Comparador<Compromisso>{
        @Override
        public int comparar(Compromisso c1, Compromisso c2){
            if(c1.getData().iguais(c2.getData())){
                if(c1.getHora().iguais(c2.getHora())){
                    return 0;
                }

                if(c1.getHora().antes(c2.getHora())){
                    return -1;
                }
                
                else{
                    return 1;
                }
            }
            
            if(c1.getData().antes(c2.getData())){
                return -1;
            } 
            
            else{
                return 1;
            }
        }
    }
    
    //compara por prioridade
    static class ComparadorPrioridade implements Lista.Comparador<Compromisso>{
        @Override
        public int comparar(Compromisso c1, Compromisso c2){
            if(c1.getPrioridadeFinal() > c2.getPrioridadeFinal()){
                return -1;
            } 

            else if(c1.getPrioridadeFinal() < c2.getPrioridadeFinal()){
                return 1;
            }

            else{
                return 0;
            }
        }

    }
    
    //compara por ID
    static class ComparadorId implements Lista.Comparador<Compromisso>{
        @Override
        public int comparar(Compromisso c1, Compromisso c2){
            if(c1.getId() < c2.getId()){
                return -1;
            } 
            
            else if(c1.getId() > c2.getId()){
                return 1;
            }
            
            else{
                return 0;
            }
        }
    }
    

    //compara por duração crescente
    static class ComparadorDuracao implements Lista.Comparador<Compromisso>{
        @Override
        public int comparar(Compromisso c1, Compromisso c2){
            if(c1.getDuracao() < c2.getDuracao()){
                return -1;
            } 
            
            else if(c1.getDuracao() > c2.getDuracao()){
                return 1;
            }
            
            else{
                return 0;
            }
        }
    }
    
    //compara por prioridade com desempate
    static class ComparadorPrioridadeComDesempate implements Lista.Comparador<Compromisso>{
        @Override
        public int comparar(Compromisso c1, Compromisso c2){
            if(c1.getPrioridadeFinal() > c2.getPrioridadeFinal()){
                return -1;
            } 
            
            else if(c1.getPrioridadeFinal() < c2.getPrioridadeFinal()){
                return 1;
            }
            
            else{
                return -CompararParaDesempate(c1, c2);
            }
        }
    }
    

    //compara por duração com desempate
    static class ComparadorDuracaoComDesempate implements Lista.Comparador<Compromisso>{
        @Override
        public int comparar(Compromisso c1, Compromisso c2){
            if(c1.getDuracao() < c2.getDuracao()){
                return -1;
            } 
            
            else if(c1.getDuracao() > c2.getDuracao()){
                return 1;
            } 
            
            else{
                return CompararParaDesempate(c1, c2);
            }
        }
    }
    
    static Lista<Compromisso> lerCompromissos(String arquivo) throws IOException{
        Lista<Compromisso> compromissos = new Lista<>();
        BufferedReader br = new BufferedReader(new FileReader(arquivo));
        String linha;
        
        while((linha = br.readLine()) != null){
            linha = linha.trim();
            if(linha.isEmpty()){
                continue;
            }
            
            if(linha.matches("^[AEORP]\\d+$")){
                char tipo = linha.charAt(0);
                int id = Integer.parseInt(linha.substring(1));
                
                //le data e hora
                String dataHora = br.readLine().trim();
                String[] dh = dataHora.split(" ");
                Data data = Data.fromString(dh[0]);
                Hora hora = Hora.fromString(dh[1]);
                
                //le duração
                String duracaoStr = br.readLine().trim();
                int duracao = Integer.parseInt(duracaoStr);
                
                if(duracao >= 1 && duracao <= 9){
                    duracao *= 1440;

                }
                
                switch(tipo){
                    case 'A':{
                        String disciplina = br.readLine().trim();
                        String nivel = br.readLine().trim();
                        int prioridade = Integer.parseInt(br.readLine().trim());
                        compromissos.inserir(new Aula(id, data, hora, duracao, prioridade, disciplina, nivel));
                        break;
                    }
                    
                    case 'O':{
                        boolean adiavel = Boolean.parseBoolean(br.readLine().trim());
                        String nomeOrientado = br.readLine().trim();
                        String nivel = br.readLine().trim();
                        String assunto = br.readLine().trim();
                        int prioridade = Integer.parseInt(br.readLine().trim());
                        compromissos.inserir(new Orientacao(id, data, hora, duracao, prioridade, adiavel, nomeOrientado, nivel, assunto));
                        break;
                    }
                    
                    case 'R':{
                        boolean adiavel = Boolean.parseBoolean(br.readLine().trim());
                        String assunto = br.readLine().trim();
                        int prioridade = Integer.parseInt(br.readLine().trim());
                        compromissos.inserir(new Reuniao(id, data, hora, duracao, prioridade, adiavel, assunto));
                        break;
                    }
                    
                    case 'E':{
                        String nomeEvento = br.readLine().trim();
                        String local = br.readLine().trim();
                        int prioridade = Integer.parseInt(br.readLine().trim());
                        compromissos.inserir(new Evento(id, data, hora, duracao, prioridade, nomeEvento, local));
                        break;

                    }
                    
                    case 'P':{
                        boolean adiavel = Boolean.parseBoolean(br.readLine().trim());
                        String motivo = br.readLine().trim();
                        String local = br.readLine().trim();
                        int prioridade = Integer.parseInt(br.readLine().trim());
                        compromissos.inserir(new Pessoal(id, data, hora, duracao, prioridade, adiavel, motivo, local));
                        break;
                    }
                }
                
                //le linha em branco
                br.readLine();
            }
        }
        
        br.close();
        return compromissos;
    }
    
    static void processarCompromissos(Lista<Compromisso> todosCompromissos) throws IOException{
        Lista<Compromisso> confirmados = new Lista<>();
        Lista<Conflito> adiados = new Lista<>();
        Lista<Conflito> cancelados = new Lista<>();
        
        //ordena compromissos
        ComparadorPrioridadeComDesempate comparadorPrioridade = new ComparadorPrioridadeComDesempate();
        todosCompromissos.ordenar(comparadorPrioridade);
        
        Lista<Compromisso>.Node node = todosCompromissos.getInicio();
        while(node != null){
            Compromisso atual = node.dado;
            boolean conflitou = false;
            Compromisso conflitanteMaisImportante = null;
            
            //percorre todos os compromissos ordenados 
            Lista<Compromisso>.Node confNode = confirmados.getInicio();
            while(confNode != null){
                Compromisso confirmado = confNode.dado;
                
                if(TemConflito(atual, confirmado)){
                    conflitou = true;
                    
                    //encontra o compromisso confirmado mais importante
                    if(conflitanteMaisImportante == null){
                        conflitanteMaisImportante = confirmado;
                    } 
                    
                    else{
                        if(comparadorPrioridade.comparar(confirmado, conflitanteMaisImportante) < 0){
                            conflitanteMaisImportante = confirmado;
                        }
                    }
                }
                
                confNode = confNode.prox;
            }
            

            //se n conflita, adiciona nos confirmados
            if(!conflitou){
                confirmados.inserir(atual);
            } 
            
            //decide se eh adiado ou cancelado
            else{
                if(atual.isAdiavel()){
                    adiados.inserir(new Conflito(atual, conflitanteMaisImportante));
                } 
                
                else{
                    cancelados.inserir(new Conflito(atual, conflitanteMaisImportante));
                }
            }
            
            node = node.prox;
        }
        //gera os relat com os resultados
        gerarRelatorios(confirmados, adiados, cancelados, todosCompromissos);
    }

    //gera todos os arquivos de relat
    static void gerarRelatorios(Lista<Compromisso> confirmados, Lista<Conflito> adiados, Lista<Conflito> cancelados, Lista<Compromisso> todos) throws IOException{
        
        ComparadorDataHora comparadorDataHora = new ComparadorDataHora();
        confirmados.ordenar(comparadorDataHora);
        
        PrintWriter fConfirm = new PrintWriter("relatconfirmados.txt");
        Lista<Compromisso>.Node node = confirmados.getInicio();
        while(node != null){
            Compromisso c = node.dado;
            fConfirm.println(c.getData().toString() + " " + c.getHora().toString());
            fConfirm.println(c.getIdFormatado());
            fConfirm.println(c.getDescricao());
            fConfirm.println();
            node = node.prox;
        }

        fConfirm.close();
        
        Lista<Compromisso> adiadosComp = new Lista<>();
        Lista<Conflito>.Node adNode = adiados.getInicio();
        while(adNode != null){
            adiadosComp.inserir(adNode.dado.compromisso);
            adNode = adNode.prox;
        }
        
        ComparadorPrioridadeComDesempate comparadorAdiados = new ComparadorPrioridadeComDesempate();
        adiadosComp.ordenar(comparadorAdiados);
        
        PrintWriter fAdiados = new PrintWriter("relatadiados.txt");
        node = adiadosComp.getInicio();
        while(node != null){
            Compromisso c = node.dado;
            Compromisso conflitante = null;
            Lista<Conflito>.Node confNode = adiados.getInicio();
            while(confNode != null){
                if(confNode.dado.compromisso == c){
                    conflitante = confNode.dado.conflitante;
                    break;
                }
                confNode = confNode.prox;
            }
            
            fAdiados.println(c.getIdFormatado());
            fAdiados.println(c.getDescricao());
            fAdiados.println(c.getPrioridadeFinal());

            if(conflitante != null){
                fAdiados.println(conflitante.getIdFormatado());
            } 

            else{
                fAdiados.println("N/A");
            }

            fAdiados.println();
            node = node.prox;
        }
        fAdiados.close();
        
        Lista<Compromisso> canceladosComp = new Lista<>();
        Lista<Conflito>.Node canNode = cancelados.getInicio();
        while(canNode != null){
            canceladosComp.inserir(canNode.dado.compromisso);
            canNode = canNode.prox;
        }
        
        ComparadorDuracaoComDesempate comparadorCancelados = new ComparadorDuracaoComDesempate();
        canceladosComp.ordenar(comparadorCancelados);
        
        PrintWriter fCancel = new PrintWriter("relatcancelados.txt");
        node = canceladosComp.getInicio();
        while(node != null){
            Compromisso c = node.dado;
            Compromisso conflitante = null;
            Lista<Conflito>.Node confNode = cancelados.getInicio();
            while(confNode != null){
                if(confNode.dado.compromisso == c){
                    conflitante = confNode.dado.conflitante;
                    break;
                }

                confNode = confNode.prox;
            }
            
            fCancel.println(c.getIdFormatado());
            fCancel.println(c.getDescricao());
            fCancel.println(c.getPrioridadeFinal());
            
            if(conflitante != null){
                fCancel.println(conflitante.getIdFormatado());
            } 

            else{
                fCancel.println("N/A");
            }
            fCancel.println();
            node = node.prox;
        }
        
        fCancel.close();
        
        ComparadorId comparadorId = new ComparadorId();
        todos.ordenar(comparadorId);
        
        PrintWriter fCompleto = new PrintWriter("relatcompromissos.txt");
        node = todos.getInicio();
        while(node != null){
            Compromisso c = node.dado;
            fCompleto.println(c.getIdFormatado() + ": " + c.getDescricao());
            
            int minutosTotais = c.getHora().toMinutos() + c.getDuracao();
            int diasExtras = minutosTotais /(24 * 60);
            int minutosRestantes = minutosTotais %(24 * 60);
            Data dataFim = c.getData().addDias(diasExtras);
            Hora horaFim = new Hora(minutosRestantes / 60, minutosRestantes % 60);
            
            fCompleto.println("Início: " + c.getData().toString() + " " + c.getHora().toString());
            fCompleto.println("Fim: " + dataFim.toString() + " " + horaFim.toString());
            fCompleto.println("Prioridade: " + c.getPrioridadeFinal());
            
            switch(c.getTipo()){
                case 'A':
                    Aula a =(Aula) c;
                    fCompleto.println("Nível: " + a.getNivel());
                    break;

                case 'R':
                    Reuniao r =(Reuniao) c;
                    fCompleto.println("Assunto: " + r.getAssunto());
                    break;
                    
                case 'O':
                    Orientacao o =(Orientacao) c;
                    fCompleto.println("Nível: " + o.getNivel());
                    fCompleto.println("Assunto: " + o.getAssunto());
                    break;

                case 'E':
                    Evento e =(Evento) c;
                    fCompleto.println("Local: " + e.getLocal());
                    break;

                case 'P':
                    Pessoal p =(Pessoal) c;
                    fCompleto.println("Local: " + p.getLocal());
                    break;
            }

            fCompleto.println();
            node = node.prox;
        }

        fCompleto.close();
        
        Scanner fpos = new Scanner(new File("posicoes.txt"));
        PrintWriter fres = new PrintWriter("resultado.txt");
        
        int i = fpos.nextInt();
        int j = fpos.nextInt();
        int k = fpos.nextInt();
        int m = fpos.nextInt();
        
        int soma = 0;
        
        if(i > 0 && i <= confirmados.getTamanho()){
            Compromisso c = confirmados.get(i-1);
            if(c != null){
                soma += c.getDuracao();
            } 
        }
        
        if(j > 0 && j <= adiadosComp.getTamanho()){
            Compromisso c = adiadosComp.get(j-1);
            if(c != null){
                soma += c.getDuracao();
            }
        }
        
        if(k > 0 && k <= canceladosComp.getTamanho()){
            Compromisso c = canceladosComp.get(k-1);
            if(c != null){
                soma += c.getDuracao();
            } 
        }
        
        if(m > 0 && m <= todos.getTamanho()){
            Compromisso c = todos.get(m-1);
            if(c != null){
                soma += c.getDuracao();
            }
        }
        
        fres.println(soma);
        fpos.close();
        fres.close();
    }
    
    public static void main(String[] args) throws IOException{
        //le todos os compromissos do arquivo
        Lista<Compromisso> compromissos = lerCompromissos("agenda.txt");
        
        //processa os compromissos e gera os relatorios
        processarCompromissos(compromissos);
    }
}