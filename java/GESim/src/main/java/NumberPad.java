import java.awt.*;
import java.awt.event.*;

public class NumberPad extends Frame{
	public static final int MAX_LENGTH = 4;
	private TextField tf;
	
	private int counter = 0;

	private ActionListener al = new ActionListener(){
		public void actionPerformed(ActionEvent e){
			if(! (counter > MAX_LENGTH)) {
				tf.setText(tf.getText() + ((Button)e.getSource()).getLabel());
				counter++;
			}
		}
	};

	public NumberPad(TextField tf){
		Panel holder = new Panel(new GridLayout(4, 3));
		Button[] buts = new Button[10];
		buts[0] = new Button("0");
		for(int i = 1; i < 10; i++){
			buts[i] = new Button(String.valueOf(i));
			buts[i].addActionListener(al);
			holder.add(buts[i]);
		}
		buts[0].addActionListener(al);
		holder.add(buts[0]);
		
		this.add(holder);
		this.pack();
		this.setVisible(true);
	}

	public void setTextField(TextField tf){
		this.tf = tf;
	}
}
