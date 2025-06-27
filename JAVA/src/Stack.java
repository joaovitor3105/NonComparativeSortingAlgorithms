// Pilha Dinâmica
public class Stack {
    private Node top;
    private int size;

    public Stack() {
        this.top = null;
        this.size = 0;
    }

    public void push(int value) {
        Node newNode = new Node(value);
        newNode.next = top;
        top = newNode;
        size++;
    }

    public int pop() {
        if (isEmpty())
            return -1;
        int value = top.data;
        top = top.next;
        size--;
        return value;
    }

    public boolean isEmpty() {
        return top == null;
    }

    public int getSize() {
        return size;
    }

    public Node getTop() {
        return top;
    }

    public void clear() {
        top = null;
        size = 0;
    }
}