public class Lista<T>{
    public class Node{
        public T dado;
        public Node prox;

        public Node(T dado){
            this.dado = dado;
            this.prox = null;
        }
    }

    private Node inicio;
    private int tamanho;

    public Lista(){
        inicio = null;
        tamanho = 0;
    }

    public void inserir(T dado){
        Node novo = new Node(dado);
        if (inicio == null){
            inicio = novo;
        } else{
            Node atual = inicio;
            while (atual.prox != null){
                atual = atual.prox;
            }
            atual.prox = novo;
        }
        tamanho++;
    }

    //comparação
    public interface Comparador<T>{
        int comparar(T a, T b);
    }

    //metodo de ordenação
    public void ordenar(Comparador<T> comparador){
        if (inicio == null || inicio.prox == null) return;
        
        Object[] array = toArray();
        
        //aplica o quicksort
        quicksort(array, 0, tamanho - 1, comparador);
        
        //reconstroi lista
        fromArray(array);
    }
    
    private void quicksort(Object[] array, int esquerda, int direita, Comparador<T> comparador){
        if (esquerda < direita){
            int indicePivo = particionar(array, esquerda, direita, comparador);
            quicksort(array, esquerda, indicePivo - 1, comparador);
            quicksort(array, indicePivo + 1, direita, comparador);
        }
    }
    
    private int particionar(Object[] array, int esquerda, int direita, Comparador<T> comparador){
        @SuppressWarnings("unchecked")
        T pivo = (T) array[direita];
        
        int i = esquerda - 1;
        
        for (int j = esquerda; j < direita; j++){
            @SuppressWarnings("unchecked")
            T elementoAtual = (T) array[j];
            
            //comparador
            if (comparador.comparar(elementoAtual, pivo) < 0){
                i++;
                Object temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
        
        Object temp = array[i+1];
        array[i+1] = array[direita];
        array[direita] = temp;
        
        return i + 1;
    }
    
    private Object[] toArray(){
        Object[] array = new Object[tamanho];
        Node atual = inicio;
        for (int i = 0; i < tamanho; i++){
            array[i] = atual.dado;
            atual = atual.prox;
        }
        return array;
    }
    
    private void fromArray(Object[] array){
        //limpa lista
        inicio = null;
        tamanho = 0;
        
        //reinserw os elementos
        for (Object obj : array){
            @SuppressWarnings("unchecked")
            T dado = (T) obj;
            inserir(dado);
        }
    }

    public Node getInicio(){
        return inicio;
    }

    public int getTamanho(){
        return tamanho;
    }
    
    public T get(int index){
        if (index < 0 || index >= tamanho) return null;
        
        Node atual = inicio;
        for (int i = 0; i < index; i++){
            atual = atual.prox;
        }
        return atual.dado;
    }
}