import java.util.Arrays;

public class PilhaEstatica {
    private int[] dados;
    private int topo;
    private int capacidade;

    public PilhaEstatica(int capacidade) {
        this.dados = new int[capacidade];
        this.topo = -1;
        this.capacidade = capacidade;
    }

    public void empilhar(int valor) {
        if (topo == capacidade - 1) {
            throw new IllegalStateException("Pilha cheia!");
        }
        dados[++topo] = valor;
    }

    public int desempilhar() {
        if (topo == -1) {
            throw new IllegalStateException("Pilha vazia!");
        }
        return dados[topo--];
    }

    public boolean vazia() {
        return topo == -1;
    }

    public int[] toArray() {
        return Arrays.copyOf(dados, topo + 1);
    }

    public void fromArray(int[] array) {
        if (array.length > capacidade) {
            throw new IllegalStateException("Capacidade excedida!");
        }
        topo = -1;
        for (int valor : array) {
            empilhar(valor);
        }
    }

    public int tamanho() {
        return topo + 1;
    }
}