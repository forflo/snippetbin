package bridge;

public class SqliteBridge {
	static { 
		System.loadLibrary("SqliteBridge"); 
	}

	public native void execSqlDML(String sql, String path, DbData data);
	public native void execSql(String sql, String fileName, DbData data);
	//TODO
	public native void createDatabase(String name); /* the name has to bee fully qualified */
}
