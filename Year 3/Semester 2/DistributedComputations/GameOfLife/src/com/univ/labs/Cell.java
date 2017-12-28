package com.univ.labs;

import java.util.concurrent.locks.ReentrantReadWriteLock;

/**
 * Created by Andrey on 03/26/2017.
 */
public class Cell {
    public ReentrantReadWriteLock lock = new ReentrantReadWriteLock();
    public byte value = 0;
}
