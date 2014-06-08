import java.io.*;
import java.net.*;
import java.math.*;
import java.util.Scanner;

public class multServerThreaded {	

	public static class Handler extends Thread {
		private Socket client = null;
		public Handler(Socket client){
			this.client = client;
		}
		public void run(){
			try {
				Scanner in = new Scanner(client.getInputStream());
				PrintWriter out = new PrintWriter(client.getOutputStream(), true);
	
				String fak1 = in.nextLine();
				String fak2 = in.nextLine();

				out.println( new BigInteger(fak1).multiply(new BigInteger(fak2)));
	
			} catch (IOException e){
				e.printStackTrace();
			} catch (Exception e){
				e.printStackTrace();
			} finally {
				if(client != null)
					try{
						client.close();
					} catch (IOException e) {
					}
			}
		}
	}

	public static void main(String[] args) throws Exception{
		ServerSocket srvSoc = new ServerSocket(12345);
		while(true){
			try {
				Socket client = null;
				client = srvSoc.accept();
				Handler handler = new Handler(client);
				handler.run();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}
