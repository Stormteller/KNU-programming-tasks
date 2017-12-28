package com.univ.labs;

import java.io.FileWriter;
import java.io.IOException;
import java.util.concurrent.locks.ReentrantReadWriteLock;
/**
 * Created by Andrey on 03/08/2017.
 */
public class WriteName implements Runnable {
    String name;
    String number;
    ReentrantReadWriteLock locker;
    String fileName = "input.txt";

    WriteName(String name, String number, ReentrantReadWriteLock locker){
        this.name = name;
        this.number = number;
        this.locker = locker;
    }

    @Override
    public void run() {
        locker.writeLock().lock();

        try(FileWriter writer = new FileWriter(fileName, true)) {
            writer.write(name + " " + number);
            writer.append('\n');
            writer.flush();
            writer.close();
            System.out.println("Added: " + name + " " + number);
        } catch (IOException e) {
            return;
        }
        locker.writeLock().unlock();
    }
}
