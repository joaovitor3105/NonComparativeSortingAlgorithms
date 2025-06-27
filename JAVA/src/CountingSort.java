public class CountingSort {
    public static int findMax(int[] array) {
        if (array.length == 0)
            return 0;
        int max = array[0];
        for (int i = 1; i < array.length; i++) {
            if (array[i] > max) {
                max = array[i];
            }
        }
        return max;
    }

    public static boolean isArraySorted(int[] array) {
        for (int i = 1; i < array.length; i++) {
            if (array[i] < array[i - 1]) {
                return false;
            }
        }
        return true;
    }

    public static void countingSort(int[] array) {
        if (array.length <= 1)
            return;

        int max = findMax(array);
        int[] count = new int[max + 1];

        // Contar ocorrências
        for (int value : array) {
            count[value]++;
        }

        // Reconstruir array ordenado
        int index = 0;
        for (int i = 0; i <= max; i++) {
            while (count[i] > 0) {
                array[index++] = i;
                count[i]--;
            }
        }
    }
}