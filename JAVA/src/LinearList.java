// Lista Linear
public class LinearList {
    private int[] data;
    private int size;
    private int capacity;

    public LinearList(int capacity) {
        this.data = new int[capacity];
        this.size = 0;
        this.capacity = capacity;
    }

    public void insert(int value) {
        if (size >= capacity)
            return;
        // Inserir no início (mover todos os elementos para a direita)
        for (int i = size; i > 0; i--) {
            data[i] = data[i - 1];
        }
        data[0] = value;
        size++;
    }

    public void append(int value) {
        if (size >= capacity)
            return;
        data[size++] = value;
    }

    public int get(int index) {
        if (index < 0 || index >= size)
            return -1;
        return data[index];
    }

    public int getSize() {
        return size;
    }

    public int[] getData() {
        return data;
    }

    public void clear() {
        size = 0;
    }
}