import java.util.Stack;

public class PilhaDinamica {
    private Stack<Integer> pilha;

    public PilhaDinamica() {
        this.pilha = new Stack<>();
    }

    public void empilhar(int valor) {
        pilha.push(valor);
    }

    public int desempilhar() {
        return pilha.pop();
    }

    public boolean vazia() {
        return pilha.isEmpty();
    }

    public int[] toArray() {
        int[] array = new int[pilha.size()];
        for (int i = 0; i < array.length; i++) {
            array[i] = pilha.get(pilha.size() - 1 - i); 
        }
        return array;
    }

    public void fromArray(int[] array) {
        pilha.clear();
        for (int i = array.length - 1; i >= 0; i--) {
            pilha.push(array[i]);
        }
    }

    public int tamanho() {
        return pilha.size();
    }
}