package com.univ.labs;

import mpi.MPI;

import java.util.Random;

/**
 * Created by Andrey on 04/10/2017.
 */
public class OneThreadMain {
    public static void printMatrix(int[] matrix, int width, int height, int thread, String matrixName) {
        StringBuilder res = new StringBuilder();
        for(int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                res.append(matrix[i * height + j]);
                res.append("  ");
            }
            res.append("\n  ");
        }
        res.append("Thread: " + thread + " _______________ " + matrixName);
        System.out.println(res.toString());
    }
    public static void main(String[] args) {
        MPI.Init(args);
        Random rnd = new Random();
        int procRank = MPI.COMM_WORLD.Rank();

        int matSize = 2;

        int[] matrixA = new int[matSize * matSize];
        int[] matrixB = new int[matSize * matSize];
        int[] matrixC = new int[matSize * matSize];

        double startTime = 0;
        if (procRank == 0) {
            for (int i = 0; i < matSize; i++) {
                for (int j = 0; j < matSize; j++) {
                    matrixA[i * matSize + j] = 1;//rnd.nextInt(10);
                    matrixB[i * matSize + j] = 2;//rnd.nextInt(10);
                    matrixC[i * matSize + j] = 0;
                }
            }
//            printMatrix(matrixA, matSize, matSize, procRank, "A start");

//            printMatrix(matrixB, matSize, matSize, procRank, "B start");

            startTime = MPI.Wtime();
            System.out.println(startTime);
        }

        for (int i = 0; i < matSize; i++) {
            for (int j = 0; j < matSize; j++)
                for (int k = 0; k < matSize; k++)
                    matrixC[i * matSize + j] += matrixA[i * matSize + k] * matrixB[k * matSize + j];

        }
        if (procRank == 0) {
//            double resTime = MPI.Wtime() - startTime;
            System.out.println(MPI.Wtime() - startTime);
            printMatrix(matrixC, matSize, matSize, procRank, "Res");
        }
        MPI.Finalize();
    }
}
