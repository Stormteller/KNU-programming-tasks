package com.univ.labs;

import java.util.concurrent.locks.ReentrantReadWriteLock;

/**
 * Created by Andrey on 03/26/2017.
 */
public class FieldUpdater implements Runnable {
    public FieldPanel fieldPanel;
    public volatile FieldModel fieldModel;
    public ReentrantReadWriteLock lock;
    public int timeSleep = 200;

    public FieldUpdater(FieldPanel fieldPanel, FieldModel fieldModel, ReentrantReadWriteLock lock){
        this.fieldPanel = fieldPanel;
        this.fieldModel = fieldModel;
        this.lock = lock;
    }

    @Override
    public void run() {
        lock.writeLock().lock();
        fieldModel.swapField();
        lock.writeLock().unlock();
        fieldPanel.repaint();
        System.out.println("Barrier");
        try {
            Thread.sleep(timeSleep);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
