package SendMessage;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.Scanner;

public class Client {
//    private static final String IP_ADDR = "180.76.234.154";//服务器地址
    private static final String IP_ADDR = "localhost";//服务器地址
    private static final int PORT = 12345;//服务器端口号

    public static void main(String[] args) {
        System.out.println("客户端启动...");
        System.out.println("输入'q'退出。");
        Scanner in = new Scanner(System.in);
        String str = "hello";
        while (!str.equalsIgnoreCase("q")) {
            Socket socket = null;
            try {
                //创建一个流套接字并将其连接到指定主机上的指定端口号  
                socket = new Socket(IP_ADDR, PORT);
                //向服务器端发送数据
                DataOutputStream out = new DataOutputStream(socket.getOutputStream());
                System.out.print("请输入: ");
                str = in.nextLine();
                // 写入socket
                out.writeUTF(str);
                out.close();
            } catch (Exception e) {
                System.out.println("客户端异常:" + e.getMessage());
            } finally {
                if (socket != null) {
                    try {
                        socket.close();
                    } catch (IOException e) {
                        socket = null;
                        System.out.println("客户端 finally 异常:" + e.getMessage());
                    }
                }
            }
        }
        in.close();
    }
}    