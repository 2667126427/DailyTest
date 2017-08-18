public class Solution {
    // 数学是个好东西，直接算出来通项求和
    int calculate(int number, int count) {
        int temp = 1;
        for (int i = 0; i < count; ++i) {
            temp *= 10;
        }
        // 溢出了，变成double再搞
        return (int)((10.0 * (temp - 1) / 9 - count) * number / 9);
    }

    int compute(int number, int count) {
        int m = 0;
        for (int i = 0; i < count; i++) {
            m += (int) (number * Math.pow(10, i));
        }
        return m;
    }

    int count(int n, int number) {
        int s = 0;
        int sum = 0;
        for (int i = 1; i <= number; i++) {
            s = compute(n, i);
            sum += s;
        }
        return sum;
    }

    // 挺无聊的小程序计算a + aa + aaa + aaaa + ... + aa...a
    public static void main(String[] args) {
        Solution sol = new Solution();
        int n = 2;
        int count = 5;
        System.out.println(sol.calculate(n, count));
        System.out.println(sol.count(n, count));
    }
}
