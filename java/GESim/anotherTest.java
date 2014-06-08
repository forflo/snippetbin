public class anotherTest {
	public static void main(String[] args) throws Exception{
		for(int i = 0; i < 1; i++){
			DbData dat = GeneralUtil.execSql("select * from Account" ,false);
			System.out.println(dat.toString());
		}
	}
}
