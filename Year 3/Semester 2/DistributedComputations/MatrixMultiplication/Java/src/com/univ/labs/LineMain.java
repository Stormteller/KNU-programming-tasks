package com.univ.labs;

import mpi.MPI;

import java.util.Date;
import java.util.Random;

public class LineMain {
    public static void printMatrix(int[] matrix, int width, int height, int thread, String matrixName) {
        StringBuilder res = new StringBuilder();
        for(int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                res.append(matrix[i * height + j]);
                res.append(" ");
            }
            res.append("\n");
        }
        res.append("Thread: " + thread + " _______________ " + matrixName);
        System.out.println(res.toString());
    }

    public static void main(String[] args) {
        MPI.Init(args);
        Random rnd = new Random();
        int procRank = MPI.COMM_WORLD.Rank();
        int procNum = MPI.COMM_WORLD.Size();

        int matSize = 100;

        int[] matrixA = new int[matSize*matSize];
        int[] matrixB = new int[matSize*matSize];
        int[] matrixC = new int[matSize*matSize];

        double startTime = 0;
        Date startDate = null;
        if(procRank == 0) {
            for(int i = 0; i < matSize; i++) {
                for(int j = 0; j < matSize; j++) {
                    matrixA[i * matSize + j] = rnd.nextInt(5);
                    matrixB[i * matSize + j] = rnd.nextInt(5);
                    matrixC[i * matSize + j] = 0;
                }
            }
//            printMatrix(matrixA, matSize, matSize, procRank, "A start");

//            printMatrix(matrixB, matSize, matSize, procRank, "B start");
            startDate = new Date();
//            startTime = MPI.Wtime() / 10000;
//            System.out.println(startTime);
        }

        int lineHeight = matSize / procNum;
        int[] bufferA = new int[lineHeight * matSize];
        int[] bufferB = new int[lineHeight * matSize];
        int[] bufferC = new int[lineHeight * matSize];

        MPI.COMM_WORLD.Scatter(matrixA, 0,lineHeight*matSize, MPI.INT, bufferA, 0, lineHeight*matSize, MPI.INT, 0);
        MPI.COMM_WORLD.Scatter(matrixB, 0,lineHeight*matSize, MPI.INT, bufferB, 0, lineHeight*matSize, MPI.INT, 0);

        int nextProc = procRank + 1;
        if(nextProc == procNum) nextProc = 0;
        int prevProc = procRank - 1;
        if(prevProc < 0) prevProc = procNum - 1;

        int prevDataNum = procRank;
        for(int p = 0; p < procNum; p++) {
            for (int i = 0; i < lineHeight; i++) {
                for (int j = 0; j < matSize; j++) {
                    for (int k = 0; k < lineHeight; k++) {
                        bufferC[i * matSize + j] += bufferA[prevDataNum * lineHeight + i * matSize + k] * bufferB[k * matSize + j];
                    }
//                    bufferC[i * matSize + j] += bufferA[i * matSize + j] * bufferB[i * matSize + j];\
                }
            }
            prevDataNum -= 1;
            if (prevDataNum < 0) prevDataNum = procNum - 1;
//            printMatrix(bufferA, matSize, lineHeight, procRank, "A buffer");
//            printMatrix(bufferB, matSize, lineHeight, procRank, "B buffer");
            MPI.COMM_WORLD.Sendrecv_replace(bufferB,0, lineHeight * matSize, MPI.INT, nextProc, 0, prevProc, 0);
        }
        MPI.COMM_WORLD.Gather(bufferC, 0, lineHeight * matSize, MPI.INT, matrixC, 0, lineHeight * matSize, MPI.INT, 0);

        if(procRank == 0) {
//            double resTime = MPI.Wtime() - startTime;
//            System.out.println(MPI.Wtime() / 10000 - startTime);
            System.out.println((new Date()).getTime() - startDate.getTime());
//            printMatrix(matrixC, matSize, matSize, procRank, "Res");
        }

        MPI.Finalize();
    }
}
