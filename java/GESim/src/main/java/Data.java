//package gesim;

import java.io.*;
import java.util.*;

/**
 + This class privides the routines for pop- and pushing
 + account, customer or cashpoint objects FROM and in the
 + database accessed throught the method execSql declared in
 + the class "GeneralUtil" ...
 + Btw: The metods in this class are only for one reason not
 + staic. You don't have to use the classname in front of the
 + methodname. "Data a = new Data()"; a.getCashpointByID("fooo")" is
 + a little bit shorter :-)
 + @author Florian Mayer
 + @version 0.1
*/
public class Data {
	public boolean verbose = false;

	public Data(){
		verbose = false;
	}

	public Data(boolean verbose){
		this.verbose = verbose;
	}

	/**
	 + returns null if cashpoint doesn't exitst
	*/
	public Cashpoint getCashpointByID(String GeID){
		try {
			DbData data = GeneralUtil.execSql("SELECT * FROM Cashpoint WHERE CP_ID = '" + GeID + "'", false);
			
			if (!data.isOkay() || data.isEmpty())
				return null;
			if(verbose)
				System.out.println("[getCashpointByID] get the Cashpoint with ID = " + GeID  + " ...");

			return new Cashpoint(data.data[0][0], Integer.parseInt(data.data[0][2]), data.data[0][1]);
		} catch (IOException e) {
			System.out.println("[getCashpointByID] Ein Datenbankfehler ist aufgetreten ...");
			return null;
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}
	}

	/**
	 + returns null if customer doesn't exist
	 + 
	*/
	public Customer getCustomerByData(String pin, String CardID){
		try {
			String a = "'" + CardID +  "'";
			String b = "'" + pin + "'";
			DbData data = GeneralUtil.execSql("SELECT * FROM Customer WHERE C_ID = " + b + " AND Account_ID = " + a , false);
			
			if(!data.isOkay())
				return null;
			
			if(verbose)
				System.out.println("[getCustomerByData] got the Customer ...");

			return new Customer(data.data[0][0], data.data[0][1], data.data[0][2], data.data[0][3], Integer.parseInt(data.data[0][4]), data.data[0][5], data.data[0][6]);
		} catch (IOException e){
			System.out.println("[getCustomerByData] Ein Datenbankfehler trat auf..");
			return null;
		} catch (Exception e){
			e.printStackTrace();
			return null;
		}
	}

	/**
	 + querys an account by the given customerid
	 + @param <p> 	The customer who owns the account </p>
	 + @return <p>	null if the query was not possible or failed.
			An Account object if everything was allright </p>
	*/
	public Account getAccountByCustomer(Customer cu){
		try {
			DbData data = GeneralUtil.execSql("SELECT Account_ID, Balance FROM Customer NATURAL JOIN Account WHERE C_ID = '" + cu.getCustomerID() + "'" , false);
			if(! data.isOkay())
				return null;
			if(verbose)
				System.out.println("[getAccountByCustomer] got the Account ...");
			
			return new Account(data.data[0][0], Double.parseDouble(data.data[0][1]));
		} catch (IOException e) {
			System.out.println("[getAccountByCustomer] Ein Datenbankfehler trat auf...");
			return null;
		} catch (Exception e){
			e.printStackTrace();
			return null;
		}
	}

	/**
	 + Updates or adds the given Cashpoint object.
	 @param <p> 	the Cashpoint object to update or add	</p>
	 @return <p>	true, if the process was successful, false
			if it was not				</p>
	*/
	public boolean pushCashpoint(Cashpoint cp){
		try {
			GeneralUtil.execSql("INSERT INTO Cashpoint VALUES ('" + cp.getCashpointID() + "', '" + cp.getLocation() + "', '" + String.valueOf(cp.getAmountMoney()) + "')" , true);
			if(verbose)
				System.out.println("[pushCashpoint] push the Cashpoint ...");
			return true;
		} catch (IOException e) {
			System.out.println("[pushCashpoint] Ein Datenbankfehler ist aufgetreten ...");
			return false;
		} catch (Exception e){
			e.printStackTrace();
			return false;
		}
	}

	/**
	 + Updates or adds the given Customer object.
	 @param <p> 	the Customer to add or to updata 	</p>
	 @return <p>	true, if the process was successful, false
			if it was not ...			</p>
	*/
	public boolean pushCustomer(Customer cu){
		try {
			String C_ID = "'" + cu.getCustomerID() + "',";
			String N = "'" + cu.getName() + "',";
			String LN = "'" + cu.getLastName() + "',";
			String S = "'" + cu.getStreet() + "',";
			String StrN = "'" + String.valueOf(cu.getStreetNr()) + "',";
			String A_ID = "'" + cu.getAccountID() + "',";
			String Gender = "'" + cu.getGender() + "'";
			//write in the database ..			
			GeneralUtil.execSql("INSERT INTO Customer VALUES(" + C_ID + N + LN + S + StrN + A_ID + Gender + ")" , true);
			if(verbose)
				System.out.println("[pushCusomter] push the Customer into the database ...");
	
			return true;
		} catch (IOException e) {
			System.out.println("[pushCustomer] Ein Datenbankfehler trat auf ...");
			return false;
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
	}

	/**
	 + Updates an existing account, or adds the
	 + given account to to database if it does not
	 + exist there..
	 @param <p> 	The account	</p>
	 @return <p> 	true, if the account was added or updatet in
			the database, false, if the process was not
			successful ...</p>
	*/
	public boolean pushAccount(Account ac){
		try {
			String A_ID = "'" + ac.getAccountID() + "',";
			//String C_ID = "'" + ac.getCustomerID() + "',";
			String B = "'" +  String.valueOf(ac.getBalance()) + "')";
			GeneralUtil.execSql("INSERT INTO Account VALUES (" + A_ID + B, true);
			if(verbose)
				System.out.println("[pushAccount] push the Account in the database ...");
			return true;
		} catch (IOException e) {
			System.out.println("[pushAccount] Ein Datanbankfehler trat auf.. ");
			return false;
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
	}
}
