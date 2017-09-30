package weibo;

import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Search {
    public static List<String> search(String content) {
        List<String> result = new ArrayList<>();
        String regex = "list_realtimehot\\\\\">((\\\\u[0-9a-f]{4}|[a-zA-Z0-9 ])+)<\\\\/a>";
        Matcher m = Pattern.compile(regex).matcher(content);
        while (m.find()) {
            String s = Decode.decode(m.group(1));
            if (result.isEmpty() || !s.equals(result.get(result.size() - 1))) {
                result.add(s);
            }
        }
        return result;
    }
}
