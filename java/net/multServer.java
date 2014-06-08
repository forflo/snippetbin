import java.io.*;
import java.net.*;
import java.math.*;
import java.util.Scanner;

public class multServer {
	
	private static void handleConnection(Socket client) throws Exception {
		Scanner in = new Scanner(client.getInputStream());
		PrintWriter out = new PrintWriter(client.getOutputStream(), true);

		String fak1 = in.nextLine();
		String fak2 = in.nextLine();

		out.println( new BigInteger(fak1).multiply(new BigInteger(fak2)));
	}

	public static void main(String[] args) throws Exception{
		ServerSocket srvSoc = new ServerSocket(12345);
		int cnt = 0;
		while(true){
			Socket client = null;
			try {
				client = srvSoc.accept();
				cnt++;
				handleConnection(client);
			} catch (IOException e){
				e.printStackTrace();
			} finally {
				if(client != null)
					try {
						client.close();
						System.out.println("client nr. " + cnt + " closed");
					} catch (IOException e) {}
			}
		}
	}
}
