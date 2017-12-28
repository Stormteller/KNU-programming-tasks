package com.univ.labs;

import java.util.Random;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class Main {

    static final String[] NAMES = new String[] {"Bob", "Steve", "Carl", "Jack", "Adolf", "AAA", "FFF", "Tile", "Peter", "Crap", "Sandra", "Winny", "Marshal", "Donald"};
    static final String[] NUMBERS = new String[] {"1212213", "1212214", "1212215", "498658546", "12122135461", "4568465", "7465486564", "1328473", "79863543543", "153485475", "778852135", "134289999"};

    public static void main(String[] args) {
        ReentrantReadWriteLock rwlock = new ReentrantReadWriteLock();

        Random rand = new Random();

        for(int i = 0; i <= 25; i++) {
            int nameIdx = Math.abs(rand.nextInt()) % NAMES.length;
            int numberIdx = Math.abs(rand.nextInt()) % NUMBERS.length;
            new Thread(new WriteName(NAMES[nameIdx], NUMBERS[numberIdx], rwlock)).start();
        }

        for(int i = 0; i <= 10; i++) {
            int numberIdx = Math.abs(rand.nextInt()) % NUMBERS.length;
            new Thread(new SearchByNumber(NUMBERS[numberIdx], rwlock)).start();
        }

        for(int i = 0; i <= 10; i++) {
            int nameIdx = Math.abs(rand.nextInt()) % NAMES.length;
            new Thread(new SearchByName(NAMES[nameIdx], rwlock)).start();
        }

        for(int i = 0; i <= 10; i++) {
            int nameIdx = Math.abs(rand.nextInt()) % NAMES.length;
            int numberIdx = Math.abs(rand.nextInt()) % NUMBERS.length;
            new Thread(new RemoveName(NAMES[nameIdx], NUMBERS[numberIdx], rwlock)).start();
        }
    }
}
