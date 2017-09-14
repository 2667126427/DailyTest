package lambda;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Predicate;

public class Filter {
    public static <T> List<T> filter(List<T> items, Predicate<T> p) {
        List<T> results = new ArrayList<>();
        for (T i : items) {
            if (p.test(i)) {
                results.add(i);
            }
        }
        return results;
    }

    public static void main(String[] args) {
        int[] array = {1, 6, 7, 3425, 675, 23, 423, 2343};
        List<Integer> ints = new ArrayList<>();
        for (int t : array) {
            ints.add(t);
        }
        System.out.println(filter(ints, (Integer t) -> t > 100));
    }

}
