import java.util.*;

public class performanceTest {
	public static void main(String[] args){
		Data data = new Data(true);
		if(args.length < 1)
			System.exit(1);
		for(int i = 0; i < Integer.parseInt(args[0]); i++){
			Account ac = new Account(GeneralUtil.getID(20), 1000.00);
			Cashpoint cap = new Cashpoint(GeneralUtil.getID(20), 1000, GeneralUtil.getRandomCity());
			data.pushCashpoint(cap);
			data.pushAccount(ac);
		}
	}
}
