package com.univ.labs;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by Andrey on 03/26/2017.
 */
public class MainFrame extends JFrame {
    private JPanel fieldPanel = null;
    private JButton	startBtn = null;
    private JButton	stopBtn	= null;
    private MainFrame self = this;
    private JSlider civSlider = null;

    public MainFrame() {
        super("LIFE IS LIFE!");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);

        JToolBar toolBar = new JToolBar();
        toolBar.setFloatable(false);
        add(toolBar, BorderLayout.SOUTH);

        fieldPanel = new FieldPanel(52, 52, 11);
        add(fieldPanel);
        startBtn = new JButton("Start");
        toolBar.add(startBtn);
        stopBtn = new JButton("Stop");
        stopBtn.setEnabled(true);
        toolBar.add(stopBtn);


        civSlider = new JSlider(1, 4);
        civSlider.setValue(1);
        toolBar.add(civSlider);

        startBtn.addActionListener(e -> {
            ((FieldPanel)fieldPanel).startSimulation((byte)civSlider.getValue(), 0.2f);
//            fieldPanel.repaint();
            startBtn.setEnabled(false);
            stopBtn.setEnabled(true);
        });

        stopBtn.addActionListener(e -> {
            ((FieldPanel)fieldPanel).stopSimulation(startBtn);
            stopBtn.setEnabled(false);
        });
        pack();
        setVisible(true);
    }
}
