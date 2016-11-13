package com.univ.labs;

//import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.*;


class SocketThread implements Callable<Double> {
    private Socket socket;

    public SocketThread(Socket clientSocket) {
        socket = clientSocket;
    }

    @Override
    public Double call() {
        DataInputStream socketInput = null;
        try {
            socketInput = new DataInputStream(socket.getInputStream());
            Double res = socketInput.readDouble();
            return res;
        } catch (IOException e) {
            System.out.println(e);
        }
        return null;
    }
}

class ListenerTask implements Callable<ArrayList<Future<Double>>> {
    private ServerSocket serverSocket;
    private ExecutorService pool;
    private ArrayList<Future<Double>> tasks;

    public ListenerTask(int port) {
        pool = Executors.newFixedThreadPool(2);
        tasks = new ArrayList<>();
        try {
            serverSocket = new ServerSocket(port);
        } catch (IOException e) {
            System.out.println(e);
        }

    }

    @Override
    public ArrayList<Future<Double>> call() {
        try {
            tasks.add(pool.submit(new SocketThread(serverSocket.accept())));
            tasks.add(pool.submit(new SocketThread(serverSocket.accept())));
            serverSocket.close();
            return tasks;
        } catch (IOException e) {
            pool.shutdownNow();
            System.out.println(e);
        }
        return null;
    }
}


public class Main {

    private static Process procF;
    private static Process procG;

    private static Double resF;
    private static Double resG;

    private static boolean inMenu = false;
    private static int userAction = -1;

    private static Timer menuTimer = null;
    private static TimerTask menuTask = null;

    private static boolean stopCalc = false;

    static class MenuTask extends TimerTask {
        @Override
        public void run() {
            inMenu = true;
        }
    }

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        //Get x
        System.out.println("Input X:");
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        Double x = 0.0;
        try{
            x = Double.parseDouble(br.readLine());
        }catch(NumberFormatException nfe){
            System.err.println("Invalid Format!");
            x = 0.0;
        } catch (IOException e) {
            e.printStackTrace();
        }

        //Pool with Socket thread and user dialog thread
        ExecutorService mainPool = Executors.newFixedThreadPool(1);

        Future<ArrayList<Future<Double>>> socketServerTask = mainPool.submit(new ListenerTask(1111));

        ProcessBuilder pb1 = new ProcessBuilder("java", "Main", Double.toString(x));
        pb1.directory(new File("C:\\Users\\Andrey\\Documents\\IdeaProjects\\longFunc1"));
        ProcessBuilder pb2 = new ProcessBuilder("java", "Main", Double.toString(x));
        pb2.directory(new File("C:\\Users\\Andrey\\Documents\\IdeaProjects\\longFunc2"));
        try {
            procF = pb1.start();
            procG = pb2.start();
        } catch (IOException e) {
            e.printStackTrace();
        }

        ArrayList<Future<Double>> socketTasks = socketServerTask.get();



        menuTimer = new Timer();
        menuTask = new MenuTask();
        menuTimer.schedule(menuTask, 5000);

        double startTime = System.nanoTime();
        double endTime;

        while (true) {
            if(inMenu) {
                endTime = System.nanoTime();
                System.out.println("\nTime: " + (endTime - startTime) / 1000000000 + " seconds");

                System.out.println("\nMenu:\n'ENTER' - continue\n'1' - don't show prompt again\n'0' - terminate\n");
                try {
                    br = new BufferedReader(new InputStreamReader(System.in));
                    String input = br.readLine();
                    switch (input) {
                        case ("1"):
                            inMenu = false;
                            menuTimer.cancel();
                            break;
                        case ("0"):
                            inMenu = false;
                            stopCalc = true;
                            menuTimer.cancel();
                            break;
                        default:
                            inMenu = false;
                            menuTimer.schedule(new MenuTask(), 5000);
                            break;
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            } else {

                if (socketTasks.get(0).isDone()) {
                    resF = socketTasks.get(0).get();
                    if (resF.compareTo(0.0) == 0) {
                        endTime = System.nanoTime();
                        System.out.println("Result: " + 0.0);
                        break;
                    } else if (socketTasks.get(1).isDone()) {
                        resG = socketTasks.get(1).get();
                        endTime = System.nanoTime();
                        System.out.println("Result: " + resF * resG);
                        break;

                    }
                }

                if (socketTasks.get(1).isDone()) {
                    resG = socketTasks.get(1).get();
                    if (resG.compareTo(0.0) == 0) {
                        endTime = System.nanoTime();
                        System.out.println("Result: " + 0.0);
                        break;
                    } else if (socketTasks.get(0).isDone()) {
                        resF = socketTasks.get(0).get();
                        endTime = System.nanoTime();
                        System.out.println("Result: " + resF * resG);
                        break;
                    }
                }
                if(stopCalc) {
                    endTime = System.nanoTime();
                    StringBuilder answer = new StringBuilder("Terminated by user.");
                    if(!socketTasks.get(0).isDone()) {
                        answer.append(" F(x) was not calculated.");
                    }
                    if(!socketTasks.get(1).isDone()) {
                        answer.append(" G(x) was not calculated.");
                    }
                    System.err.println(answer);
                    break;
                }
            }
            Thread.sleep(20);
        }

        System.out.println("\nTime: " + (endTime - startTime) / 1000000000 + " seconds");
        procF.destroy();
        procG.destroy();
        mainPool.shutdownNow();
        System.exit(0);
    }
}