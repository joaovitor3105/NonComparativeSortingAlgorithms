public class MemoryUtils {
    public static long getMemoryUsage() {
        Runtime runtime = Runtime.getRuntime();
        return runtime.totalMemory() - runtime.freeMemory();
    }
}