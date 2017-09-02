public class _14 {
    private static  int lg(int N) {
        if (N <= 0) return -1;
        int res = -1;
        int t = 1;
        while (t <= N) {
            ++res;
            t *= 2;
        }
        return res;
    }

    public static void main(String[] args) {
        System.out.println(lg(1023));// 9
        System.out.println(lg(1024));// 10
        System.out.println(lg(0)); // -1
        System.out.println(lg(1));// 0
        System.out.println(lg(2));// 1
    }
}
