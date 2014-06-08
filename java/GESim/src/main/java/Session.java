//package client;
import java.net.*;
import java.util.Scanner;
import java.io.*;

/**
 + This class is used by the clients of the system
 + to simplify the connection with the server
 + If a client want to interact with a server
 + it has to create an instance of Session by
 + passing the CashpointID, the Serverport and
 + the serverip to the konstructor...
*/
public class Session{
	private Socket soc;
	private String GeID;
	private boolean isAuthenticated = false;
	private Scanner getLine;
	private PrintWriter pushLine;

	/**
	 +
	*/
	public Session(String GeID, int port, String ip){
		this.GeID = GeID;
		try {
			//establishes the connection between
			//the Server. The Server will create
			//a new SessionHander (which is an inheritance of the Thread class)
			//and connect this object with an instance of
			//SessionHandler via tcp
			soc = new Socket(InetAddress.getByName(ip), port);
			this.getLine = new Scanner(soc.getInputStream());
			this.pushLine = new PrintWriter(soc.getOutputStream(), true);
		} catch (IOException e){
			e.printStackTrace();
		} catch (Exception e){
			e.printStackTrace();
		}
	}

	public boolean setSocket(Socket soce){
		if (soce.isClosed() != true) {
			soc = soce;
			return true;
		} else {
			return false;
		}
	}

	/**
	 + authenticates the current session at the server
	 + using the pin and the cardID, both given by
	 + the current User at the Cashpoint
	 @ return <p> 	true, if the authentication was successful.
			false, if it was'nt 	</p>
	 @ param <p> 	The PIN and the CardID given by the current
			cashpoint User 		</p>
	*/
	private boolean authenticate(String pin, String cardID) throws Exception {
		if (isAuthenticated == true)
			return true;
		if (soc.isClosed())
			return false;

		sendLine("authenticate");
		if ( getLine().equals("okay")) {
			sendLine(GeID);
			sendLine(pin);
			sendLine(cardID);
			if(getLine().equals("okay")){
				isAuthenticated = true;
				return true;
			} else {
				soc.close();
				return false;
			}
		} else {
			soc.close();
			isAuthenticated = false;
			return false;
		}
	}

	/**
	 + returns the balance of the bank account...
	 @ return <p> 	The balance.</p>
	 @ throws <p> 	IllegalAccessException if the session isn't authenticated
			IllegalStateException if the session is closed</p>
	*/
	private double getBalance() throws Exception {
		if (isAuthenticated == false)
			throw new IllegalAccessException("Not Authenticated ...");
		if ( soc.isClosed() == true)
			throw new IllegalStateException("The Session is closed ...");

		double result = 0.0; 	
		sendLine("get balance");
		if(getLine().equals("okay")){
			result = Double.parseDouble(getLine());	
			return result;
		} else {
			throw new IOException();
		}
	}

	/**
	 + If the current user of the cashpoint wants to draw money the account
	 + the client has to call this method to determine whether there is enought
	 + money or not ...
	 @param <p> 	The money the user wants to draw from the account </p>
	 @throws <p> 	IllegalAccessException if the Session isn't valid 
			IllegalStateException if the Session has been closed </p>
	 @return <p> 	true, if there is enough money, false, if there is not or
			the draw could be done </p>
	*/
	private boolean drawMoney(int money) throws Exception{
		if (isAuthenticated == false)
			throw new IllegalAccessException("Not Authenticated ...");
		if ( soc.isClosed() == true)
			throw new IllegalStateException("The Session is closed ...");
		
		sendLine("draw money");
		if (getLine().equals("okay"))
			sendLine(String.valueOf(money));
		else
			return false;

		if (getLine().equals("okay"))
			return true;
		else 
			return false;
	}

	/**
	 + closes the current session assigned socket and sets the 
	 + authentication state to false
	 @param void
	 @return <p> 	true, if the process was successful, false if not </p>
	*/
	private boolean closeConnection(){
		try {
			isAuthenticated = false;
			sendLine("done");
			soc.close();
		} catch (IOException e){
			isAuthenticated = false;
			return false;
		} catch (Exception e) {
			isAuthenticated = false;
			e.printStackTrace();
			return false;
		}
		return true;
	}
	
	/**
	 + Sends a line to the SessionHandler through the session-socket, in this
	 + case "soc"
	 @param <p> 	The string to send over the connection </p>
	*/
	private void sendLine(String line){
		pushLine.println(line);
	}

	/**
	 + returns a line from the open session-socket
	 @return <p> 	The string read over the connection</p>
	*/
	private String getLine(){
		return getLine.nextLine();
	}
}
