import com.baidu.aip.speech.AipSpeech;
import com.baidu.aip.speech.TtsResponse;
import org.json.JSONObject;

import java.io.FileOutputStream;
import java.io.IOException;
import java.util.HashMap;

/**
 * Created by yaning on 2017/7/27.
 */
public class Main {


    //设置APPID/AK/SK
    public static final String APP_ID = "9953195";
    public static final String API_KEY = "nkPXCWhzczmyn0rGnbGZBNX3";
    public static final String SECRET_KEY = "hSkXghf9BPGPrkQFyOxA2Oc6Lw4gigYN";

    public static void main(String[] args) throws IOException {
//        // 初始化一个FaceClient
//        AipSpeech client = new AipSpeech(APP_ID, API_KEY, SECRET_KEY);
//        // 设置可选参数
//        HashMap<String, Object> options = new HashMap<String, Object>();
//        options.put("spd", "5");
//        options.put("pit", "5");
//        options.put("per", "4");
//        TtsResponse res = client.synthesis("你是我的小呀小苹果", "zh", 1, options);
//        System.out.println(res.getErrorCode());
////        TtsResponse res1 = client.synthesis("你好百度", "zh", 1, options);
//        System.out.println(res.getErrorCode());
//        byte[] data = res.getData();
//        String fileName = "test.mp3";
//        FileOutputStream outputStream = new FileOutputStream(fileName);
//        outputStream.write(data);
//        System.out.println(fileName + " was downloaded successfully");
//        outputStream.close();
//
        AipSpeech client = new AipSpeech(APP_ID, API_KEY, SECRET_KEY);
        client.setConnectionTimeoutInMillis(2000);
        client.setSocketTimeoutInMillis(60000);
        JSONObject res = client.asr("test.wav", "wav", 16000, null);
        System.out.println(res.toString());
    }
}
