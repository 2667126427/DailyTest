public class _9 {
    public static String toBinary(int num) {
        StringBuilder sb = new StringBuilder();
        if (num <= 0) return "";
        while (num > 0) {
            sb = sb.append(num % 2);
            num /= 2;
        }
        return sb.reverse().toString();
    }

    public static void main(String[] args) {
        int i = 100;
        System.out.println(Integer.toBinaryString(i));
        System.out.println(toBinary(100));
    }
}
