/*
 + Klasse zur Manipulatinon der Bits eines Int Wertes
 + Mittels Casten können auch "short" "byte" und "char
 + Variable verändert werden ...
*/

public class bitManipulation {
	public static boolean testBit(int i, int pos){
		int mask = 1 << pos;
		return (i & mask) == mask;
	}

	public static int setBit(int i, int pos){
		return i | (1 << pos);
	}

	public static int invertBit(int i, int pos){
		return i ^ (1 << pos);
	}

	public static int clearBit(int i, int pos){
		return i & ~(1 << pos);
	}
}
