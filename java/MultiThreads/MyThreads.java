import java.util.concurrent.locks.ReentrantLock;

/**
 * Time: 22/06/17 20:00
 * Created by yaning.
 * School: HUST
 * Email: wangyaning6166@gmail.com
 */
public class MyThreads {
    public static void main(String[] args) throws InterruptedException {
        MyThread myThread = new MyThread();
        for (int i = 0; i < 10; i++) {
            new Thread(myThread).start();
        }
        Thread.sleep(1000);

        System.out.println(myThread.getNum());
        System.out.println("Main thread finished");
    }

}

class MyThread implements Runnable {

    int num;
    ReentrantLock lock = new ReentrantLock();

    public MyThread() {
        this.num = 0;
    }

    public int getNum() {
        return num;
    }

    @Override
    public void run() {
        lock.lock();
        try {
            for (int i = 0; i < 1000; i++) {
                num++;
            }
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            lock.unlock();
        }
    }
}
