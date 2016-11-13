package com.univ.labs;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Date;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;


/**
 * Created by Andrey on 10/23/2016.
 */
public class BakeryLock extends FixnumLock {
    private ArrayList<Boolean> chosen;
    private ArrayList<Integer> ticket;

    public BakeryLock(int threadNum) {
        super(threadNum);
        chosen = new ArrayList<>(Collections.nCopies(threadNum, false));
        ticket = new ArrayList<>(Collections.nCopies(threadNum, 0));
    }

    int max(ArrayList<Integer> arr) {
        int maxVal = 0;
        for(int i = 0; i < arr.size(); i++) {
            if(maxVal < arr.get(i)) maxVal = arr.get(i);
        }
        return maxVal;
    }

    @Override
    public void lock() {
        int threadId = (int)getId(Thread.currentThread());
        chosen.set(threadId, true);
        ticket.set(threadId, max(ticket) + 1);
        chosen.set(threadId, false);

        for(int i = 0; i < threadNum; i++) {
            if(i != threadId) {
                while(chosen.get(i)) { Thread.yield(); }
                while ((ticket.get(i) != 0) && (ticket.get(threadId) > ticket.get(i) ||
                        (ticket.get(threadId).equals(ticket.get(i)) && threadId > i))) { Thread.yield(); }
            }
        }
    }

    @Override
    public void unlock() {
        int threadId = (int)getId(Thread.currentThread());
        ticket.set(threadId, 0);
    }


    @Override
    public boolean tryLock() {
        int threadId = (int)getId(Thread.currentThread());
        chosen.set(threadId, true);
        ticket.set(threadId, max(ticket) + 1);
        chosen.set(threadId, false);

        for(int i = 0; i < threadNum; i++) {
            if(i != threadId) {
                if(chosen.get(i)) { unlock(); return false; }
                if ((ticket.get(i) != 0) && (ticket.get(threadId) > ticket.get(i) ||
                        (ticket.get(threadId) == ticket.get(i) && threadId > i))) { unlock(); return false;     }
            }
        }
        return true;
    }

    @Override
    public Condition newCondition() { return new Condition() {
        @Override
        public void await() throws InterruptedException {

        }

        @Override
        public void awaitUninterruptibly() {

        }

        @Override
        public long awaitNanos(long nanosTimeout) throws InterruptedException {
            return 0;
        }

        @Override
        public boolean await(long time, TimeUnit unit) throws InterruptedException {
            return false;
        }

        @Override
        public boolean awaitUntil(Date deadline) throws InterruptedException {
            return false;
        }

        @Override
        public void signal() {

        }

        @Override
        public void signalAll() {

        }
    };}

    @Override
    public void lockInterruptibly() {

    }

    @Override
    public boolean tryLock(long time, TimeUnit unit) {
        return true;
    }
}
