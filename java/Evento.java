public class Evento extends Compromisso{
    private String local;

    public Evento(int id, Data data, Hora hora, int duracao, int prioridade, String nomeEvento, String local){
        super(id, 'E', data, hora, duracao, prioridade, nomeEvento);
        this.local = local;
        calcularPrioridadeFinal();
    }

    @Override
    public void calcularPrioridadeFinal(){
        //multiplicador 3x
        this.prioridadeFinal = this.prioridade * 3;
    }
    

    @Override
    public String getDescricao(){
        return this.descricao;
    }

    @Override
    public boolean isAdiavel(){
        //eventos n sao adiaveis
        return false;
    }

    public String getLocal(){
        return local;
    }
}