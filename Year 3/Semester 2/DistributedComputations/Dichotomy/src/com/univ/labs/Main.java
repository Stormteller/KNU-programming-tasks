package com.univ.labs;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;

class Winner extends RecursiveTask<Integer> {

    private ArrayList<Integer> monksSpirit;
    private Integer start;
    private Integer end;

    public Winner(ArrayList monksSp, Integer start, Integer end) {
        monksSpirit = monksSp;
        this.start = start;
        this.end = end;
    }

    public Integer compute() {
        if(end - start == 1)
            return Math.max(monksSpirit.get(start), monksSpirit.get(end));
        if(end - start == 0)
            return monksSpirit.get(start);
        Winner winnerLeft = new Winner(monksSpirit, start, (end + start) / 2);
        winnerLeft.fork();
        Winner winnerRight = new Winner(monksSpirit, (end + start) / 2 + 1,  end);
        return Math.max(winnerLeft.join(), winnerRight.compute());
    }
}

public class Main {

    static final int N = 10;
    static ArrayList<Integer> monksSpirit = new ArrayList<>();

    public static void main(String[] args) {
        Random rnd = new Random();
        for (int i = 0; i < N; i++) monksSpirit.add(rnd.nextInt(255));
        ForkJoinPool pool = new ForkJoinPool();
        Integer winner = pool.invoke(new Winner(monksSpirit, 0, N - 1));
        System.out.println(winner);
        System.out.println(Arrays.toString(monksSpirit.toArray()));
    }
}
