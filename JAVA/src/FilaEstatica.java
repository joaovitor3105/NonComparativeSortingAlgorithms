public class FilaEstatica {
    private int[] dados;
    private int inicio;
    private int fim;
    private int tamanho;
    private int capacidade;

    public FilaEstatica(int capacidade) {
        this.dados = new int[capacidade];
        this.inicio = 0;
        this.fim = -1;
        this.tamanho = 0;
        this.capacidade = capacidade;
    }

    public void enfileirar(int valor) {
        if (tamanho == capacidade) {
            throw new IllegalStateException("Fila cheia!");
        }
        fim = (fim + 1) % capacidade;
        dados[fim] = valor;
        tamanho++;
    }

    public int desenfileirar() {
        if (tamanho == 0) {
            throw new IllegalStateException("Fila vazia!");
        }
        int valor = dados[inicio];
        inicio = (inicio + 1) % capacidade;
        tamanho--;
        return valor;
    }

    public int[] toArray() {
        int[] array = new int[tamanho];
        for (int i = 0; i < tamanho; i++) {
            array[i] = dados[(inicio + i) % capacidade];
        }
        return array;
    }

    public void fromArray(int[] array) {
        if (array.length > capacidade) {
            throw new IllegalStateException("Capacidade excedida!");
        }
        inicio = 0;
        fim = -1;
        tamanho = 0;
        for (int valor : array) {
            enfileirar(valor);
        }
    }

    public int tamanho() {
        return tamanho;
    }
}