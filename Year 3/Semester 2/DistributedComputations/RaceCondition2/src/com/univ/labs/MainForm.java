package com.univ.labs;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * Created by Andrey on 02/19/2017.
 */
public class MainForm extends JFrame {
    private JSlider slider;
    private JButton start1Button;
    private JButton stop1Button;
    private JButton start2Button;
    private JButton stop2Button;
    private JPanel panel;
    AtomicInteger semaphore = new AtomicInteger(0);
    Thread thread1;
    Thread thread2;

    public MainForm() {
        super("Lab 1.2");
        setContentPane(panel);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setLocation(new java.awt.Point(400, 200));
        setResizable(false);
        setVisible(true);
        pack();

        start1Button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (semaphore.compareAndSet(1, 1)) {
                    JOptionPane.showMessageDialog(null, "Critical section is busy.");
                    return;
                }
                thread1 = new Thread(new Runnable() {
                    @Override
                    public void run() {
//                synchronized (slider) {
                        semaphore.set(1);
                        while(true) {
                            if (thread1.isInterrupted()) return;
                            slider.setValue(slider.getValue() + 1);
                        }
//                }
                    }
                });
                thread1.setPriority(1);
                thread1.start();
                stop2Button.setEnabled(false);
            }
        });


        stop1Button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(thread1 != null && thread1.isAlive()) {
                    thread1.interrupt();
                    semaphore.compareAndSet(1, 0);
                    stop2Button.setEnabled(true);
                }
            }
        });

        start2Button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (semaphore.compareAndSet(1, 1)) {
                    JOptionPane.showMessageDialog(null, "Critical section is busy.");
                    return;
                }
                thread2 = new Thread(new Runnable() {
                    @Override
                    public void run() {
//                synchronized (slider) {
                        semaphore.compareAndSet(0, 1);
                        while(true) {
                            if (thread2.isInterrupted()) return;
                            slider.setValue(slider.getValue() - 1);
                        }
//                }
                    }
                });
                thread2.setPriority(10);
                thread2.start();
                stop1Button.setEnabled(false);
            }
        });

        stop2Button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(thread2 != null && thread2.isAlive()) {
                    thread2.interrupt();
                    semaphore.compareAndSet(1, 0);
                    stop1Button.setEnabled(true);
                }
            }
        });
    }
}
