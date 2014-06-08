public class StaticMethodCall {
	private native void nativeMethod();
	private static void callback() {
		System.out.println("in Java");
	}

	public static void main(String[] args){
		StaticMethodCall a = new StaticMethodCall();
		a.nativeMethod();
	}
	static {
		System.loadLibrary("StaticMethodCall");
	}
}
