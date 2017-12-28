package com.univ.labs;

import java.io.*;
import java.util.concurrent.locks.ReentrantReadWriteLock;
/**
 * Created by Andrey on 03/08/2017.
 */
public class RemoveName implements Runnable {
    String name;
    String number;
    ReentrantReadWriteLock locker;
    String fileName = "input.txt";

    RemoveName(String name, String number, ReentrantReadWriteLock locker){
        this.name = name;
        this.number = number;
        this.locker = locker;
    }

    @Override
    public void run() {

        locker.writeLock().lock();

        File newFile = new File(fileName + ".tmp");
        File oldFile = new File(fileName);
        try {
            FileReader reader = new FileReader(oldFile);
            FileWriter writer = new FileWriter(newFile, false);

            boolean flag = false;

            int ch;
            while ((ch = reader.read()) != -1) {
                String currName = "" + (char) ch;
                String currNumber = "";

                while ((ch = reader.read()) != -1 && (char) ch != ' ')
                    currName += (char) ch;

                while ((ch = reader.read()) != -1 && (char) ch == ' ') ;

                currNumber += (char) ch;
                while ((ch = reader.read()) != -1 && (char) ch != '\n')
                    currNumber += (char) ch;

                if (!(number.equals(currNumber) && name.equals(currName))) {
                    writer.write(currName + " " + currNumber);
                    writer.append('\n');
                    writer.flush();
                }else flag = true;

            }
            if (flag) System.out.println("Removed: " + name + " " + number);
            else  System.out.println("Not found: " + name + " " + number);

            reader.close();
            writer.close();
            oldFile.exists();
            oldFile.delete();
            newFile.renameTo(oldFile);

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        locker.writeLock().unlock();
    }
}
