import java.io.*;

public class serializeBoolArr {
	public static Boolean[][] testing = {

		{ false, false, false, false, false, true, true, true, true, false, false, false, false, false }, // 1
			{ false, false, false, true, true, false, false, false, false, true, true, false, false, false }, // 2
			{ false, false, true, false, false, false, false, false, false, false, false, true, false, false },// 3
			{ false, true, false, false, false, false, false, false, false, false, false, false, true, false },// 4
			{ false, true, false, false, true, true, false, false, true, true, false, false, true, false }, // 5
			{ true, false, false, false, true, true, false, false, true, true, false, false, false, true },
			{ true, false, false, false, false, false, false, false, false, false, false, false, false, true },
			{ true, false, false, false, false, false, false, false, false, false, false, false, false, true },
			{ true, false, false, true, false, false, false, false, false, false, true, false, false, true },
			{ false, true, false, false, true, false, false, false, false, true, false, false, true, false },
			{ false, true, false, false, false, true, true, true, true, false, false, false, true, false },
			{ false, false, true, false, false, false, false, false, false, false, false, true, false, false },
			{ false, false, false, true, true, false, false, false, false, true, true, false, false, false },
			{ false, false, false, false, false, true, true, true, true, false, false, false, false, false, }

	};
	
	public static void main(String[] args) throws Exception{
		serialize("/Users/florianmayer/Desktop/data.txt", testing);
	}

	public static void serialize(String file, Boolean[][] data) throws IOException {
		File f = new File(file);
		OutputStream os = new FileOutputStream( f );
		for ( int i = 0; i < data.length; i ++ ){
			for ( int j = 0; j < data[0].length; j++ )
				os.write( ( data[i][j] == true ) ? new String("1").getBytes() : new String("0").getBytes() );
			os.write(new String("\n").getBytes());
		}
		os.close();
	}
}
