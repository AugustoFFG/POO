public class Data{
    private int dia;
    private int mes;
    private int ano;

    public Data(){
        this(1, 1, 2000);
    }

    public Data(int dia, int mes, int ano){
        this.dia = dia;
        this.mes = mes;
        this.ano = ano;
    }

    public static Data fromString(String s){
        String[] partes = s.split("/");
        int d = Integer.parseInt(partes[0]);
        int m = Integer.parseInt(partes[1]);
        int a = Integer.parseInt(partes[2]);
        return new Data(d, m, a);
    }

    public String toString(){
        return String.format("%02d/%02d/%04d", dia, mes, ano);
    }

    public Data addDias(int dias){
        int d = this.dia;
        int m = this.mes;
        int a = this.ano;
        
        d += dias;
        
        while(d > diasNoMes(m, a)){
            d -= diasNoMes(m, a);
            m++;
            if(m > 12){
                m = 1;
                a++;
            }
        }
        
        return new Data(d, m, a);
    }
    
    private int diasNoMes(int mes, int ano){
        switch(mes){
            case 2:
                return(ano % 4 == 0 &&(ano % 100 != 0 || ano % 400 == 0)) ? 29 : 28;
            case 4: case 6: case 9: case 11:
                return 30;
            default:
                return 31;
        }
    }

    public boolean iguais(Data other){
        return this.dia == other.dia && this.mes == other.mes && this.ano == other.ano;
    }

    public boolean antes(Data other){
        if(this.ano != other.ano){
            return this.ano < other.ano;
        }

        else if(this.mes != other.mes){
            return this.mes < other.mes;
        }

        else{
            return this.dia < other.dia;
        }
        
    }

    //calculo de conflito
    public long ConverteMin(){
        long totalDias = 0;
        
        //dias desde 2000
        for(int ano = 2000; ano < this.ano; ano++){
            totalDias +=(ano % 4 == 0 &&(ano % 100 != 0 || ano % 400 == 0)) ? 366 : 365;
        }
        
        //dias dos meses no ano atual
        for(int mes = 1; mes < this.mes; mes++){
            totalDias += diasNoMes(mes, this.ano);
        }
        
        //dias do mes atual
        totalDias += this.dia - 1;
        
        return totalDias * 24 * 60;
    }

    public int getDia(){ 
        return dia; 
    }
    
    public int getMes(){ 
        return mes;
    }
    
    public int getAno(){ 
        return ano; 
    }
}