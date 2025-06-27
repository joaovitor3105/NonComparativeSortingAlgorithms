// Fila Linear
public class LinearQueue {
    private int[] data;
    private int front;
    private int rear;
    private int size;
    private int capacity;

    public LinearQueue(int capacity) {
        this.data = new int[capacity];
        this.front = 0;
        this.rear = -1;
        this.size = 0;
        this.capacity = capacity;
    }

    public void enqueue(int value) {
        if (size >= capacity)
            return;
        rear = (rear + 1) % capacity;
        data[rear] = value;
        size++;
    }

    public int dequeue() {
        if (size <= 0)
            return -1;
        int value = data[front];
        front = (front + 1) % capacity;
        size--;
        return value;
    }

    public boolean isEmpty() {
        return size <= 0;
    }

    public int getSize() {
        return size;
    }

    public int[] getData() {
        return data;
    }

    public int getFront() {
        return front;
    }

    public void clear() {
        front = 0;
        rear = -1;
        size = 0;
    }
}