import java.util.Arrays;

public class _35 {
    public static void main(String[] args) {
        int SIDES = 6;
        byte[] array = new byte[2 * SIDES - 1];
        for (int i = 1; i <= SIDES; i++) {
            for (int j = 1; j <= SIDES; j++) {
                ++array[i + j - 2];
            }
        }

        System.out.println(Arrays.toString(array));
    }
}
