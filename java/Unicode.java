import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Unicode {
    public static String decodeUnicode(String ascii) {

        List<String> ascii_s = new ArrayList<String>();
        Matcher m = Pattern.compile("\\\\u[0-9a-fA-F]{4}").matcher(ascii);
        while (m.find()) {
            ascii_s.add(m.group());
        }
        for (int i = 0, j = 2; i < ascii_s.size(); i++) {
            String code = ascii_s.get(i).substring(j, j + 4);
            char ch = (char) Integer.parseInt(code, 16);
            ascii = ascii.replace(ascii_s.get(i), String.valueOf(ch));
        }
        return ascii;
    }

    public static void main(String[] args) {
        System.out.println("Test for unicode");
        Scanner in = new Scanner(System.in);
        int code = in.nextInt();
        String str = "你好world so \\u" + code;
        System.out.println(str);
        System.out.println(decodeUnicode(str));
        in.close();
    }
}
