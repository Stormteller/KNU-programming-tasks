package com.univ.labs;

class ThreadFramework {
    int c = 0;
    BakeryLock lock;

    ThreadFramework(int[] a) {
        lock = new BakeryLock(a.length);
        for(int i = 0; i < a.length; i++) {
            final int idx = i;
            Thread thread = new Thread(new Runnable() {
                @Override
                public void run() {
                    while (true) {
                        lock.lock();
                        c+=a[idx];
                        lock.unlock();
                    }
                }
            });
            lock.register(thread);
            thread.start();
        }
        while(true) {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println(c);
        }
    }
}

public class Main {
    public static void main(String[] args) {
        int[] arr = { 1, -2, -1, 2, 1, 2, -1, 1, -2, 1 };
        new ThreadFramework(arr);
    }
}
