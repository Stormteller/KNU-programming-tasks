package com.univ.labs;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.concurrent.ConcurrentLinkedQueue;

/**
 * Created by Andrey on 04/01/2017.
 */
public class GamePanel extends JPanel {
    int width = 1000;
    int height = 600;
    private GamePanel panel = this;
    private ImageIcon background = new ImageIcon("./src/resources/cyb.jpg");
    private int maxDucks = 15;
    ConcurrentLinkedQueue<Duck> ducks = new ConcurrentLinkedQueue<>();
    private Hunter hunter = null;
    private MainFrame main = null;

    public GamePanel(MainFrame main, int width, int height) {
        setBackground(Color.WHITE);
        this.main = main;

        this.width = width;
        this.height = height;

        setLayout(null);
        setSize(width, height);

        GameMouseAdapter mouseAdapter = new GameMouseAdapter();
        addMouseListener(mouseAdapter );

        Game game = new Game();
        game.start();
    }

    class Game extends Thread{
        @Override
        public void run() {
            if (hunter == null){
                hunter = new Hunter(main,panel);
                hunter.start();
            }
            while (!isInterrupted()){
                if (ducks.size() < maxDucks){
                    Duck duck = new Duck(width,height,panel);
                    ducks.add(duck);
                    duck.start();
                }
                try {
                    sleep(200);
                } catch (InterruptedException ignored) {}
            }
        }
    }

    class GameMouseAdapter extends MouseAdapter {
        @Override
        public void mouseReleased(MouseEvent e) {
            for (Duck duck: ducks){
                if (e.getX() >= duck.x && e.getX() <= duck.x + duck.labelWidth &&
                    e.getY() >= duck.y && e.getY() <= duck.y + duck.labelHeight) duck.interrupt();
            }
        }
    }


    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.drawImage(background.getImage(),0,0,width, height, null);
    }

    @Override
    public Dimension getPreferredSize() {
        return new Dimension(width, height);
    }
    @Override
    public Dimension getMinimumSize() {
        return new Dimension(width, height);
    }
    @Override
    public Dimension getMaximumSize() {
        return new Dimension(width, height);
    }
}
