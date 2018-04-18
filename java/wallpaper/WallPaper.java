import java.io.*;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class WallPaper {
    // 1s = 1000ms
    private final static int SECONDS = 1000;

    public static void main(String[] args) throws IOException {
        for (int i = 0; i < args.length; i++) {
            System.out.println(args[i]);
        }
        int threadCount = args.length > 0 ? Integer.valueOf(args[0]) : 10;
        int pages = args.length > 1 ? Integer.valueOf(args[1]) : 10;
        String tempUrl = "https://wall.alphacoders.com/by_resolution.php?w=3840&h=2160&page=%d";
        Downloader downloader = new Downloader();
        ExecutorService service = Executors.newFixedThreadPool(threadCount);
        for (int i = 0; i <= pages; i++) {
            for (String url : downloader.getUrls(String.format(tempUrl, i))) {
                service.execute(new Task(url));
            }
        }
        service.shutdown();
        System.out.println("Main end.");
    }

    static class Downloader {
        List<String> getUrls(String uri) throws IOException {
            URL url;
            url = new URL(uri);
            URLConnection conn = url.openConnection();
            conn.setConnectTimeout(30 * SECONDS);
            BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));
            List<String> urls = new ArrayList<>();
            String line;
            Pattern pattern = Pattern.compile("data-href=\"(https://initiate.alphacoders.com/download/wallpaper[/a-z0-9]+)\"");
            while ((line = reader.readLine()) != null) {
                Matcher matcher = pattern.matcher(line);
                if (matcher.find()) {
                    urls.add(matcher.group(1));
                }
            }
            return urls;
        }
    }

    static class Task implements Runnable {
        private URL url;

        Task(String url) {
            try {
                this.url = new URL(url);
            } catch (MalformedURLException e) {
                e.printStackTrace();
            }
        }

        @Override
        public void run() {
            try {
                URLConnection conn = url.openConnection();
                conn.setConnectTimeout(30 * SECONDS);
                InputStream is = conn.getInputStream();
                String path = url.getPath();
                String fileName = path.replaceAll("[/.:a-z]+", "") + ".jpg";
                File file = new File(fileName);
                if (!file.exists()) {
                    int length;
                    byte[] buffer = new byte[4096];
                    FileOutputStream fos = new FileOutputStream(fileName);
                    while ((length = is.read(buffer, 0, buffer.length)) > 0) {
                        fos.write(buffer, 0, length);
                    }
                    fos.close();
                    is.close();
                    System.out.println(fileName + " was downloaded.");
                } else {
                    System.out.println(fileName + " has existed.");
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}