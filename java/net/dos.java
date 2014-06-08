import java.net.*;

public class dos {
	public static void main(String[] args){
		try{
			byte[] testPack = new String("Ich habe keine Ahnung wohin ich gehe").getBytes();
			DatagramSocket soc = new DatagramSocket();
			DatagramPacket pac = new DatagramPacket(testPack, testPack.length, InetAddress.getByName(args[0]), 1234);
			while(true)
				soc.send(pac);
		} catch (Exception e) {}
	}
}
