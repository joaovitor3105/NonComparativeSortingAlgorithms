// Fila Dinâmica
public class Queue {
    private Node front;
    private Node rear;
    private int size;

    public Queue() {
        this.front = null;
        this.rear = null;
        this.size = 0;
    }

    public void enqueue(int value) {
        Node newNode = new Node(value);
        if (rear == null) {
            front = rear = newNode;
        } else {
            rear.next = newNode;
            rear = newNode;
        }
        size++;
    }

    public int dequeue() {
        if (isEmpty())
            return -1;
        int value = front.data;
        front = front.next;
        if (front == null)
            rear = null;
        size--;
        return value;
    }

    public boolean isEmpty() {
        return front == null;
    }

    public int getSize() {
        return size;
    }

    public Node getFront() {
        return front;
    }

    public void clear() {
        front = rear = null;
        size = 0;
    }
}