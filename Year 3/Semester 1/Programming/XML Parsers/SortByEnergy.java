package com.univ.labs;

import java.util.Comparator;

public class SortByEnergy implements Comparator {
    @Override
    public int compare(Object o1, Object o2) {
        Candy candy1 = (Candy) o1;
        Candy candy2 = (Candy) o2;
        if (candy1.getEnergy() > candy2.getEnergy()) {
            return 1;
        } else if (candy1.getEnergy() < candy2.getEnergy()) {
            return -1;
        } else {
            return 0;
        }
    }
}
