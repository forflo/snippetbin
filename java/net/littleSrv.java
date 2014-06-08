import java.io.*;
import java.net.*;
import java.util.Scanner;

public class littleSrv {
	public static void main(String[] args) throws Exception{
		ServerSocket soc = new ServerSocket(12345);

		Socket client = soc.accept();

		Scanner in = new Scanner(client.getInputStream());
		PrintWriter out = new PrintWriter(client.getOutputStream(), true);
	
		if(in.nextLine().equals("authenticate")){
			out.println("okay");
			String a = in.nextLine();
			String b = in.nextLine();
			String c = in.nextLine();
			out.println("a " + a +  " b " + b + " c "+  c);
		}

		client.close();
		soc.close();
	}
}
