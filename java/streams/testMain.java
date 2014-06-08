import java.io.*;

public class testMain {
	public static void main(String[] args) throws Exception{
		File f = new File("/Users/florianmayer/Desktop/bla.txt");
/*
		FileWriter fw = new FileWriter(f);
		fw.write(nDynArr.generateCode(3, 8));
		fw.close();
*/
		System.out.println(nDynArr.generateCode(Integer.parseInt(args[0]), 8));
	}


}
