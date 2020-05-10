/* CS232 Caesar Cipher Server
*
* Author: Brian Goins (bm23) 
*
*/


import java.util.Scanner;
import java.net.Socket;
import java.net.ServerSocket;
import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Date;
import java.text.DateFormat;
import java.text.SimpleDateFormat;

public class CaesarCipherServer {

	public static void main(String[] args) throws Exception {

		
		if (args.length != 1) {
            System.err.println("Usage: <port>");
            System.exit(1);
        }

        
		int portNumber = Integer.parseInt(args[0]);
		
		Boolean listening = true;

		
		try (ServerSocket serverSocket = new ServerSocket(portNumber)) { 

			
            while (listening) {
	            new CaesarCipherMultiThread(serverSocket.accept()).start();
	        }

	    
	    } catch (IOException e) {
            System.err.println("Could not listen on port " + portNumber);
            System.exit(-1);
        }
    }
}


class CaesarCipherMultiThread extends Thread {

	
	private Socket clientSocket = null;
	private String ipAddress;

	
	public CaesarCipherMultiThread(Socket socket) {
		this.clientSocket = socket;
		DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
		Date date = new Date();
		ipAddress = this.clientSocket.getRemoteSocketAddress().toString();
		System.out.println("New connection to " + ipAddress + " at " + dateFormat.format(date));
	}

	
	public void run() {

		try (   PrintWriter writer = new PrintWriter(clientSocket.getOutputStream(), true);
				BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
		) {
			
			Boolean integer = true;
			Integer rotation = 0;
			String inputline;
	
			
			while ((inputline = in.readLine()) != null) {

				
				if (integer) {
					rotation = Integer.parseInt(inputline);
					writer.append(rotation.toString());
					writer.append("\n");
					writer.flush();
					integer = false;
					continue;
				}

				
				writer.append(caesarCipher(rotation, inputline));
				writer.append("\n");
				writer.flush();
			}

		
			System.out.println("Closing connection to client " + ipAddress);
			out.close();
			in.close();
			clientSocket.close();

		} catch (IOException e) {
			e.printStackTrace();
		}
	}


	
	private static String caesarCipher(Integer rotation, String string) {

		String tempString = "";
		Integer length = string.length();

		for (Integer x = 0; x < length; x++) {
			char c = (char)(string.charAt(x) + rotation);
			if (c > 'z') {
				tempString += (char)(string.charAt(x) - (26-rotation));
			} else {
				tempString += (char)(string.charAt(x) + rotation);
			}
		}
		return tempString;
	}

}