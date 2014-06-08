import java.io.*;
import java.util.Scanner;
import java.net.*;

public class multClient {
	public static void main(String[] args) throws Exception {
		BufferedReader red = new BufferedReader(new InputStreamReader(System.in));
		Socket client = new Socket(args[0],Integer.parseInt(args[1]));

		PrintWriter pw = new PrintWriter(client.getOutputStream(), true);
		Scanner scan = new Scanner(client.getInputStream());

		pw.println(red.readLine());
		pw.println(red.readLine());
		Thread.sleep(1000);
		System.out.println(scan.nextLine());
	}
}
