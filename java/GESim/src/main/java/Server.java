import java.net.*;
import java.util.*;
import java.io.*;


public class Server {
	public static final String USERTEXT = "usage: java programname portnumber (must be greater than 1024) ...";
	public static int counter = 0;

	public static class SessionHandler extends Thread {
		private Socket conn;
		private Scanner getLine;
		private PrintWriter pushLine;
		private boolean isAuthenticated = false;
		private Cashpoint cp;
		private Customer cu;
		private Account ac;
		private Data data;
		private int ThreadNumber;

		public SessionHandler(Socket client, int threadNr){
			ThreadNumber = threadNr;
			Data data = new Data();
			conn = client;
			try {
				getLine = new Scanner(conn.getInputStream());
				pushLine = new PrintWriter(conn.getOutputStream(), true);
			} catch (IOException e){
				e.printStackTrace();
			} catch (Exception e){
				e.printStackTrace();
			}
		}

		public void printMsg(String msg){
			System.out.println(String.valueOf(ThreadNumber) + " ---> [" + msg + "]");
		}

		public void run(){
			//The message loop ...

			while(true) {
				//get a command ...
				String tmp;
				try {
					tmp = getLine();
				} catch (Exception e) {
					break;
				}
				
				//execute commands ...
				if ( tmp.equals("done")) {
					break;
				} else if ( tmp.equals("authenticate")) {
					if ( authenticate() ) {
						continue;
					} else { 
						break;
					}
				} else if ( tmp.equals("draw money") ) {
					if(isAuthenticated)
						drawMoney();
					else
						continue;
				} else if ( tmp.equals("get Balance") ) {
					if(isAuthenticated)
						getBalance();
					else
						continue;
				} else {
					printMsg("No Command ...");
				}
			}

			try {
				conn.close();
			} catch (Exception e){}
		}

		private boolean getBalance() {
			sendLine("okay");
			sendLine(String.valueOf(ac.getBalance()));
			return true;
		}

		private boolean drawMoney(){
			sendLine("okay");
			int moneyNumber = Integer.parseInt(getLine());
			if((moneyNumber % 5) != 0){
				sendLine("nope");
				return false;
			} else {
				if(!cp.setMoney(cp.getAmountMoney() - moneyNumber)){
					sendLine("nope");
					return false;
				}
			}
			sendLine("okay");
			return false;
		}

		private boolean authenticate(){
			sendLine("okay");
			String GeID = getLine();
			String Pin = getLine();
			String CardID = getLine();
			//the authentication
			printMsg(GeID + Pin + CardID);
			cp = data.getCashpointByID(GeID);
			cu = data.getCustomerByData(Pin, CardID);
			
			if(cu == null || cp == null) {
				sendLine("close");
				return false;
			} else {
				sendLine("okay");
			}
			isAuthenticated = true;
			return true;
		}

		private void sendLine(String line){
			pushLine.println(line);
		}

		private String getLine(){
			return getLine.nextLine();
		}
	}

	/**
	 + To run the Server you need to call the program
	 + by passing the portnumber as argument of the
	 + "java" commandline program
	*/
	public static void main(String[] args) throws Exception{
		/* checks the arguments */

		if (args.length < 1 || args.length > 1) {
			System.out.println(USERTEXT);
			System.exit(1);
		}

		/*
		 + only root can run a server socekt on ports
		 + that are less than 1024 ...
		*/
		if (Integer.parseInt(args[0]) <= 1024){
			System.out.println("The Portnumber must be greater than 1024");
			System.exit(1);
		}

		ServerSocket soc = null;
		try {
			soc = new ServerSocket(Integer.parseInt(args[0]));
		} catch (Exception e){
			/* exit if the socket could not be bound to the given port */
			e.printStackTrace();
			System.exit(1);
		}
		
		/*
		 + the main server loop runs until there occures an
		 + exception which is not an IOException. Because it
		 + could be an SecurityException or worse, the server
		 + will stop accepting further connections and immediately
		 + asks on the commandline on continuation ...
		*/
		while(true){
			Socket client = null;
			try {
				client = soc.accept();
				new SessionHandler(client, counter++).run();
			} catch ( IOException e ) {
				e.printStackTrace();
			} catch ( Exception e) {
				e.printStackTrace();
				BufferedReader bufRead = new BufferedReader(new InputStreamReader(System.in));
				System.out.println("\n\nEine möglicherweise kritische Ausnahme ist eingetreten\nTrotzdem weitermachen ? (yes/no)");
				
				while (true) {
					String in = bufRead.readLine();
					if ( in.toUpperCase().equals("YES")) {
						break;
					} else if (in.toUpperCase().equals("NO")) {
						System.exit(0);
					} else {
						System.out.println(">>> Conduction [yes/no] !\n");
					}
				}
			}
		}
	}
}
