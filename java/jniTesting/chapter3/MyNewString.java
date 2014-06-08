public class MyNewString {
	public static native String getString(char[] str, int len);

	public static void main(String[] args){
		MyNewString a = new MyNewString();
		//char[] a = new char[]{}
		System.out.println(a.getString(new char[]{'A', 'B', 'C'}, 3));
	}

	static {
		System.loadLibrary("MyNewString");
	}
}
