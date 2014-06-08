// package geSim;

public class Customer {
	private int StreetNr;
	private String CustomerId; //PIN
	private String Street;
	private String LastName;
	private String Name;
	private String AccountID; //CardID
	private String Gender;

	public Customer(String cid, String name, String lastname, String street, int snr, String accountid, String gender){
		this.CustomerId = cid;
		this.Street = street;
		this.StreetNr = snr;
		this.LastName = lastname;
		this.Name = name;
		this.AccountID = accountid;
		this.Gender = gender;
	}

	public String getCustomerID(){ 
		return CustomerId; 
	}

	public int getStreetNr(){ 
		return StreetNr; 
	}

	public String getStreet(){
		return Street;
	}

	public String getName(){ 
		return Name; 
	}

	public String getLastName() { 
		return LastName; 
	}

	public String getAccountID() { 
		return AccountID; 
	}

	public String getGender(){ 
		return Gender; 
	}

	public int hashCode(){
		int result = 31 + StreetNr;
		result = 31 * result + CustomerId.hashCode();
		result = 31 * result + Street.hashCode();
		result = 31 * result + LastName.hashCode();
		result = 31 * result + Name.hashCode();
		result = 31 * result + AccountID.hashCode();
		result = 31 * result + Gender.hashCode();
		return result;
	}

	public boolean equals(Object that){
		if(this == that)
			return true;

		if(that == null)
			return false;

		if( getClass() != that.getClass())
			return false;

		if( StreetNr != ((Customer)that).getStreetNr())
			return false;

		if( ! CustomerId.equals(((Customer)that).getCustomerID()))
			return false;

		if( ! Street.equals(((Customer)that).getStreet()))
			return false;

		if( ! LastName.equals(((Customer)that).getLastName()))
			return false;

		if( ! Name.equals(((Customer)that).getName()))
			return false;

		if( ! AccountID.equals(((Customer)that).getAccountID()))
			return false;

		if( ! Gender.equals(((Customer)that).getGender()))
			return false;

		return true;
	}

	public String toString(){
		return "(PIN = " + CustomerId + ", Street = " + Street + ", LastName = " + LastName + ", Name = " + Name + ", AccountID = " + AccountID + ", Gender = " + Gender + ")";
	}
}
