public class Orientacao extends Compromisso{
    private boolean adiavel;
    private String nivel;
    private String assunto;

    public Orientacao(int id, Data data, Hora hora, int duracao, int prioridade, boolean adiavel, String nomeOrientado, String nivel, String assunto){
        super(id, 'O', data, hora, duracao, prioridade, nomeOrientado);
        this.adiavel = adiavel;
        this.nivel = nivel;
        this.assunto = assunto;
        calcularPrioridadeFinal();
    }

    @Override
    public void calcularPrioridadeFinal(){
        //multiplicador 1x
        int multiplicador = 1;
        //se n adiável +1x
        if(!adiavel){
            multiplicador += 1;
        }
        this.prioridadeFinal = this.prioridade * multiplicador;
    }

    @Override
    public String getDescricao(){
        return "Orientação de " + this.descricao;
    }

    @Override
    public boolean isAdiavel(){
        return adiavel;
    }

    public String getNivel(){
        return nivel;
    }

    public String getAssunto(){
        return assunto;
    }
}