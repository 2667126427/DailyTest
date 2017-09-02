public class _3AllEquals {
    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Too few arguments");
            return;
        }
        int a = Integer.valueOf(args[0]), b = Integer.valueOf(args[1]), c = Integer.valueOf(args[2]);
        if (a == b && b == c) {
            System.out.println("Yes they all equal");
        }else {
            System.out.println("No they don't equal");
        }
    }
}
