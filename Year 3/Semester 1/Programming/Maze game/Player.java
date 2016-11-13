package labs.univ.com;

import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;

public class Player {
    public Maze maze;
    public int x = 1;
    public int y = 1;
    public float deltaX = 0;
    public float deltaY = 0;
    public float sizeParam;
    public float prevXmove = 0;
    public float prevYmove = 0;
    public boolean inFinish = false;

    public Player(Maze maze, float sizeParam) {
        this.maze = maze;
        this.sizeParam = sizeParam;
        maze.mapMatrix[y][x] = CellType.PLAYER;
    }

    public void draw(Canvas canvas) {
        Paint redPaint = new Paint();
        redPaint.setColor(Color.argb(255, 255, 0, 0));
        float playerCenterX = x*sizeParam + sizeParam/2 + deltaX;
        float playerCenterY = y*sizeParam + sizeParam/2 + deltaY;
        float playerRadius = sizeParam/3;
        canvas.drawCircle(playerCenterX, playerCenterY, playerRadius, redPaint);
    }

    public void moveTo(float toX, float toY) {
        maze.mapMatrix[y][x] = CellType.VISITED;
        deltaX += (toX - prevXmove);
        deltaY += (toY - prevYmove);
        prevXmove = toX;
        prevYmove = toY;
        int startXmaze = x;
        int startYmaze = y;

        if(maze.mapMatrix[y+1][x] == CellType.WALL && deltaY > 0) {
            deltaY = 0;
        }
        if(maze.mapMatrix[y][x+1] == CellType.WALL && deltaX > 0) {
            deltaX = 0;
        }
        if(maze.mapMatrix[y-1][x] == CellType.WALL && deltaY < 0) {
            deltaY = 0;
        }
        if(maze.mapMatrix[y][x-1] == CellType.WALL && deltaX < 0) {
            deltaX = 0;
        }
        if(maze.mapMatrix[y+1][x-1] == CellType.WALL && deltaY > sizeParam/3 && deltaX < -sizeParam/3) {
            if(deltaY > sizeParam/3) {
                deltaY = 0;
            }
            if(deltaX < -sizeParam/3) {
                deltaX = 0;
            }
        }
        if(maze.mapMatrix[y-1][x+1] == CellType.WALL && deltaY < -sizeParam/3 && deltaX > sizeParam/3) {
            if(deltaY < -sizeParam/3) {
                deltaY = 0;
            }
            if(deltaX > sizeParam/3) {
                deltaX = 0;
            }
        }
        if(maze.mapMatrix[y+1][x+1] == CellType.WALL && deltaY > sizeParam/3 && deltaX > sizeParam/3) {
            if(deltaY > sizeParam/3) {
                deltaY = 0;
            }
            if(deltaX > sizeParam/3) {
                deltaX = 0;
            }
        }
        if(maze.mapMatrix[y-1][x-1] == CellType.WALL && deltaY < -sizeParam/3 && deltaX < -sizeParam/3) {
            if(deltaY < -sizeParam/3) {
                deltaY = 0;
            }
            if(deltaX < -sizeParam/3) {
                deltaX = 0;
            }
        }

        int endXmaze = 0;
        int endYmaze = 0;
        System.out.println("X: " + deltaX);
        System.out.println("Y: " + deltaY);
        if(Math.abs(deltaY) >= sizeParam) {
            int k = (int)(deltaY / sizeParam);
            //endYmaze = startYmaze + k;
            y += k;
            deltaY -= k*sizeParam;
        }

        if(Math.abs(deltaX) >= sizeParam) {
            int k = (int)(deltaX / sizeParam);
            //endXmaze = startXmaze + k;
            x += k;
            deltaX -= k*sizeParam;
        }
/*
        if(deltaX < 0) {
            for(int i = startXmaze; i > endXmaze; i--) {
                if(maze.mapMatrix[y][i-1] != CellType.WALL)
                    x--;
                else break;
            }
        }

        if(deltaX > 0) {
            for(int i = startXmaze; i < endXmaze; i++) {
                if(maze.mapMatrix[y][i+1] != CellType.WALL)
                    x++;
                else break;
            }
        }

        if(deltaY < 0) {
            for(int i = startYmaze; i > endYmaze; i--) {
                if(maze.mapMatrix[i-1][x] != CellType.WALL)
                    y--;
                else break;
            }
        }

        if(deltaY > 0) {
            for(int i = startYmaze; i < endYmaze; i++) {
                if(maze.mapMatrix[i+1][x] != CellType.WALL)
                    y++;
                else
                    break;
            }
        }

*/

        if(maze.mapMatrix[y][x] == CellType.FINISH) {
            inFinish = true;
        }


        maze.mapMatrix[y][x] = CellType.PLAYER;
    }

    public void startMovement(float x, float y) {
        prevXmove = x;
        prevYmove = y;
    }

    public void finishMovement() {
        prevXmove = 0;
        prevYmove = 0;
    }

}
