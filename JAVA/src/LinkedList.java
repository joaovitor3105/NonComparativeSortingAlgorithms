// Lista Ligada Dinâmica
public class LinkedList {
    private Node head;
    private int size;

    public LinkedList() {
        this.head = null;
        this.size = 0;
    }

    public void insert(int value) {
        Node newNode = new Node(value);
        newNode.next = head;
        head = newNode;
        size++;
    }

    public int getSize() {
        return size;
    }

    public Node getHead() {
        return head;
    }

    public void clear() {
        head = null;
        size = 0;
    }
}