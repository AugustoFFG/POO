public class Reuniao extends Compromisso{
    private boolean adiavel;
    private String assunto;

    public Reuniao(int id, Data data, Hora hora, int duracao, int prioridade, boolean adiavel, String assunto){
        super(id, 'R', data, hora, duracao, prioridade, assunto);
        this.adiavel = adiavel;
        this.assunto = assunto;
        calcularPrioridadeFinal();
    }

    @Override
    public void calcularPrioridadeFinal(){
        //multiplicador 4x
        int multiplicador = 4;
        //se n adiavel  +1
        if(!adiavel){
            multiplicador += 1;
        }
        this.prioridadeFinal = this.prioridade * multiplicador;
    }

    @Override
    public String getDescricao(){
        return "Reunião de Departamento";
    }

    @Override
    public boolean isAdiavel(){
        return adiavel;
    }

    public String getAssunto(){
        return assunto;
    }
}