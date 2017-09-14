package lambda;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Random;

import static java.util.stream.Collectors.toList;

class Apple {
    private Integer weight;

    Apple(int weight) {
        this.weight = weight;
    }

    Integer getWeight() {
        return weight;
    }

    @Override
    public String toString() {
        return Integer.toString(weight);
    }
}

public class Sort {
    public static void main(String[] args) {
        Random rand = new Random(47);
        ArrayList<Apple> apples = new ArrayList<>();
        for (int i = 0; i < 30; i++) {
            apples.add(new Apple(rand.nextInt(200)));
        }
        apples.sort(Comparator.comparing(Apple::getWeight));
        System.out.println(apples);
        new Thread(()->System.out.println("Good")).start();
        // 感觉好像C#的LINQ啊
        List<Integer> l = apples.stream()
                .map(Apple::getWeight)
                .distinct()
                .filter(i -> i > 100)
                .collect(toList());
        System.out.println(l);
    }
}
