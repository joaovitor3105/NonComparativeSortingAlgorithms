// Conversores entre estruturas e arrays
public class Converters {
    // Conversões Lista Ligada
    public static int[] listToArray(LinkedList list) {
        if (list.getSize() == 0)
            return null;

        int[] array = new int[list.getSize()];
        Node current = list.getHead();

        // Lista insere no início, então elementos estão em ordem reversa
        for (int i = list.getSize() - 1; i >= 0; i--) {
            array[i] = current.data;
            current = current.next;
        }
        return array;
    }

    public static LinkedList arrayToList(int[] array) {
        LinkedList list = new LinkedList();
        // Inserir em ordem reversa para manter ordem original
        for (int i = array.length - 1; i >= 0; i--) {
            list.insert(array[i]);
        }
        return list;
    }

    // Conversões Pilha Dinâmica
    public static int[] stackToArray(Stack stack) {
        if (stack.getSize() == 0)
            return null;

        int[] array = new int[stack.getSize()];
        Node current = stack.getTop();

        // Pilha está em ordem reversa, converter para ordem de inserção
        for (int i = stack.getSize() - 1; i >= 0; i--) {
            array[i] = current.data;
            current = current.next;
        }
        return array;
    }

    public static Stack arrayToStack(int[] array) {
        Stack stack = new Stack();
        for (int value : array) {
            stack.push(value);
        }
        return stack;
    }

    // Conversões Fila Dinâmica
    public static int[] queueToArray(Queue queue) {
        if (queue.getSize() == 0)
            return null;

        int[] array = new int[queue.getSize()];
        Node current = queue.getFront();

        for (int i = 0; i < queue.getSize(); i++) {
            array[i] = current.data;
            current = current.next;
        }
        return array;
    }

    public static Queue arrayToQueue(int[] array) {
        Queue queue = new Queue();
        for (int value : array) {
            queue.enqueue(value);
        }
        return queue;
    }

    // Conversões Lista Linear
    public static int[] linearListToArray(LinearList list) {
        if (list.getSize() == 0)
            return null;

        int[] array = new int[list.getSize()];
        System.arraycopy(list.getData(), 0, array, 0, list.getSize());
        return array;
    }

    public static LinearList arrayToLinearList(int[] array) {
        LinearList list = new LinearList(array.length);
        for (int value : array) {
            list.append(value);
        }
        return list;
    }

    // Conversões Pilha Linear
    public static int[] linearStackToArray(LinearStack stack) {
        if (stack.getSize() == 0)
            return null;

        int[] array = new int[stack.getSize()];
        System.arraycopy(stack.getData(), 0, array, 0, stack.getSize());
        return array;
    }

    public static LinearStack arrayToLinearStack(int[] array) {
        LinearStack stack = new LinearStack(array.length);
        for (int value : array) {
            stack.push(value);
        }
        return stack;
    }

    // Conversões Fila Linear
    public static int[] linearQueueToArray(LinearQueue queue) {
        if (queue.getSize() == 0)
            return null;

        int[] array = new int[queue.getSize()];
        int index = queue.getFront();

        for (int i = 0; i < queue.getSize(); i++) {
            array[i] = queue.getData()[index];
            index = (index + 1) % queue.getData().length;
        }
        return array;
    }

    public static LinearQueue arrayToLinearQueue(int[] array) {
        LinearQueue queue = new LinearQueue(array.length);
        for (int value : array) {
            queue.enqueue(value);
        }
        return queue;
    }
}