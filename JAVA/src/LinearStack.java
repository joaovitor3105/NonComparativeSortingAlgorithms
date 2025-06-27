// Pilha Linear
public class LinearStack {
    private int[] data;
    private int top;
    private int capacity;

    public LinearStack(int capacity) {
        this.data = new int[capacity];
        this.top = -1;
        this.capacity = capacity;
    }

    public void push(int value) {
        if (top >= capacity - 1)
            return;
        data[++top] = value;
    }

    public int pop() {
        if (top < 0)
            return -1;
        return data[top--];
    }

    public boolean isEmpty() {
        return top < 0;
    }

    public int getSize() {
        return top + 1;
    }

    public int[] getData() {
        return data;
    }

    public void clear() {
        top = -1;
    }
}