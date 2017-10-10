import java.util.Arrays;

public class ThreeMagic {
    private static final int[] nums = new int[6];
    private static final boolean[] used = new boolean[10];

    private static boolean check() {
        int numA = 0;
        int numB = 0;

        for (int num : nums) {
            numA = numA * 10 + num;
        }

        for (int i = 1; i < nums.length; i++) {
            numB = numB * 10 + nums[i];
        }
        numB = numB * 10 + nums[0];

        return numA * 3 == numB;
    }

    private static void search(int currentDepth) {
        if (currentDepth == nums.length) {
            if (check()) {
                System.out.println(Arrays.toString(nums));
            }
            return;
        }

        for (int i = 0; i < 10; i++) {
            if (!used[i]) {
                used[i] = true;
                nums[currentDepth] = i;
                search(currentDepth + 1);
                used[i] = false;
            }
        }
    }

    public static void main(String[] args) {
        search(0);
    }
}
