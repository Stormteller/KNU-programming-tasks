package com.univ.labs;

import java.util.Arrays;
import java.util.Random;
import java.util.concurrent.locks.ReentrantReadWriteLock;

/**
 * Created by Andrey on 03/26/2017.
 */
public class FieldModel {

    private Cell[][] mainField = null;
    private Cell[][] nextField = null;

    private int	width, height;
    private int[][]	neighbors = new int[][] { {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

    private ReentrantReadWriteLock lock = null;

    public FieldModel(int width, int height, ReentrantReadWriteLock lock) {
        this.lock = lock;
        this.width = width;
        this.height = height;
        mainField = new Cell[height][width];
        nextField = new Cell[height][width];
        for(int i = 0; i < width; i++)
            for(int j = 0; j < width; j++) {
                nextField[i][j] = new Cell();
                mainField[i][j] = new Cell();
            }
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public void clear() {
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                mainField[i][j].value = 0;
    }

    public void setCell(int x, int y, Cell c) {
        mainField[x][y] = c;
    }

    public Cell getCell(int x, int y) {
        return mainField[x][y];
    }

    public void simulate(byte types, int start, int finish) {
        for (byte type = 1; type <= types; type++) {
            for (int x = start; x < finish; x++) {
                for (int y = 0; y < width; y++) {
                    nextField[x][y].lock.writeLock().lock();
                    nextField[x][y].value = simulateCell(mainField[x][y].value, nextField[x][y].value, countNeighbors(x, y, type), type);
                    nextField[x][y].lock.writeLock().unlock();
                }
            }
        }
    }

    public void swapField(){
        Cell[][] t = mainField;
        mainField = nextField;
        nextField = t;
        nextField = new Cell[height][width];
        for(int i = 0; i < width; i++)
            for(int j = 0; j < width; j++) {
                nextField[i][j] = new Cell();
            }
    }

    public void generate(byte civAmount, float density) {
        Random rand = new Random();
        int cellAmount = (int) (width * height * density / civAmount);
        for (byte i = 1; i <= civAmount; i++) {
            for (int j = 0; j < cellAmount; j++) {
                int randomX = rand.nextInt(width);
                int randomY = rand.nextInt(height);

                if (mainField[randomX][randomY].value != 0) {
                    boolean set = false;
                    for (int ri = randomX; ri < width && !set; ri++) {
                        for (int rj = randomY; rj < height && !set; rj++) {
                            if (mainField[ri][rj].value == 0) {
                                mainField[ri][rj].value = i;
                                set = true;
                            }
                        }
                    }
                    for (int ri = 0; ri < randomX && !set; ri++) {
                        for (int rj = 0; rj < randomY && !set; rj++) {
                            if (mainField[ri][rj].value == 0) {
                                mainField[ri][rj].value = i;
                                set = true;
                            }
                        }
                    }
                }
                else {
                    mainField[randomX][randomY].value = i;
                }
            }
        }
    }

    private byte countNeighbors(int cellX, int cellY, byte type) {
        return (byte)Arrays.stream(neighbors).filter((neighbor) -> {
            int neighborX = cellX + neighbor[0];
            int neighborY = cellY + neighbor[1];
            if (neighborX >= 0 && neighborX < height && neighborY >= 0 && neighborY < width){
                if (mainField[neighborX][neighborY].value == type)
                    return true;
            }
            return false;
        }).count();
    }

    private byte simulateCell(byte cell, byte inNewField, byte neighbors, byte type) {
        if (cell == type && neighbors < 2) return 0;
        if (cell == type && (neighbors == 2 || neighbors == 3)) return type;
        if (cell == type && neighbors > 3) return 0;
        if (cell != type && neighbors == 3) return type;
//        if (cell != type && cell != 0 )
//            if(inNewField != 0) {
//                return inNewField;
//            }
//            else return cell;
        return inNewField;
    }
}
