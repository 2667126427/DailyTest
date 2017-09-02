public class _15 {
    private static int[] histogram(int[] a, int M) {
        // Orz
        if (M < 0) {
            System.err.println("negative argument M");
            return null;
        }

        int[] result = new int[M];
        for (int t : a) {
            if (t < a.length && t >= 0) {
                ++result[t];
            }
        }

        return null;
    }

    public static void main(String[] args) {

    }
}
