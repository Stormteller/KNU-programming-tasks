package com.univ.labs;

import javax.swing.*;
import java.awt.*;
import java.util.Random;

/**
 * Created by Andrey on 04/01/2017.
 */
public class Duck extends Thread {
    int x = 0;
    int y = 0;
    private int speedX = 0;
    private int speedY = 0;
    private int skyWidth = 0;
    private int skyHeight = 0;
    int labelWidth = 70;
    int labelHeight = 70;
    private Random random = new Random();
    private JLabel duck = null;
    private GamePanel panel = null;
    private ImageIcon duckRight = new ImageIcon("./src/resources/1cRL.png");
    private ImageIcon duckLeft = new ImageIcon("./src/resources/1cLR.png");

    Duck(int width, int height, GamePanel panel){
        super();
        this.skyWidth = width;
        this.skyHeight = height - 250;
        this.panel = panel;

        if (random.nextInt() % 2 == 0){
            duck = new JLabel(duckLeft);
            duck.setSize(new Dimension(labelWidth, labelHeight));
            int type = random.nextInt(3);
            if (type == 0){
                x = -labelWidth;
                y = Math.abs(random.nextInt()) % skyHeight;
            } else if (type == 1) {
                y = -labelHeight;
                x = Math.abs(random.nextInt()) % skyWidth;
            } else {
                y = skyHeight - labelHeight;
                x = Math.abs(random.nextInt()) % skyWidth;
            }
            speedX = Math.abs(random.nextInt(5)) + 1;
        } else {
            duck = new JLabel(duckRight);
            duck.setSize(new Dimension(labelWidth,labelHeight));
            int type = random.nextInt(3);
            if (type == 0){
                x = skyWidth + labelWidth;
                y = Math.abs(random.nextInt()) % skyHeight;
            } else if (type == 1){
                y = -labelHeight;
                x = Math.abs(random.nextInt()) % skyWidth;
            } else {
                y = skyHeight - labelHeight;
                x = Math.abs(random.nextInt()) % skyWidth;
            }
            speedX = - Math.abs(random.nextInt(5)) - 1;
        }
        if (y > skyHeight/2) speedY = - Math.abs(random.nextInt(4)) - 1;
        else speedY = Math.abs(random.nextInt(4)) + 1;
    }

    @Override
    public void run() {
        panel.add(duck);
        boolean flag = true;
        while (!isInterrupted() && flag){
            int nextX = x + speedX;
            int nextY = y + speedY;
            if (speedX > 0 && nextX > skyWidth || speedX < 0 && nextX < -labelWidth ||
                speedY > 0 && nextY > skyHeight || speedY < 0 && nextY < -labelHeight)
                flag = false;
            x = nextX; y = nextY;
            duck.setLocation(x,y);
            try {
                sleep(Math.abs(random.nextInt(5)) + 20);
            } catch (InterruptedException e) { interrupt(); }
        }
        panel.remove(duck);
        panel.repaint();
        panel.ducks.remove(this);
    }
}
