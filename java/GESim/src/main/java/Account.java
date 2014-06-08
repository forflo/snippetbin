// package gesim;

public class Account {
	//private String CustomerId;
	//private Date CreationDate;
	private String AccountID;
	private double Balance;

	public Account(String acc,  double bal){
		AccountID = acc;
		Balance = bal;
	}

	/*
	public String getCustomerID() {
		return CustomerId;
	}


	public Data getCreationDate(){
		return CreationDate;
	}
	*/

	public String getAccountID(){
		return AccountID;
	}


	public double getBalance(){
		return Balance;
	}

	public int hashCode(){
		int result = 31 + AccountID.hashCode();
		long tmp = Double.doubleToLongBits( Balance );
		result = result * 31 + (int) (tmp ^ tmp >>> 31);
		return result;
	}

	public boolean equals(Object that){
		if(this == that)
			return true;

		if(that == null)
			return false;

		if(getClass() != that.getClass())
			return false;

		if(Balance != ((Account)that).getBalance())
			return false;

		if( ! AccountID.equals(((Account)that).getAccountID()))
			return false;

		return true;
	}

	public String toString(){
		return "(AccountID = " + AccountID + ", Balance = " + String.valueOf(Balance) + ")";
	}
}
