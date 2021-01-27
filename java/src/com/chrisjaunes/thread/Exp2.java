package com.chrisjaunes.thread;

/**
 * designed a exp about thread and runnable
 * How we use the class about thread?
 * What happens if we use the same variables to construct 2 thread?
 * @author ChrisJaunes
 * @date 2021/01/27
 */
public class Exp2 {
    public void main() {
        new MyThread1().start();
        new Thread(new MyThread2()).start();

        MyThread3 myThread3 = new MyThread3();
        new Thread(myThread3).start();
        new Thread(myThread3).start();

        MyThread4 myThread4 = new MyThread4();
        new Thread(myThread4).start();
        new Thread(myThread4).start();

        MyThread5 myThread5 = new MyThread5();
        new Thread(myThread5).start();
        new Thread(myThread5).start();
    }

    static private class MyThread1 extends Thread{
        @Override
        public void run() {
            System.out.println("we executed function run of MyThread1 " + Thread.currentThread());
        }
    }
    static private class MyThread2 implements Runnable{
        @Override
        public void run() {
            System.out.println("we execute function run of Thread2" + Thread.currentThread());
        }
    }
    static private class MyThread3 implements Runnable{
        @Override
        public void run() {
            System.out.println("we execute function run of Thread3" + Thread.currentThread());
        }
    }
    static private class MyThread4 implements Runnable{
        private int x = 0;
        @Override
        public void run() {
            ++x;
            System.out.println("we execute function run of Thread4, x " + x + " " + Thread.currentThread());
        }
    }
    static private class MyThread5 implements Runnable{
        @Override
        public void run() {
            System.out.println("we execute function run of Thread5" + Thread.currentThread());
            synchronized (this) {
                System.out.println("we sleep the thread" + Thread.currentThread());
                while (true) {}
            }
        }
    }
}
