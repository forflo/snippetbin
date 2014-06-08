

public class SqliteBridge {
	static { 
		System.loadLibrary("SqliteBridge"); 
	}

	public native void execSqlDML(String sql, String path, DbData data);
	public native void execSql(String sql, String fileName, DbData data);
}
