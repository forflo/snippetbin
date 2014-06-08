import java.io.*;
import org.junit.*;
import static org.junit.Assert.*;
import java.util.logging.Logger;

public class testGeneralUtils {
	private static Logger logger = Logger.getLogger(testGeneralUtils.class.getName());
	public static final String DELIMITER = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

	public static void drawDelimiter(String name){
		System.out.println("\n" + DELIMITER + name + DELIMITER);
	}

	public static void dEnd(){
		drawDelimiter("testing ended");
	}

	@Test
	public void testGetCardValue(){
		drawDelimiter("testGetCardValue");
		try{
			System.out.println(GeneralUtil.getCardValue(50));
			System.out.println(GeneralUtil.getCardValue(500));
			System.out.println(GeneralUtil.getCardValue(400));
			System.out.println(GeneralUtil.getCardValue(90));
			System.out.println(GeneralUtil.getCardValue(1));
			System.out.println(GeneralUtil.getCardValue(0));
		} catch (IllegalArgumentException e) {
			System.out.println(e.getMessage());
		}
		dEnd();
	}
	@Test	
	public void testGetCity(){
		drawDelimiter("testGetCity");
		System.out.println(GeneralUtil.getRandomCity());
		System.out.println(GeneralUtil.getRandomCity());
		System.out.println(GeneralUtil.getRandomCity());
		dEnd();
	}
	@Test
	public void testGetID(){
		drawDelimiter("testGetID");
		System.out.println(GeneralUtil.getID(50));
		System.out.println(GeneralUtil.getID(20));
		dEnd();
	}

	@Test
	public void testExecSql(){
		drawDelimiter("testExecSql");
		DbData data;
		try {
			data = GeneralUtil.execSql("select * from testing", false);
			System.out.println(data.toString());
		} catch (IOException e){
			System.out.println("Ein Fehler bei der Sql Abfrage ist aufgetreten !");
		}
		dEnd();
	}

	/**
	 + tests if the method throws an exception
	 + as expected ...
	*/
	@Test
	public void testExecSql2(){
		drawDelimiter("testExecSql 2");
		try {
			DbData data = GeneralUtil.execSql("select hahaha;++fae333", false);
			assertTrue(1 == 0);
		} catch (IOException e) {
			assertTrue(1 == 1);
		}
		dEnd();
	}

	@Test
	public void testExecSql3(){
		drawDelimiter("testExecSql 3");
		try {
			DbData data = GeneralUtil.execSql("select * from bla", false);
		} catch (IOException e){
			System.out.println("Error as expected ...");
		}
		dEnd();
	}
}
