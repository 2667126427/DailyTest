package math;

import org.jetbrains.annotations.Contract;

import java.util.Arrays;

public class LIS {
    @Contract(pure = true)
    // 二分查找target插入到array里时大于前面的最后一个位置例1 2 3 5 插入6后变成1 2 3 6
    private static int lowBoundary(int[] array, int target, int end) {
        int s = 0, e = end;
        if (array[e] < target) return e + 1;
        int mid = 0;
        // 二分查找时间复杂度logN
        while (s < e) {
            mid = s + (e - s) / 2;
            if (array[mid] <= target) {
                s = mid + 1;
            } else {
                e = mid;
            }
        }
        return s;
    }

    @Contract(pure = true)
    // 使用辅助数组和二分查找使时间复杂度降到NlogN
    private static int lis(int[] array) {
        if (array == null || array.length == 0) return 0;
        int[] temp = new int[array.length];
        temp[0] = array[0];
        int index = 0;
        int max = 0;
        int[] result = null;
        for (int i = 1; i < array.length; i++) {
            // 获取要插入的位置
            index = lowBoundary(temp, array[i], index);
            temp[index] = array[i];
            max = index + 1 > max ? index + 1 : max;
            // 下面这个可以用来记录所得到的最长递增字串，需要把上面那句注释掉
//            if (index + 1 > max) {
//                max = index + 1;
//                result = new int[max];
//                System.arraycopy(temp, 0, result, 0, max);
//            }
        }

        return max;
    }

    public static void main(String[] args) {
        // 16个数字的时候不存在长度为5的递增字串，递减字串差不多，插入位置需要是小于前面的最靠后位置，也需要是
        int[] array = {6, 5, 8, 7, 3, 4, 1, 2, 14, 13, 16, 15, 11, 12, 9, 10};
        System.out.println(lis(array));
    }
}
