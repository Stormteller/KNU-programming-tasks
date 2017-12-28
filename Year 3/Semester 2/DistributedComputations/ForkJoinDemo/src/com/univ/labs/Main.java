package com.univ.labs;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveAction;


class Matrix {
    public int[][] array;
    public int width;
    public int height;
    private Random rand = new Random();

    Matrix(int n, int m) {
        height = n;
        width = m;
        array = new int[n][m];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                array[i][j] = rand.nextInt() % 10;
    }
}

class Calc extends RecursiveAction {

    private Matrix a, b, c;
    private int row;

    Calc(Matrix a, Matrix b, Matrix c) {
        this(a, b, c, -1);
    }

    Calc(Matrix a, Matrix b, Matrix c, int row) {
        this.a = a;
        this.b = b;
        this.c = c;
        this.row = row;
    }

    @Override
    protected void compute() {
        if (row == -1) {
            List<Calc> tasks = new ArrayList<>();
            for (int row = 0; row < a.height; row++) {
                tasks.add(new Calc(a, b, c, row));
            }
            invokeAll(tasks);
        } else {
            rowByColumn(a, b, c, row);
        }
    }

    void rowByColumn(Matrix a, Matrix b, Matrix c, int row) {
        for (int j = 0; j < b.width; j++)
            for (int k = 0; k < a.width; k++)
                c.array[row][j] = c.array[row][j] +  a.array[row][k] * b.array[k][j];
    }
}


public class Main {

    public static void main(String[] args) {
        int matSize = 1000;

        Matrix a = new Matrix(matSize, matSize);
        Matrix b = new Matrix(matSize, matSize);
        Matrix c = new Matrix(matSize, matSize);



//        long timeStart =  System.currentTimeMillis();
        ForkJoinPool pool = new ForkJoinPool(4);
        pool.invoke(new Calc(a, b, c));
        pool.invoke(new Calc(a, b, c));
        long timeStart =  System.currentTimeMillis();
        pool.invoke(new Calc(a, b, c));
        long timeExecute = System.currentTimeMillis() - timeStart;
        System.out.println("Fork join time: " + timeExecute);
    }
}
