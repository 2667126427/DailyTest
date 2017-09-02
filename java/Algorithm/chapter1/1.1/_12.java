public class _12 {
    public static void main(String[] args) {
        final int len = 10;
        int[] a = new int[len];
        for (int i = 0; i < len; i++) {
            a[i] = len - i - 1;
        }
        for (int i = 0; i < len; i++) {
            a[i] = a[a[i]];
        }
        for (int t : a) {
            System.out.println(t);
        }
        // output 0 1 2 3 4 4 3 2 1 0
    }
}
