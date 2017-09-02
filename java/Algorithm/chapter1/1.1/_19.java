public class _19 {

    static long[] fibo = new long[100];

    public static long F(int N) {
//        if (N == 0) return 0;
//        if (N == 1) return 1;
//        return F(N - 1) + F(N - 2);
        return fibo[N];
    }


    public static void main(String[] args) {
        fibo[0] = 0;
        fibo[1] = 1;
        for (int i = 2; i < fibo.length; i++) {
            fibo[i] = fibo[i - 1] + fibo[i - 2];
        }
        for (int i = 0; i < 100; i++) {
            System.out.println(i + " " + F(i));
        }
    }
}
