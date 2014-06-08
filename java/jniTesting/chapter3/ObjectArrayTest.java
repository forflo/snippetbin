public class ObjectArrayTest {
	private static native int[][] initInt2DArray(int size);
	public static void main(String[] args){
		int[][] i2arr = initInt2DArray(Integer.parseInt(args[0]));
		for(int i = 0; i < Integer.parseInt(args[0]); i++){
			for(int j = 0; j < Integer.parseInt(args[0]); j++){
				System.out.print(" " + i2arr[i][j]);
			}
			System.out.println("\n");
		}
	}
	static { System.loadLibrary("ObjectArrayTest"); }
}
