package com.univ.labs;

import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.locks.ReentrantReadWriteLock;

/**
 * Created by Andrey on 03/26/2017.
 */
public class Worker extends Thread {
    public volatile FieldModel fieldModel;
    public CyclicBarrier barrier;
    public ReentrantReadWriteLock lock;
    byte types;
    int start;
    int finish;

    Worker(FieldModel fieldModel, CyclicBarrier barrier, ReentrantReadWriteLock lock, int start, int finish, byte types){
        this.fieldModel = fieldModel;
        this.barrier = barrier;
        this.lock = lock;
        this.types = types;
        this.start = start;
        this.finish = finish;
    }

    @Override
    public void run() {
        while (true){
            if (this.isInterrupted()) break;
            lock.readLock().lock();
            fieldModel.simulate(types, start, finish);
            lock.readLock().unlock();
            try {
                barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {}
        }
    }
}
