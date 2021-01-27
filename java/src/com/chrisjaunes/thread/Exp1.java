package com.chrisjaunes.thread;

/**
 * designed a exp about synchronized and monitor
 * Question:
 * Can function B access variable x in thread PB when we execute the function A in thread PA?
 * Can thread PB execute function B when we execute the function A in thread PA?
 * 
 * @author ChrisJaunes
 * @date 2021/01/27
 */
public class Exp1 {
    private final MyMonitor1 mon1 = new MyMonitor1();
    private final MyMonitor2 mon2 = new MyMonitor2();
    private final MyMonitor3 mon3 = new MyMonitor3();
    private final MyMonitor4 mon4 = new MyMonitor4();
    public void main() {
        new Thread(mon1::A).start();
        new Thread(mon1::B).start();

        new Thread(mon2::A).start();
        new Thread(mon2::B).start();

        new Thread(mon3::A).start();
        new Thread(mon3::B).start();

        new Thread(mon4::A).start();
        new Thread(mon4::B).start();
        System.out.println("main thread finish");
    }
    static private class MyMonitor1 {
        int x = 0;

        public synchronized void A() {
            System.out.println("we execute function A about MyMonitor1");
            x = 1;
            while (true) {
            }
        }

        public synchronized void B() {
            System.out.println("we execute function B about MyMonitor1");
            x = 2;
            System.out.println("we can access variable x");
        }
    }
    static private class MyMonitor2 {
        public synchronized void A() {
            System.out.println("we execute function A about MyMonitor2");
            while (true) {
            }
        }

        public synchronized void B() {
            System.out.println("we execute function B about MyMonitor2");
        }
    }
    static private class MyMonitor3 {
        public synchronized void A() {
            System.out.println("we execute function A about MyMonitor3");
        }

        public synchronized void B() {
            System.out.println("we execute function B about MyMonitor3");
        }
    }
    static private class MyMonitor4 {
        public synchronized void A() {
            System.out.println("we execute function A about MyMonitor4");
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("we executed function A about MyMonitor4");
        }

        public synchronized void B() {
            System.out.println("we execute function B about MyMonitor4");
        }
    }
}
