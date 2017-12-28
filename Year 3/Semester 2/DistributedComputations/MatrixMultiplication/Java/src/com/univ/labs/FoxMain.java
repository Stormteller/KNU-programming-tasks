package com.univ.labs;

import mpi.Cartcomm;
import mpi.Intracomm;
import mpi.MPI;
import mpi.Status;

import java.util.Arrays;
import java.util.Date;
import java.util.Random;

public class FoxMain {
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
                res.append("  ");
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

        int matSize = 4000;
        int blockSize = matSize / gridSize;

        int[] matrixA = new int[matSize*matSize];
        int[] matrixB = new int[matSize*matSize];
        int[] matrixC = new int[matSize*matSize];
        int[] ABlock = new int[blockSize*blockSize];
        int[] BBlock  = new int[blockSize*blockSize];
        int[] CBlock  = new int[blockSize*blockSize];
        int[] tempABlock = new int[blockSize*blockSize];

        double startTime = 0;
        Date startDate;
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
            startTime = MPI.Wtime();
            startDate = new Date();
//            System.out.println(startTime);
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


        matrixScatter(matrixA, tempABlock, matSize, blockSize);
        matrixScatter(matrixB, BBlock, matSize, blockSize);


        for (int iter = 0; iter < gridSize; iter ++) {
            // Sending blocks of matrix A to the process grid rows
            int pivot = (gridCoords[0] + iter) % gridSize;

            // Copying the transmitted block in a separate memory buffer
            if (gridCoords[1] == pivot) {
                for (int i=0; i < blockSize * blockSize; i++)
                    ABlock[i] = tempABlock[i];
            }

            // Block broadcasting
            RowComm.Bcast(ABlock, 0, blockSize*blockSize, MPI.INT, pivot);

            for(int i=0; i < blockSize; i++) {
                for(int j=0; j < blockSize; j++)
                    for(int k=0; k < blockSize; k++)
                        CBlock[i*blockSize + j] += ABlock[i * blockSize + k] * BBlock[k * blockSize + j];
            }

            // Cyclic shift of blocks of matrix B in process grid columns
            int nextProc = gridCoords[0] + 1;
            if (gridCoords[0] == gridSize - 1) nextProc = 0;
            int prevProc = gridCoords[0] - 1;
            if (gridCoords[0] == 0) prevProc = gridSize - 1;

//            if(MPI.COMM_WORLD.Rank() == 0) {
//                System.out.println(Arrays.toString(CBlock));
//                System.out.println();
//            }

            ColComm.Sendrecv_replace(BBlock, 0, blockSize * blockSize, MPI.INT, nextProc, 0, prevProc, 0);
        }

        System.out.println(Arrays.toString(CBlock));
        //Result
        int[] resultRow = new int[matSize * blockSize];
        for (int i = 0; i < blockSize; i++) {
            int[] subRow = Arrays.copyOfRange(CBlock, i * blockSize,  CBlock.length);
            int[] subRowRes = new int[gridSize * blockSize];

            RowComm.Gather(subRow, 0, blockSize, MPI.INT,
                    subRowRes, 0, blockSize, MPI.INT, 0);
            for(int j = 0; j < gridSize * blockSize; j++) {
                resultRow[i * matSize + j] = subRowRes[j];
            }
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
