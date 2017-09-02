public class _20 {
    public static double ln(int N) {
        double t = 1;
        for (int i = 2; i <= N; i++) {
            t *= i;
        }
        return Math.log(t);
    }


    public static void main(String[] args) {
        for (int i = 1; i < 10; i++) {
            System.out.println(ln(i));
        }
    }
}
