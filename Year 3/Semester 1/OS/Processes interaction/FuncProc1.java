import java.net.Socket;
import java.io.DataOutputStream;

public class Main {

    public static void main(String[] args) {
        Socket socket;
        try {
            socket = new Socket("localhost", 1111);

            double x = Double.parseDouble(args[0]);
			
            DataOutputStream output = new DataOutputStream(socket.getOutputStream());
			
			if (Double.compare(x, 1.0) == 0) {
				Thread.sleep(5 * 1000);
                output.writeDouble(5.0);
			} else if (Double.compare(x, 2.0) == 0) {
				Thread.sleep(1 * 1000);
                output.writeDouble(5.0);				
			} else if (Double.compare(x, 3.0) == 0) {
				Thread.sleep(6 * 1000);
                output.writeDouble(5.0);				
			} else if (Double.compare(x, 4.0) == 0) {
				while(true) {}				
			} else if (Double.compare(x, 5.0) == 0) {
				Thread.sleep(8 * 1000);
                output.writeDouble(5.0);				
			} else if (Double.compare(x, 6.0) == 0) {
				while(true) {}				
			} else if (Double.compare(x, 7.0) == 0) {
				Thread.sleep(1 * 1000);
                output.writeDouble(5.0);				
			} else if (Double.compare(x, 8.0) == 0) {
				Thread.sleep(6 * 1000);
                output.writeDouble(5.0);				
			} else {
				Thread.sleep(4 * 1000);
                output.writeDouble(5.0);				
			} 
			
			
            output.close();
            socket.close();
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
