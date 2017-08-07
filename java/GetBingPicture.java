import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.nio.file.FileAlreadyExistsException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class GetBingPicture {

    public static void main(String[] args) throws Exception {
        GetBingPicture getBingPicture = new GetBingPicture();
        String  home = "http://cn.bing.com";
        String url = getBingPicture.GetUrl(home);
        getBingPicture.SavePicture(home + url);
    }

    private String GetUrl(String home_url) throws Exception {
        InputStream is = new URL(home_url).openStream();
        byte[] buff = new byte[1024];
        StringBuilder builder = new StringBuilder();
        while (is.read(buff, 0, buff.length) > 0) {
            builder.append(new String(buff, "UTF-8"));
        }
        is.close();
        Matcher matcher = Pattern.compile("g_img=\\{url: \"([\\w_\\-/]+?\\.jpg)\"").matcher(builder.toString());
        if (matcher.find()) {
            System.out.println("Find the url: " + matcher.group(1));
            return matcher.group(1);
        } else {
            throw new Exception("Not found the url");
        }
    }

    private void SavePicture(String url) throws IOException {
        InputStream is = new URL(url).openStream();
        String name = url.substring(url.lastIndexOf("/" ) + 1);
        File file = new File(name);
        if (file.exists())  {
            throw new  FileAlreadyExistsException(name + " has existed");
        } else {
            file.createNewFile();
            FileOutputStream fileOutputStream = new FileOutputStream(file);
            byte[] buff = new byte[1024];
            int len = 0;
            while ((len = is.read(buff, 0, buff.length)) > 0) {
                fileOutputStream.write(buff, 0, len);
            }
            System.out.println(name + " was downloaded successfully");
            fileOutputStream.close();
        }
        is.close();
    }
}
