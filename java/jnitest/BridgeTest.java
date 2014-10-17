import bridge.*;

public class BridgeTest {
	public static void main(String args[]){
		SqliteBridge bridge = new SqliteBridge();
		DbData data = new DbData();
		bridge.createDatabase("testdb");
		bridge.execSql("create table human (name, surname); ", "testdb", data);
		bridge.execSql("select * from human", "testdb", data);
		System.out.println("Daten:\n" + data);
	}
}
