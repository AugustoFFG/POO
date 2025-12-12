public class Aula extends Compromisso{
    private String nivel;

    public Aula(int id, Data data, Hora hora, int duracao, int prioridade, String disciplina, String nivel){
        super(id, 'A', data, hora, duracao, prioridade, disciplina);
        this.nivel = nivel;
    }

    @Override
    public void calcularPrioridadeFinal(){
        //multiplicador 2x
        this.prioridadeFinal = this.prioridade * 2;
    }

    @Override
    public String getDescricao(){
        return "Aula de " + this.descricao;
    }

    @Override
    public boolean isAdiavel(){
        //aulas n sao adiaveis
        return false;
    }

    public String getNivel(){
        return nivel;
    }
}