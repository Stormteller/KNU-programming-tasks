package com.univ.labs;

import java.util.Arrays;
import java.util.Random;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.stream.IntStream;

class Task extends Thread {

    private int[] array;
    private CyclicBarrier barrier;

    public Task(int[] arr, CyclicBarrier cb) {
        array = arr;
        barrier = cb;
    }

    @Override
    public void run() {
        Random rnd = new Random();

        while (true) {
            if(Thread.currentThread().isInterrupted()) break;

            int toChangeRnd = rnd.nextInt(2);
            int indChange = rnd.nextInt(array.length);
            if(toChangeRnd == 1) array[indChange] += 1;
            else array[indChange] -= 1;

            array[indChange] %= 10;

            try {
                barrier.await();
            } catch (InterruptedException | BrokenBarrierException e) {
                e.printStackTrace();
            }
        }
    }
}


class CheckTask implements Runnable {

    private Task[] tasks;
    private int[][] arrays;

    public CheckTask(int[][] arrs, Task[] t) {
        arrays = arrs;
        tasks = t;
    }

    @Override
    public void run() {
        int firstSum = IntStream.of(arrays[0]).sum();
        int secondSum = IntStream.of(arrays[1]).sum();
        int thirdSum = IntStream.of(arrays[2]).sum();

        if(firstSum == secondSum && secondSum == thirdSum) {
            for (Task task : tasks) {
                task.interrupt();
            }
        }
        System.out.println(Arrays.toString(arrays[0]));
        System.out.println(Arrays.toString(arrays[1]));
        System.out.println(Arrays.toString(arrays[2]));
        System.out.println();
    }
}

public class Main {

    public static void main(String[] args) {
        Random random = new Random();
        int size = 5;
        int[] arr1 = new int[size];
        int[] arr2 = new int[size];
        int[] arr3 = new int[size];


        for (int i = 0; i < size; i++){
            arr1[i] = random.nextInt(10);
            arr2[i] = random.nextInt(10);
            arr3[i] = random.nextInt(10);
        }

        Task[] tasks = new Task[3];
        CyclicBarrier barrier = new CyclicBarrier(3,
                new CheckTask(new int[][] { arr1, arr2, arr3 }, tasks));
        tasks[0] = new Task(arr1, barrier);
        tasks[1] = new Task(arr2, barrier);
        tasks[2] = new Task(arr3, barrier);
        for (Task task : tasks) {
            task.start();
        }
    }
}
