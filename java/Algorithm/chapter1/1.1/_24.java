public class _24 {
    private static int gcd(int a, int b, int depth) {
        System.out.printf("%d depth: %d %d\n", depth, a, b);
        if (b == 0) return a;
        return gcd(b, a % b, depth + 1);
    }

    public static void main(String[] args) {
        System.out.println(gcd( 1111111, 1234567, 1));
    }
}
