//package gesim;

public class Cashpoint {
	private String CashpointId;
	private int AmountOfMoney;
	private String Location;
	private boolean isEmpty;
	
	public Cashpoint(String id, int amountOfMoney, String loc){
		this.CashpointId = id;
		if((amountOfMoney % 5) == 0)
			this.AmountOfMoney = amountOfMoney;
		else
			this.AmountOfMoney = 10000;
		this.Location = loc;
		this.isEmpty = false;
	}

	public String getCashpointID(){
		return CashpointId;
	}

	public int getAmountMoney(){
		return AmountOfMoney;
	}

	public String getLocation(){
		return Location;
	}

	/**
	 + returns ture, if there is enoug money
	 + false if it isn't
	*/
	public boolean setMoney(int mon){
		if((AmountOfMoney - mon) <=0 ) {
			isEmpty = true;
			return false;
		}
		AmountOfMoney = mon;
		return true;
	}

	/*
	 + equals and hashcode ...
	 + implemented by hand (-.-)
	*/
	public boolean equals(Object that){
		if(this == that)
			return true;

		if(that == null)
			return false;

		if(getClass() != that.getClass())
			return false;

		if(! CashpointId.equals(((Cashpoint)that).getCashpointID()))
			return false;

		if(! (AmountOfMoney != ((Cashpoint)that).getAmountMoney()))
			return false;

		if(! Location.equals(((Cashpoint)that).getLocation()))
			return false;

		return true;
	}

	public String toString(){
		return "(CP_ID = " + CashpointId + ", Money = " + String.valueOf(AmountOfMoney) + ", Location = " + Location + ", Empty? = " + String.valueOf(isEmpty) + ")";
	}

	public int hashCode(){
		int result = 31 + AmountOfMoney;
		result = 31 * result + CashpointId.hashCode();
		result = 31 * result + Location.hashCode();
		result = 31 * result + ((isEmpty == true) ? 100 : 200);
		return result;
	}
}
