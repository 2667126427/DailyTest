public class _5 {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Too few arguments");
            return;
        }
        double a = Double.valueOf(args[0]), b = Double.valueOf(args[1]);

        if (a >= 0.0 && a <= 1.0 && b >= 0.0 && b <= 1.0) {
            System.out.println("Yes they all between 0 and 1");
        }else {
            System.out.println("Sorry they not all in 0 and 1");
        }
    }
}
