import java.util.*;

public class DbData{
	public String[] attributes = null;
	public String[][] data = null;
	public String errors;

	public DbData(){
		errors = "NONE";
		//attributes = new String[];
		//data = new String[][];
	}
	
	public boolean isOkay(){
		return errors.equals("NONE");
	}

	/**
	 + This function can be used to format the sql-data
	 + If this Object does not contain the requested row,
	 + the resulting array will be null
	 + @return <p> The n-th row as stringarray </p>
	*/
	public String[] getNthRow(int line){
		if(line < 0 || line > data.length)
			return null;
		return data[line - 1];
	}

	public int getRowCount(){
		return data.length;
	}

	public boolean isEmpty(){
		return data == null;
	}

	public int getAttrCount(){
		return attributes.length;
	}

	public String toString(){
		StringBuffer buf = new StringBuffer();
		for(int i = 0; i < attributes.length; i++)
			buf.append("   " + attributes[i] + " | ");
		buf.append("\n\n");
		
		for(int i = 0; i < data.length; i++){
			for(int j = 0; j < data[0].length; j++) {
				if (j == 0) buf.append(String.valueOf(i) + ": ");
				buf.append(data[i][j] + " | ");
			}
			buf.append("\n");
		}
		return buf.toString();
	}
}
