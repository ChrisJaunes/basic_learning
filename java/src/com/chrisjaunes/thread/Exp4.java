package com.chrisjaunes.thread;

/**
 * designed a exp about Object.wait and Object.notify
 * What happens if we use the other Object.wait()?
 * What happens if we use Object.wait() and Object.notify()?
 * @author ChrisJaunes
 */
public class Exp4 {
    public void main() {
        new MyThread1().start();
        try { Thread.sleep(50); } catch (InterruptedException e) { e.printStackTrace(); }
        synchronized (lock) { lock.notify(); }

        new Thread(new MyThread2()).start();
        new Thread(new MyThread2()).start();
        try {
            Thread.sleep(50);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        Thread t3 = new Thread(new MyThread3());
        t3.start();
        try { Thread.sleep(50); } catch (InterruptedException e) { e.printStackTrace(); }
        Thread t4 = new Thread(new MyThread4());
        t4.start();
        try { Thread.sleep(50); } catch (InterruptedException e) { e.printStackTrace(); }
        System.out.println("[Exp4::main]" + t3.getState());
    }

    static private final Object lock = new Object();
    static private final Object tmp = new Object();

    static private class MyThread1 extends Thread {
        @Override
        public void run() {
            synchronized (lock) {
                try {
                    System.out.println("[Exp4::MyThread1::run] ");
                    // thread will release the lock and enter queue of waiting
                    lock.wait();
                    // JVM will throws "java.lang.IllegalMonitorStateException: current thread is not owner"
                    // tmp.wait();
                    // wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    static private class MyThread2 implements Runnable {
        @Override
        public void run() {
            synchronized (lock) {
                for (int i = 0; i < 5; i++) {
                    try {
                        System.out.println("[Exp4::MyThread2::run]" + Thread.currentThread() + "i : " + i);
                        lock.notify();
                        lock.wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                lock.notify();
            }
        }
    }

    static private class MyThread3 implements Runnable {
        @Override
        public void run() {
            synchronized (lock) {
                try{ lock.wait(); } catch (InterruptedException e) {e.printStackTrace();}
            }
        }
    }
    static private class MyThread4 implements Runnable {
        @Override
        public void run() {
            synchronized (lock) {
                lock.notify();
                try { Thread.sleep(1000); } catch (InterruptedException e) { e.printStackTrace(); }
            }
        }
    }
}