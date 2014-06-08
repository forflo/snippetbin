public class SqliteBridge {
	public static void main(String[] args){
		SqliteBridge a = new SqliteBridge();
		DbData data = new DbData();
		a.execSql("select name from testing", "testdb", data);
		if (data != null){
			System.out.println(data.toString());
		}
	}

	static { 
		System.loadLibrary("SqliteBridge"); 
	}

	public native void execSql(String sql, String fileName, DbData data);
}
