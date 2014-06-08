import java.net.*;
import java.util.*;

/*
	Scanner is a Program which checks the alive status of
	the pcs in a entire subnet.
*/

public class scanner {
	//Args must be in the form: [192.168 , b] or [192.168.2, c] which means that
	//the program searches for hosts in the class b/ cnetwork
	public static void main(String[] args){
		List<String> reachable = new ArrayList<String>();
		List<InetAddress> reachableInet = new ArrayList<InetAddress>();
		System.out.println(args[0] + args[1]);
		try {
			whoIsAlive(Integer.parseInt(args[2]), reachable, reachableInet, args[0], args[1]);
		} catch (Exception e) {
			System.out.println("Ein Fehler ist aufgetreten");
		}

		System.out.println("\n######################################################");
		System.out.println("Die Verfügbaren Rechner sind: \n");
		for (int i = 0; i < reachable.size(); i++){
			System.out.print(reachable.get(i) + " ==> ");
			System.out.print(reachableInet.get(i).getHostName() + "\n");
		}
		try { 
			System.out.println("Die Eigene Adresse ist: " + InetAddress.getLocalHost());
		} catch (Exception e){
		}
	}

	public static void whoIsAlive(int timeout, List<String> a, List<InetAddress> b, String cla, String clazz) throws Exception {
		if (clazz.equals("c")) {
			for(int i = 1; i < 255; i++){
				InetAddress tmp = InetAddress.getByName(cla + "." + String.valueOf(i));
				if (tmp.isReachable(timeout)) {
					System.out.println(cla + "." + String.valueOf(i) + " ist erreichbar: " + "true");
					a.add(cla + "." + String.valueOf(i));
					b.add(InetAddress.getByName(cla + "." + String.valueOf(i)));
				} else {
					System.out.println(cla + "." + String.valueOf(i) + " ist erreichbar: " + "false");
				}
			}
		} else if (clazz.equals("b")) {
			for(int i = 1; i < 255; i++){
				for(int j = 1; j < 255; j++){
					String tmp = cla + "." + String.valueOf(i) + "." + String.valueOf(j);
					InetAddress tmpIP = InetAddress.getByName(tmp);
					if (tmpIP.isReachable(timeout)){
						System.out.println(tmp + " ist erreichbar: true");
						a.add(tmp);
						b.add(InetAddress.getByName(tmp));
					} else {
						System.out.println(tmp + " ist erreichbar: false");
					}
				}
			}
		} else if (clazz.equals("a")) {
			for(int i = 1; i < 255; i++){
				for(int j = 1; j < 255; j++){
					for ( int k = 1; k < 255; k++){
						String tmp = cla + "." + String.valueOf(i) + "." + String.valueOf(j) + "." + String.valueOf(k);
						InetAddress tmpIP = InetAddress.getByName(tmp);
						if (tmpIP.isReachable(timeout)){
							System.out.println(tmp + " ist errecihbar: true");
							a.add(tmp);
							b.add(tmpIP);
						} else {
							System.out.println(tmp + " ist erreichbar: false");
						}
					}
				}
			}
		} else {
			throw new IllegalArgumentException();
		}
	}
}
