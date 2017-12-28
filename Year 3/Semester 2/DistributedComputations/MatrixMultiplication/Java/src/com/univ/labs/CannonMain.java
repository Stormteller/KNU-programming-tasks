package com.univ.labs;

import mpi.Cartcomm;
import mpi.MPI;

import java.util.Arrays;
import java.util.Random;

public class CannonMain {
    private static int[] gridCoords = new int[2];
    private static Cartcomm ColComm;
    private static Cartcomm RowComm;

    private static void matrixScatter(int[] matrix, int[] matrixBlock, int matSize, int blockSize) {
        int[] matrixRow = new int[blockSize * matSize];
        if (gridCoords[1] == 0) {
            ColComm.Scatter(matrix, 0, blockSize * matSize, MPI.INT, matrixRow, 0,blockSize * matSize, MPI.INT, 0);
        }
        for (int i = 0; i < blockSize; i++) {
            int[] subRow = Arrays.copyOfRange(matrixRow, i * matSize,  matrixRow.length);
            int[] subRowRes = new int[blockSize];

            RowComm.Scatter(subRow, 0, blockSize, MPI.INT,
                    subRowRes, 0, blockSize, MPI.INT, 0);
            for(int j = 0; j < blockSize; j++) {
                matrixBlock[i * blockSize + j] = subRowRes[j];
            }
        }
    }

    public static void printMatrix(int[] matrix, int width, int height, int thread, String matrixName) {
        StringBuilder res = new StringBuilder();
        for(int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                res.append(matrix[i * height + j]);
                res.append(" ");
            }
            res.append("\n ");
        }
        res.append("Thread: " + thread + " _______________ " + matrixName);
        System.out.println(res.toString());
    }

    public static void main(String[] args) {
        MPI.Init(args);
        Random rnd = new Random();
        int procRank = MPI.COMM_WORLD.Rank();
        int procNum = MPI.COMM_WORLD.Size();
        int gridSize = (int)Math.sqrt(procNum);
        Cartcomm gridComm;

        int matSize = 1000;
        int blockSize = matSize / gridSize;

        int[] matrixA = new int[matSize*matSize];
        int[] matrixB = new int[matSize*matSize];
        int[] matrixC = new int[matSize*matSize];
        int[] ABlock = new int[blockSize*blockSize];
        int[] BBlock  = new int[blockSize*blockSize];
        int[] CBlock  = new int[blockSize*blockSize];

        double startTime = 0;
        if(procRank == 0) {
            for(int i = 0; i < matSize; i++) {
                for(int j = 0; j < matSize; j++) {
                    matrixA[i * matSize + j] = 1;//rnd.nextInt(5);
                    matrixB[i * matSize + j] = 2;//rnd.nextInt(5);
                    matrixC[i * matSize + j] = 0;
                }
            }
//            printMatrix(matrixA, matSize, matSize, procRank, "A start");

//            printMatrix(matrixB, matSize, matSize, procRank, "B start");
            startTime = MPI.Wtime();
            System.out.println(startTime);
        }

        int[] dimSize = new int[2];  // Number of processes in each dimension of the grid
        boolean[] periodic = new boolean[2]; // =1, if the grid dimension should be periodic
        boolean[] subdims = new boolean[2];  // =1, if the grid dimension should be fixed

        dimSize[0] = gridSize;
        dimSize[1] = gridSize;
        periodic[0] = false;
        periodic[1] = false;

        // Creation of the Cartesian communicator
        gridComm = MPI.COMM_WORLD.Create_cart(dimSize, periodic, true);

        // Determination of the cartesian coordinates for every process
        gridCoords = gridComm.Coords(procRank);

        // Creating communicators for rows
        subdims[0] = false;  // Dimensionality fixing
        subdims[1] = true;  // The presence of the given dimension in the subgrid
        RowComm = gridComm.Sub(subdims);

        // Creating communicators for columns
        subdims[0] = true;
        subdims[1] = false;
        ColComm = gridComm.Sub(subdims);


        matrixScatter(matrixA, ABlock, matSize, blockSize);
        matrixScatter(matrixB, BBlock, matSize, blockSize);

        if (gridCoords[0] != 0){
            int nextProc = gridCoords[1] - gridCoords[0];
            if (nextProc < 0) nextProc += gridSize;
            RowComm.Sendrecv_replace(ABlock, 0, blockSize * blockSize, MPI.INT,
                                     nextProc, 0, MPI.ANY_SOURCE, 0);
        }

        if (gridCoords[1] != 0){
            int nextProc = gridCoords[0] - gridCoords[1];
            if (nextProc < 0) nextProc += gridSize;
            ColComm.Sendrecv_replace(BBlock, 0,blockSize * blockSize, MPI.INT,
                                     nextProc, 1, MPI.ANY_SOURCE, 1);
        }

        MPI.COMM_WORLD.Barrier();
        for (int i = 0; i < blockSize; i++) {
            for (int j = 0; j < blockSize; j++)
                for (int k = 0; k < blockSize; k++)
                    CBlock[i*blockSize + j] += ABlock[i*blockSize + k] * BBlock[k * blockSize + j];
        }


        for (int iter = 0; iter < gridSize - 1; iter ++) {
            int nextProc = gridCoords[1] - 1;
            if (nextProc < 0)
                nextProc += gridSize;
            RowComm.Sendrecv_replace(ABlock, 0, blockSize, MPI.INT, nextProc, 0, MPI.ANY_SOURCE, 0);

            nextProc = gridCoords[0] - 1;
            if (nextProc < 0)
                nextProc += gridSize;
            ColComm.Sendrecv_replace(BBlock, 0, blockSize, MPI.INT, nextProc, 1, MPI.ANY_SOURCE, 1);

            for(int i=0; i < blockSize; i++) {
                for(int j=0; j < blockSize; j++)
                    for(int k=0; k < blockSize; k++)
                        CBlock[i*blockSize + j] += ABlock[i * blockSize + k] * BBlock[k * blockSize + j];
            }
//            System.out.println(Arrays.toString(CBlock));
        }

//        System.out.println(Arrays.toString(CBlock));
        //Result
        int[] resultRow = new int[matSize * blockSize];
        for (int i = 0; i < blockSize; i++) {
            int[] subRow = Arrays.copyOfRange(CBlock, i * blockSize,  CBlock.length);
            int[] subRowRes = new int[gridSize * blockSize];
            RowComm.Gather(subRow, 0, blockSize, MPI.INT,
                    subRowRes, 0, blockSize, MPI.INT, 0);
            System.arraycopy(subRowRes, 0, resultRow, i * matSize, gridSize * blockSize);
        }

        if (gridCoords[1] == 0) {
            ColComm.Gather(resultRow, 0, blockSize * matSize, MPI.INT,
                    matrixC, 0, blockSize * matSize, MPI.INT, 0);
        }

        if(procRank == 0) {
            System.out.println(MPI.Wtime() - startTime);
//            printMatrix(matrixC, matSize, matSize, procRank, "Res");
        }

        MPI.Finalize();
    }
}
