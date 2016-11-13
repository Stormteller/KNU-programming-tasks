package labs.univ.com;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;


public class GamePanel extends SurfaceView implements SurfaceHolder.Callback
{
    private MainThread thread;
    private Maze maze;
    private Player player;

    public GamePanel(Context context)
    {
        super(context);


        //add the callback to the surfaceholder to intercept events
        getHolder().addCallback(this);

        thread = new MainThread(getHolder(), this);

        //make gamePanel focusable so it can handle events
        setFocusable(true);
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height){}

    @Override
    public void surfaceDestroyed(SurfaceHolder holder){
        boolean retry = true;
        while(retry)
        {
            try{thread.setRunning(false);
                thread.join();

            }catch(InterruptedException e){e.printStackTrace();}
            retry = false;
        }

    }

    @Override
    public void surfaceCreated(SurfaceHolder holder){

        //we can safely start the game loop
        thread.setRunning(true);
        thread.start();

    }
    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if(event.getAction() == MotionEvent.ACTION_DOWN) {
            player.startMovement(event.getX(), event.getY());
            return true;
        }

        if(event.getAction() == MotionEvent.ACTION_MOVE) {
            player.moveTo(event.getX(), event.getY());
            return true;
        }

        if(event.getAction() == MotionEvent.ACTION_UP) {
            player.finishMovement();
            return true;
        }

        return super.onTouchEvent(event);
    }

    public void update() {
        if(maze == null && getWidth() != 0) {
            maze = new Maze(17, 29, getWidth(), getHeight());
            player = new Player(maze, maze.wallWidth);
        } else if(player.inFinish) {
            maze = new Maze(maze.width + 2, maze.height +2, getWidth(), getHeight());
            player = new Player(maze, maze.wallWidth);
        }


    }

    @Override
    public void draw(Canvas canvas)
    {

        canvas.drawColor(Color.argb(255, 0, 0, 0));
        maze.draw(canvas);
        player.draw(canvas);
    }
}
