import java.util.ArrayList;

public class ListaDinamica {
    private ArrayList<Integer> lista;

    public ListaDinamica() {
        this.lista = new ArrayList<>();
    }

    public void inserir(int valor) {
        lista.add(valor);
    }

    public int[] toArray() {
        int[] array = new int[lista.size()];
        for (int i = 0; i < array.length; i++) {
            array[i] = lista.get(i);
        }
        return array;
    }

    public void fromArray(int[] array) {
        lista.clear();
        for (int valor : array) {
            lista.add(valor);
        }
    }

    public int tamanho() {
        return lista.size();
    }
}