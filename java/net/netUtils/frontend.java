package netUtils;

import java.awt.*;
import java.awt.event.*;
import java.net.InetAddress;

public class frontend {
	public static void main(String[] args){
		Frame f = new Frame();
		f.setLayout(new GridLayout(1,1));
		Panel holder = new Panel(new GridLayout(1,3));
		final TextField tf = new TextField();
		final TextField tf2 = new TextField();
		tf2.setText("ip-Adresse hier eingeben ...");
		tf.setText("mac-Adresse hier eingeben ...");
		holder.add(tf);
		holder.add(tf2);
		Button b1 = new Button("Senden");
		b1.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				try {
					Jwakeonlan.sendPacket(Jwakeonlan.getMagicPacket(tf.getText()), InetAddress.getByName(tf2.getText()));
				} catch (Exception f){
					Frame ff = new Frame();
					ff.setLayout(new GridLayout(1,1));
					ff.add(new Label("Hier ist etwas schiefgegangen"));
					ff.setSize(200,200);
					ff.setVisible(true);
					try{
						Thread.sleep(1000);
					} catch (Exception fe){}
					ff.dispose();
				}
			}
		});
		holder.add(b1);
		f.add(holder);
		f.setVisible(true);
	}
}
