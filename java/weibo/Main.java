package weibo;

import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;
import java.util.List;

public class Main {
    private static final String utf = "UTF-8";

    public static void main(String[] args) {
        String url = "http://s.weibo.com/top/summary?cate=realtimehot";
        List<String> result = new ArrayList<>();
        try {
            URL weiboUrl = new URL(url);
            URLConnection connection = weiboUrl.openConnection();
            InputStream is = connection.getInputStream();
            byte[] buf = new byte[1024];
            StringBuilder sb = new StringBuilder();

            while (is.read(buf, 0, buf.length) > 0) {
                sb.append(new String(buf, "utf-8"));
            }
            is.close();
            result = Search.search(sb.toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
        for (int i = 1; i <= result.size(); i++) {
            System.out.println(i + ": " + result.get(i - 1));
        }
    }
}

