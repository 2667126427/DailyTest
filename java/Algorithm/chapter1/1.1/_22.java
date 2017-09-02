import java.util.Arrays;

public class _22 {
    private static int binarySearch(int[] array, int target, int left, int right, int depth) {
        System.out.printf("%d depth: %d %d\n", depth, left, right);
        if (left > target) return -1;
        int mid = left + (right - left) / 2;
        if (array[mid] > target) {
            return binarySearch(array, target, left, mid - 1, depth + 1);
        } else if (array[mid] < target) {
            return binarySearch(array, target, mid + 1, right, depth + 1);
        }
        return mid;
    }


    public static void main(String[] args) {
        int[] array = {1, 76, 9, 7, 3, 783, 4, 23, 423, 324, 654, 4532, 865, 3216, 432, 12265, 4213,};
        Arrays.sort(array);
        System.out.println(Arrays.toString(array));
        System.out.println(binarySearch(array, 423, 0, array.length - 1, 1));
    }
}
