package labs.univ.com;


import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Point;
import android.util.Pair;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Random;

enum CellType {WALL, CELL, VISITED, PLAYER, FINISH}

public class Maze {
    public CellType[][] mapMatrix;
    public int height;
    public int width;
    public Point startPoint;
    public Point finishPoint;
    public int screenWidth;
    public int screenHeight;
    public float wallWidth;
    public boolean setFinish = false;

    public Maze(int width, int height, int scWidth, int scHeight) {
        mapMatrix = new CellType[height][width];
        this.height = height;
        this.width = width;
        this.screenWidth = scWidth;
        this.screenHeight = scHeight;
        this.wallWidth = screenWidth/width;

        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++) {
                if((i % 2 != 0 && j % 2 != 0) && (i < height - 1 && j < width - 1)) {
                    mapMatrix[i][j] = CellType.CELL;
                } else {
                    mapMatrix[i][j] = CellType.WALL;
                }
            }
        }

        startPoint = new Point(1, 1);
        mapMatrix[startPoint.y][startPoint.x] = CellType.VISITED;
        Point current = new Point(startPoint);
        Point neighbour;
        Random random = new Random();
        ArrayDeque<Point> stack = new ArrayDeque<>();
        do {
            ArrayList<Point> neighbours = getNeighbours(current, 2);
            if(neighbours.size() != 0) {
                int randNeighb = random.nextInt(neighbours.size());
                neighbour = new Point(neighbours.get(randNeighb));
                stack.push(neighbour);
                removeWall(current, neighbour);
                current = new Point(neighbour);
                mapMatrix[current.y][current.x] = CellType.VISITED;
            } else if(stack.size() > 0) {
                if(!setFinish && current.y > height/2 && current.x > width/2) {
                    mapMatrix[current.y][current.x] = CellType.FINISH;
                    setFinish = true;
                }
                current = stack.pop();
            }
        }while (unvisitedCount() > 0);
    }

    public void draw(Canvas canvas) {
        Paint blackPaint = new Paint();
        Paint whitePaint = new Paint();
        Paint greenPaint = new Paint();
        blackPaint.setColor(Color.argb(255, 0, 0, 0));
        whitePaint.setColor(Color.argb(255, 255, 255, 255));
        greenPaint.setColor(Color.argb(255, 0, 255, 0));
        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++) {
                if(mapMatrix[i][j] == CellType.WALL)
                    canvas.drawRect(j*wallWidth, i*wallWidth, (j+1)*wallWidth, (i+1)*wallWidth, blackPaint);
                else if(mapMatrix[i][j] == CellType.VISITED || mapMatrix[i][j] == CellType.PLAYER)
                    canvas.drawRect(j*wallWidth, i*wallWidth, (j+1)*wallWidth, (i+1)*wallWidth, whitePaint);
                else if(mapMatrix[i][j] == CellType.FINISH) {
                   canvas.drawRect(j*wallWidth, i*wallWidth, (j+1)*wallWidth, (i+1)*wallWidth, greenPaint);
                }
            }
        }
    }

    private int unvisitedCount() {
        int count = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (mapMatrix[i][j] == CellType.CELL) count++;
            }
        }
        return count;
    }

    private void removeWall(Point first, Point second) {
        int diffX = second.x - first.x;
        int diffY = second.y - first.y;
        int addX, addY;
        Point target = new Point();

        addX = (diffX != 0) ? (diffX / Math.abs(diffX)) : 0;
        addY = (diffY != 0) ? (diffY / Math.abs(diffY)) : 0;

        target.x = first.x + addX;
        target.y = first.y + addY;

        mapMatrix[target.y][target.x] = CellType.VISITED;
    }

    private ArrayList<Point> getNeighbours(Point current, int distance) {
        Point up = new Point(current.x, current.y - distance);
        Point right = new Point(current.x + distance, current.y);
        Point down = new Point(current.x, current.y + distance);
        Point left = new Point(current.x - distance, current.y);
        Point[] points = {up, right, down, left};
        ArrayList<Point> neighbours = new ArrayList<>();
        for(int i = 0; i < 4; i++) {
            if(points[i].x > 0 && points[i].x < width && points[i].y > 0 && points[i].y < height) {
                CellType currType = mapMatrix[points[i].y][points[i].x];
                Point curr = points[i];
                if(currType != CellType.WALL && currType != CellType.VISITED && currType != CellType.FINISH){
                   neighbours.add(curr);
                }
            }
        }
        return neighbours;
    }
}
