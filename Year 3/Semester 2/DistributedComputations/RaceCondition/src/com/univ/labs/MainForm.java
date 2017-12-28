package com.univ.labs;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MainForm extends JFrame {
    private JPanel mainPanel;
    private JButton increasePriorityButton;
    private JButton decreasePriorityButton;
    private JButton increasePriorityButton1;
    private JButton decreasePriorityButton1;
    private JSlider slider;

    public MainForm() {
        super("Lab 1");
        setContentPane(mainPanel);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setLocation(new java.awt.Point(400, 200));
        setResizable(false);
        setVisible(true);
        pack();

        ConcurrentValueTester cvt = new ConcurrentValueTester(slider);
        cvt.startTesting();
        increasePriorityButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                cvt.incDecPrior();
            }
        });


        decreasePriorityButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                cvt.decDecPrior();
            }
        });

        increasePriorityButton1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                cvt.incIncPrior();
            }
        });

        decreasePriorityButton1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                cvt.decIncPrior();
            }
        });
    }
}
