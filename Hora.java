public class Hora{
    private int hora;
    private int minuto;

    public Hora(){
        this(0, 0);
    }

    public Hora(int hora, int minuto){
        this.hora = hora;
        this.minuto = minuto;
    }

    public static Hora fromString(String s){
        String[] partes = s.split(":");
        int h = Integer.parseInt(partes[0]);
        int m = Integer.parseInt(partes[1]);
        return new Hora(h, m);
    }

    //retorna string formatada
    public String toString(){
        return String.format("%02d:%02d", hora, minuto);
    }

    //converte hora para minutos totai
    public int toMinutos(){
        return hora * 60 + minuto;
    }

    //verifica se esta hora e anterior a outra
    public boolean antes(Hora other){
        return this.toMinutos() < other.toMinutos();
    }

    //compara se duas horas sao iguais
    public boolean iguais(Hora other){
        return this.hora == other.hora && this.minuto == other.minuto;
    }

    public int getHora(){ 
        return hora;
    }
    
    public int getMinuto(){ 
        return minuto; 
    }
}