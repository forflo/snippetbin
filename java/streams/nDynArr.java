import java.util.*;

public class nDynArr {

	//generates a c source file which
	//contains a functionn for the dynamical
	//allocation of a n-Dim Array using
	//a void pointer wicht has to be
	//casted before the assignment
	public static String generateCode(int dimensions, int pointerBytes){
		String[] param = generateParameterList(dimensions);
		String[] vars = generateVarList(dimensions - 1);
		String pB = String.valueOf(pointerBytes);

		StringBuffer source = new StringBuffer();
		source.append("#include <stdio.h> \n");
		source.append("#include <stdlib.h> \n\n\n");
		source.append("void ");

		points(source, dimensions);

		source.append("get" + dimensions + "DimArr(");
		for(int i = 0; i < dimensions - 1; i++)
			source.append("int " + param[i] + ", ");
		source.append("int " + param[dimensions - 1] + "){\n\n");
		source.append("\tint ");	
	
		for(int i = 0; i < dimensions - 1; i++){
			source.append(vars[i] + ", ");
		}
		//change
		source.append(vars[dimensions - 2] + ";\n\n\tvoid ");
		points(source, dimensions);
		source.append("matrix;\n\n\t");
		
		source.append("matrix = malloc(zeile * " + pB + ")\n\t");

		for(int i = 1; i < dimensions; i++){
			writeNthLoop(i, source, param, vars, dimensions, pB);
		}
		
		source.append("\treturn matrix;\n}");
        return source.toString();
	}

	public static void points(StringBuffer b, int dimensions){
		for(int i = 0; i < dimensions; i++){
			b.append("*");
		}
	}

	public static void writeNthLoop(int loop, StringBuffer b, String[] param, String[] vars, int dim, String pB){
		String a = "*(";

		b.append("\n\t");
		for(int i = 0; i < loop; i ++){
			b.append("for(" + vars[i] + "; " + vars[i] + " < " + param[i] + "; " + vars[i] + "++){\n\t");
		}

		for(int i = 0; i < loop; i++){
			b.append(a);
		}

		b.append("matrix");
		for(int i = 0; i < loop; i++)
			b.append(" + " + vars[i] + ")");
		b.append(" = malloc(" + param[loop] + " * " + pB + ");\n");
		
		for(int i = 0; i < loop; i++){
			b.append("\t}\n");
		}
	}

	public static String getID(int length) {
                char[] result = new char[length];
                result[0] = 'a';
		for(int i = 1; i < length; i++){
                        int tmp = (int) Math.round((Math.random() *  2));
                        if (tmp == 2) {
                                result[i] = (char) (48 + Math.round(Math.random() * (57 - 48)));
                        } else if (tmp == 1)  {
                                result[i] = (char) (97 + Math.round(Math.random() * (122 - 97)));
                        } else {
                                result[i] = (char) (65 + Math.round(Math.random() * (90 - 65)));
                        }
                }
                return new String(result);
        }	

	public static String[] generateParameterList(int dimensions){
		String[] result = new String[dimensions];
		for(int i = 0; i < dimensions; i++){
			result[i] = getID(10);
		}

		return result;
	}

	public static String[] generateVarList(int dimensions){
		String[] result = new String[dimensions];
		for(int i = 0; i < dimensions; i++){
			result[i] = getID(10);
		}

		return result;
	}
}
