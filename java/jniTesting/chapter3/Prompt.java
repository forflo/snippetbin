public class Prompt {
	private native String getLine(String p);

	public static void main(String[] args){
		Prompt p = new Prompt();
		String input = p.getLine("Type something: ");
		System.out.println("User typed: " + input);
	}
	static {
		System.loadLibrary("Prompt");
	}
}
