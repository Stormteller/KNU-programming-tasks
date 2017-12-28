package com.univ.labs;

import javax.swing.*;
public class ConcurrentValueTester {
    private JSlider slider;
    private int decPrior = 1;
    private int incPrior = 1;
    private Thread threadDecreaser;
    private Thread threadIncreaser;

    public ConcurrentValueTester(JSlider s) {
        slider = s;
    }

    public void incDecPrior() {
        if(decPrior < 10) {
            decPrior++;
            System.out.println(decPrior);
            threadDecreaser.setPriority(decPrior);
        }
    }
    public void decDecPrior() {
        if(decPrior > 1) {
            decPrior--;
            System.out.println(decPrior);
            threadDecreaser.setPriority(decPrior);
        }

    }
    public void incIncPrior() {
        if(incPrior < 10) {
            incPrior++;
            System.out.println(incPrior);
            threadIncreaser.setPriority(incPrior);
        }
    }
    public void decIncPrior() {
        if(incPrior > 1) {
            incPrior--;
            System.out.println(incPrior);
            threadIncreaser.setPriority(incPrior);
        }
    }

    public void startTesting() {
        threadIncreaser = new Thread(new Runnable() {
            @Override
            public void run() {
                while(true) {
                    synchronized (slider) {
                        slider.setValue(slider.getValue() + 1);
                    }

                }
            }
        });

        threadDecreaser = new Thread(new Runnable() {
            @Override
            public void run() {
                while(true) {
                    synchronized (slider) {
                        slider.setValue(slider.getValue() - 1);
                    }
                }
            }
        });

        threadIncreaser.setPriority(1);
        threadDecreaser.setPriority(1);
        threadDecreaser.start();
        threadIncreaser.start();
    }
}
