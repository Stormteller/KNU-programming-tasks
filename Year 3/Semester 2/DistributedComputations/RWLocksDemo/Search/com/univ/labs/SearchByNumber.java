package com.univ.labs;

import java.io.FileReader;
import java.io.IOException;

import java.util.concurrent.locks.ReentrantReadWriteLock;

/**
 * Created by Andrey on 03/08/2017.
 */
public class SearchByNumber implements Runnable {
    String number;
    ReentrantReadWriteLock locker;
    String fileName = "input.txt";

    SearchByNumber(String number, ReentrantReadWriteLock loсker){
        this.number = number;
        this.locker = loсker;
    }

    @Override
    public void run() {
        locker.readLock().lock();
        try(FileReader reader = new FileReader(fileName))
        {
            int ch;
            while((ch=reader.read())!=-1){
                String currName = "" + (char)ch;
                String currNumber = "";

                while ((ch=reader.read())!=-1 && (char)ch != ' ')
                    currName += (char)ch;

                while ((ch=reader.read())!=-1 && (char)ch == ' ');

                currNumber += (char)ch;
                while ((ch = reader.read())!=-1 && (char)ch != '\n')
                    currNumber += (char)ch;
                if (number.equals(currNumber)) {
                    System.out.println("Found by number " + number + ": " + currName);
                    reader.close();
                    locker.readLock().unlock();
                    return;
                }
            }
            System.out.println("Not found " + number);
            reader.close();
        }
        catch(IOException ex){

            System.out.println(ex.getMessage());
        }
        locker.readLock().unlock();
    }
}