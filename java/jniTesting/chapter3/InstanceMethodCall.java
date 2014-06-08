import java.awt.*;
import java.awt.event.*;

public class InstanceMethodCall{
	private native void nativeMethod();
	private void callback() {
		System.out.println("In Java");
		Frame f = new Frame("Ich bin aus C gerufen worden");
		f.setLayout(new GridLayout(2,2));
		f.add(new Button("NR 1"));
		f.add(new Button("NR 2"));
		f.add(new Button("NR 3"));
		f.add(new Button("NR 4"));
		f.addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent e){
				System.exit(0);
			}
		});
		f.setVisible(true);
	}
	public static void main(String[] args){
		InstanceMethodCall c = new InstanceMethodCall();
		c.nativeMethod();
	}
	static {
		System.loadLibrary("InstanceMethodCall");
}
}
