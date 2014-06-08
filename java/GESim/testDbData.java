import org.junit.*;
import static org.junit.Assert.*;
import java.util.logging.Logger;

public class testDbData {
	public DbData data = new DbData();
	@Before
	public void setUp(){
		data.attributes = new String[] {"A", "B", "C"};
		data.data = new String[][] {{"A1", "B1", "C1"}, {"A2","B2","C2"}, {"A3","B3","C3"}};
		data.errors = "";
	}
	@Test
	public void testGetNthRow(){
		assertTrue(data.getNthRow(5) ==  null);
		assertTrue(data.getNthRow(3)[2].equals("C3"));
	}
}
