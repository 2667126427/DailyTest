package SendMessage;

import Time.Time;

import java.io.DataInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
    private static final int PORT = 12345;//监听的端口号

    public static void main(String[] args) {
        // 启动服务器
        Server server = new Server();
        server.init();
    }

    private void init() {
        try {
            ServerSocket serverSocket = new ServerSocket(PORT);
            while (true) {
                // 一旦有堵塞, 则表示服务器与客户端获得了连接
                Socket client = serverSocket.accept();
                // 处理这次连接
                new HandlerThread(client);
            }
        } catch (Exception e) {
            System.out.println("服务器异常: " + e.getMessage());
        }
    }

    private class HandlerThread implements Runnable {
        private Socket socket;

        HandlerThread(Socket client) {
            socket = client;
            new Thread(this).start();
        }

        public void run() {
            try {
                // 读取客户端数据
                DataInputStream input = new DataInputStream(socket.getInputStream());
                String clientInputStr = input.readUTF();//这里要注意和客户端输出流的写方法对应,否则会抛 EOFException
                // 处理客户端数据
                // 创建当天的日志文件
                // 加同步锁，防止两个socket同时打开
                synchronized (this) {
                    String fileName = Time.getDayTime() + ".log";
                    // 追加打开
                    FileWriter writer = new FileWriter(fileName, true);
                    // 记录信息和接受时间
                    writer.write(Time.getSecondTime() + ": " + clientInputStr + "\n");
                    // 关闭writer才会保存
                    writer.close();
                }
            } catch (Exception e) {
                try {
                    // 记录错误日志
                    synchronized (this) {
                        FileWriter writer = null;
                        writer = new FileWriter(Time.getDayTime() + "error.log", true);
                        writer.write(Time.getSecondTime() + ": " + e + "\n");
                        writer.close();
                    }
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
            } finally {
                if (socket != null) {
                    try {
                        socket.close();
                    } catch (Exception e) {
                        socket = null;
                    }
                }
            }
        }
    }
}
