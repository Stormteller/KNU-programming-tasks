package com.univ.labs;

import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

/**
 * Created by Andrey on 04/01/2017.
 */
public class Hunter extends Thread {
    private JLabel hunterLabel = null;
    private GamePanel panel = null;
    private int x = 0;
    private int y = 0;
    private int labelWidth = 137;
    private int labelHeight = 150;
    private ImageIcon dukeRight = new ImageIcon("./src/resources/dukeLR.png");
    private ImageIcon dukeLeft = new ImageIcon("./src/resources/dukeRL.png");
    private int side = 1;
    private int dx = 20;
    private int panelWidth = 0;
    private int panelHeight = 0;
    private volatile int countBullet = 0;
    private Hunter Iam = this;

    private boolean keyleft = false;
    private boolean keyright = false;

    Hunter(MainFrame main, GamePanel panel) {
        this.panelWidth = panel.width;
        this.panelHeight = panel.height;
        this.panel = panel;
        x = panel.width / 2;
        y = panel.height - labelHeight;
        hunterLabel = new JLabel(new ImageIcon("./src/resources/dukeRL.png"));
        hunterLabel.setSize(new Dimension(labelWidth, labelHeight));
        hunterLabel.setLocation(x, y);
        hunterLabel.setVisible(true);
        panel.add(hunterLabel);
        HunterKeyListener keyListener = new HunterKeyListener();
        main.addKeyListener(keyListener);
    }

    synchronized public void addBullet(int num){
        countBullet += num;
    }

    public class HunterKeyListener implements KeyListener {
        @Override
        public void keyTyped(KeyEvent e) {}

        @Override
        public void keyPressed(KeyEvent e) {
            if (panel != null){
                switch(e.getKeyCode()) {
                    case KeyEvent.VK_SPACE:
                        if(countBullet < 10) {
                            Bullet bullet;
                            if (side == 1) bullet = new Bullet(panel, Iam, x, y + 50);
                            else bullet = new Bullet(panel, Iam, x + labelWidth, y + 50);
                            bullet.start();
                        }
                        break;
                    case KeyEvent.VK_LEFT:
                        keyleft = true;
                        if (x > 0){
                            if (side != 1){
                                hunterLabel.setIcon(dukeLeft);
                                side = 1;
                            }
                        }
                        break;
                    case KeyEvent.VK_RIGHT:
                        keyright = true;
                        if (x < panelWidth - labelWidth){
                            if (side != 2){
                                hunterLabel.setIcon(dukeRight);
                                side = 2;
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
        }

        @Override
        public void keyReleased(KeyEvent e) {
            if (e.getKeyCode() == KeyEvent.VK_RIGHT)
                keyright = false;
            else if (e.getKeyCode() == KeyEvent.VK_LEFT)
                keyleft = false;
        }
    }


    @Override
    public void run() {
        while (!isInterrupted()) {
            if (keyleft && x - dx >= 0)
                x -= dx;
            else if (keyright && x + dx + labelWidth <= panelWidth)
                x += dx;

            hunterLabel.setLocation(x, y);
            try {
                sleep(20);
            } catch (InterruptedException e) { break; }
        }
        panel.remove(hunterLabel);
    }
}
