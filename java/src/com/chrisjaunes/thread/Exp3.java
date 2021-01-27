package com.chrisjaunes.thread;

/**
 * designed a exp about thread status
 * noted volatile
 * @author ChrisJaunes
 * @date 2021/01/27
 */
public class Exp3 {
    private volatile boolean controlA = true;
    private volatile boolean controlB = true;
    public void main() {
        try {
            // created a new thread t, the thread t state is "new“
            final Thread t = new MyThread();
            System.out.println("1 " + t.getState());
            // start the thread t, the thread state is “runnable”
            t.start();
            System.out.println("2 " + t.getState());
            // cause anonymous thread enter critical region(function test1)
            // thread t finish the loop when controlA be assigned to false
            // thread t be blocked when thread try to enter critical region(function test1)
            // thread t state is "blocked"
            new Thread(this::test1).start();
            try{Thread.sleep(50); }catch (InterruptedException e) {e.printStackTrace();}
            controlA = false;
            try{Thread.sleep(50); }catch (InterruptedException e) {e.printStackTrace();}
            System.out.println("3 " + t.getState());
            // we assign controlB to false, anonymous thread will finish the loop and finish
            // thread t will enter critical region(function test1) and leave critical region(function test1)
            // thread t will enter critical region(function test2)
            // thread t call wait, thread t state is "waiting"
            controlB = false;
            try{Thread.sleep(50); }catch (InterruptedException e) {e.printStackTrace();}
            System.out.println("4 " + t.getState());
            // cause thread t release this lock, anonymous thread can enter critical region(function test2)
            new Thread(this::test2).start();
            try{Thread.sleep(50); }catch (InterruptedException e) {e.printStackTrace();}
            System.out.println("[Exp3::test] wait will unlock");
            // cause object use notifyAll(), thread t and anonymous thread continue
            // thread t call Thread.sleep, the state is “time_waiting"
            synchronized (this) { notifyAll(); }
            try{Thread.sleep(50); }catch (InterruptedException e) {e.printStackTrace();}
            System.out.println("5 " + t.getState());
            // join can block self, when thread died, thread t state is "terminated"
            t.join(1000);
            System.out.println("6 " + t.getState());
            t.join();
            System.out.println("6 " + t.getState());
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private synchronized void test1() {
        System.out.println("[Exp3::test1] we execute thread " + Thread.currentThread());
        while (controlB) { Thread.onSpinWait(); }
    }
    private synchronized void test2() {
        System.out.println("[Exp3::test2] we execute thread " + Thread.currentThread());
        try{ wait(); } catch (InterruptedException e) { e.printStackTrace(); }
        System.out.println("[Exp3::test2] we wakeup thread " + Thread.currentThread());
    }

    private class MyThread extends Thread{
        @Override
        public void run() {
            System.out.println("[Exp3::MyThread::Run] we execute thread " + Thread.currentThread());
            while (controlA) { Thread.onSpinWait(); }
            test1();
            test2();
            try { Thread.sleep(10000); }catch (InterruptedException e) { e.printStackTrace(); }
        }
    }
}
