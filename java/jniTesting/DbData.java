import java.util.*;

public class DbData{
	public String[] attributes;
	public String[][] data;

	public String toString(){
		StringBuffer buf = new StringBuffer();
		for(int i = 0; i < attributes.length; i++)
			buf.append("   " + attributes[i] + " | ");
		buf.append("\n\n");
		
		for(int i = 0; i < data.length; i++){
			for(int j = 0; j < data[0].length; j++) {
				if (j == 0) buf.append("1: ");
				buf.append(data[i][j] + " | ");
			}
			buf.append("\n");
		}
		return buf.toString();
	}
}
