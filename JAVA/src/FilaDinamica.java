import java.util.Iterator;
import java.util.LinkedList;

public class FilaDinamica {
    private LinkedList<Integer> fila;

    public FilaDinamica() {
        this.fila = new LinkedList<>();
    }

    public void enfileirar(int valor) {
        fila.addLast(valor);
    }

    public int desenfileirar() {
        return fila.removeFirst();
    }

    public int[] toArray() {
        int[] array = new int[fila.size()];
        Iterator<Integer> it = fila.iterator();
        for (int i = 0; i < array.length; i++) {
            array[i] = it.next();
        }
        return array;
    }

    public void fromArray(int[] array) {
        fila.clear();
        for (int valor : array) {
            fila.addLast(valor);
        }
    }

    public int tamanho() {
        return fila.size();
    }
}