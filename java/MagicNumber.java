public class MagicNumber {
    // 想用Set的，想想还是自己弄个数组吧
    private static int[] isRecorded = new int[100];

    // 吸血鬼不会拼。。。
    private void magicNumber() {
        int[] nums = new int[4];
        for (int i = 1000; i < 10000; i++) {
            if (i % 100 == 0) {
                continue;
            }
            // 把数字拆分到数组里好麻烦
            int t = i;
            nums[0] = t / 1000;
            t %= 1000;
            nums[1] = t / 100;
            t %= 100;
            nums[2] = t / 10;
            nums[3] = t % 10;
            isMagic(i, nums, 0);
        }
    }

    private void isMagic(int number, int[] nums, int index) {
        int a, b;
        for (int i = index + 1; i < nums.length; i++) {
            // Java交换数字好麻烦
            int t = nums[index];
            nums[index] = nums[i];
            nums[i] = t;
            a = nums[0] * 10 + nums[1];
            b = nums[2] * 10 + nums[3];
            if (a * b == number && isRecorded[number % 91] == 0) {
                System.out.println(a + " * " + b + " = " + number);
                isRecorded[number % 91] = 1;
            }
            isMagic(number, nums, index + 1);
            t = nums[index];
            nums[index] = nums[i];
            nums[i] = t;
        }
    }
    // 1260 1395 1435 1530 1827 2187 6880

    public static void main(String[] args) {
        // 计算时间
        long t1 = System.currentTimeMillis();
        MagicNumber main = new MagicNumber();
        main.magicNumber();
        System.out.println(System.currentTimeMillis() - t1);
    }
}

