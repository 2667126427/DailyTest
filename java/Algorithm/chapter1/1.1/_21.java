import java.util.Scanner;

public class _21 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        while (in.hasNextLine()) {
            String data = in.nextLine();
            String[] datas = data.split(" ");

            if (!data.isEmpty() && datas.length == 3) {
                System.out.printf("%s %s %s %.3f\n", datas[0], datas[1], datas[2],
                        Double.valueOf(datas[1]) / Double.valueOf(datas[2]));
            }
            else {
                break;
            }
        }

        in.close();
    }
}
