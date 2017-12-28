package com.univ.labs;

import javax.swing.*;
import java.awt.*;

/**
 * Created by Andrey on 04/01/2017.
 */
public class MainFrame extends JFrame {
    private GamePanel panel = null;

    public MainFrame(String title) {
        super(title);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);
        setLayout(null);
        this.setSize(new Dimension(1000,620));

        java.awt.Dimension dim = getToolkit().getScreenSize();
        this.setLocation(dim.width/2 - 500,dim.height/2 - 350);
        panel = new GamePanel(this, 1000, 600);
        add(panel);
        setVisible(true);
    }
}
