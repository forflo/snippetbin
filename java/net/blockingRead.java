import java.net.*;

public class blockingRead {
	public static void main(String[] args) throws Exception{
		new ServerSocket(12345);

		final Socket t = new Socket("localhost", 12345);

		new Thread( new Runnable(){
			public void run(){
				try{
					System.out.println("gleich awera");
					System.out.println(t.getInputStream().read());
					System.out.println("her hängt er ...");
				} catch (Exception e) {
					System.out.println("Fertig gelöst");
				}
			}
		}).start();
		Thread.sleep(2000);
		t.close();
	}

}
