package weibo;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Decode {
    public static String decode(String str) {
        Matcher m = Pattern.compile("\\\\u([0-9a-f]{4})").matcher(str);
        while (m.find()) {
            char ch = (char) Integer.parseInt(m.group(1), 16);
            str = str.replaceAll("\\\\u" + m.group(1), ch + "");
        }

        return str;
    }
}
