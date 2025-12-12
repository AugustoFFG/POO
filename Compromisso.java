public abstract class Compromisso{
    protected int id;
    protected char tipo;
    protected Data data;
    protected Hora hora;
    protected int duracao;
    protected int prioridade;
    protected int prioridadeFinal;
    protected String descricao;

    public Compromisso(int id, char tipo, Data data, Hora hora, int duracao, int prioridade, String descricao){
        this.id = id;
        this.tipo = tipo;
        this.data = data;
        this.hora = hora;
        this.duracao = duracao;
        this.prioridade = prioridade;
        this.descricao = descricao;
        this.prioridadeFinal = prioridade;
    }

    public abstract void calcularPrioridadeFinal();
    public abstract String getDescricao();
    public abstract boolean isAdiavel();

    public String getIdFormatado(){
        return String.format("%06d", id);
    }

    public int getId(){
        return id;
    }
    
    public char getTipo(){
        return tipo;
    }

    public Data getData(){
        return data;
    }

    public Hora getHora(){
        return hora;
    }

    public int getDuracao(){
        return duracao;
    }

    public int getPrioridade(){
        return prioridade;
    }

    public int getPrioridadeFinal(){
        return prioridadeFinal;
    }
    
    //comparaçao
    public boolean antes(Compromisso outro){
        if (!this.data.equals(outro.data)){
            return this.data.antes(outro.data);
        }
        return this.hora.antes(outro.hora);
    }
    
    public boolean maiorPrioridade(Compromisso outro){
        //compara prioridade final
        return this.prioridadeFinal > outro.prioridadeFinal;
    }
    
    public boolean menorId(Compromisso outro){
        return this.id < outro.id;
    }
    
    public boolean menorDuracao(Compromisso outro){
        return this.duracao < outro.duracao;
    }
}