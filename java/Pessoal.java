public class Pessoal extends Compromisso{
    private boolean adiavel;
    private String local;

    public Pessoal(int id, Data data, Hora hora, int duracao, int prioridade, boolean adiavel, String motivo, String local){
        super(id, 'P', data, hora, duracao, prioridade, motivo);
        this.adiavel = adiavel;
        this.local = local;
        calcularPrioridadeFinal();
    }

    @Override
    public void calcularPrioridadeFinal(){
        //multiplicador 2x
        int multiplicador = 2;
        //se nao adiável +1x
        if(!adiavel){ 
            multiplicador += 1;
        }
        this.prioridadeFinal = this.prioridade * multiplicador;
    }

    @Override
    public String getDescricao(){
        return this.descricao;
    }

    @Override
    public boolean isAdiavel(){
        return adiavel;
    }

    public String getLocal(){
        return local;
    }
}