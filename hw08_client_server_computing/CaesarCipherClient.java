/* CS232 Caesar Cipher Client
*
* Author: Brian Goins (bm23) 
*
*/

import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.OutputStream;
import java.util.Scanner;
import java.net.Socket;


public class CaesarCipherClient {

	public static void main(String[] args) throws IOException {

        if (args.length != 2) {
            System.err.println("Usage: <server> <port> (both required)");
            System.exit(1);
        }

        String serverName = args[0];
		Integer portNumber = Integer.parseInt(args[1]);
	
		
		System.out.println("Welcome!\n");

		System.out.print("Please enter the rotation offset integer (1..25): ");

		//Get user input
		Scanner keyboardScanner = new Scanner(System.in);
		Integer rotation = keyboardScanner.nextInt();

		try (
            Socket serverSocket = new Socket(serverName, portNumber);
            OutputStream os = serverSocket.getOutputStream();
            PrintWriter write= new PrintWriter(os, true);
			BufferedReader input = new BufferedReader(new InputStreamReader(serverSocket.getInputStream()));
		) {
			
			write.append(rotation.toString());
			write.append("\n");
			write.flush();

            
            
			String outputLine = input.readLine();
			System.out.println("Server returned integer of: " + outputLine + "\n");

			
			String textBack;
			while (true) {
				System.out.print("Enter plain text: ");
				String text = keyboardScanner.nextLine();

				if (text.equals("quit")) {
					System.out.println("\nSee you later!n");
					break;
				}

				write.append(text);
				write.append("\n");
				write.flush();

				textBack = input.readLine();

				System.out.println("Text recieved: " + textBack + "\n");
			}
		} catch (IOException e) {
			System.err.println("Unable to connect to: " + serverName);
			System.exit(-1);
		}

	}
}