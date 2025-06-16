import java.util.Arrays;

public class SortUtils {
    public static void countingSort(int[] array) {
        if (array.length == 0) return;

        int max = Arrays.stream(array).max().getAsInt();
        int[] count = new int[max + 1];

        for (int num : array) {
            count[num]++;
        }

        int idx = 0;
        for (int i = 0; i <= max; i++) {
            while (count[i] > 0) {
                array[idx++] = i;
                count[i]--;
            }
        }
    }
}