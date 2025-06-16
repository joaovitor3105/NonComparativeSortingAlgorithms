import java.util.Arrays;

public class ListaEstatica {
    private int[] dados;
    private int tamanho;
    private int capacidade;

    public ListaEstatica(int capacidade) {
        this.dados = new int[capacidade];
        this.tamanho = 0;
        this.capacidade = capacidade;
    }

    public void inserir(int valor) {
        if (tamanho == capacidade) {
            throw new IllegalStateException("Lista cheia!");
        }
        dados[tamanho++] = valor;
    }

    public int[] toArray() {
        return Arrays.copyOf(dados, tamanho);
    }

    public void fromArray(int[] array) {
        if (array.length > capacidade) {
            throw new IllegalStateException("Capacidade excedida!");
        }
        System.arraycopy(array, 0, dados, 0, array.length);
        tamanho = array.length;
    }

    public int tamanho() {
        return tamanho;
    }
}