import java.awt.*;
import java.awt.event.*;

public class testData {
	public static class DialogOne extends Frame{
		public TextField tf1 = new TextField("PIN");
		public TextField tf2 = new TextField("CardID");
		public TextField tf3 = new TextField("CashpointID");
		
		public DialogOne(){
			setLayout(new GridLayout(2,1));
			add(tf1);
			add(tf3);
			add(tf2);
		}
	}

	public static class TableViewer extends Frame {
		

		public TableViewer(){

		}
	}
	

	public static void main(String[] args){
		Panel p1 = new Panel(new GridLayout(1,5));
		Panel p2 = new Panel(new GridLayout(1,3));

		Frame f = new Frame();
		
		final Data d = new Data();

		f.setLayout(new GridLayout(2,1));
		f.setSize(500, 200);
		f.addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent e){
				System.exit(0);
			}
		});

		Button reset = new Button("reset");
		reset.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				GeneralUtil.resetDB();
			}
		});

		Button deleteT = new Button("delete");
		deleteT.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				GeneralUtil.deleteTables();
			}
		});
		
		//Testdata ...
		String accID1 = GeneralUtil.getID(10);
		String accID2 = GeneralUtil.getID(10);

		final Account a = new Account(accID1, 12344.09);
		final Account b = new Account(accID1, 12344.09);	
		final Account c = new Account(accID2, 12333.03);

		String caID1 = GeneralUtil.getID(10);
		String caID2 = GeneralUtil.getID(10);

		final Customer ca = new Customer("1234", "Florian", "Mayer", "Frankenweg", 28, caID1, "Männlich");
		final Customer cb = new Customer("1234", "Florian", "Mayer", "Frankenweg", 28, caID1, "Männlich");
		final Customer cc = new Customer("4321", "Philipp", "Mayer", "Frankenweg", 28, caID2, "Männlich");

		String caaID1 = GeneralUtil.getID(10);
		String caaID2 = GeneralUtil.getID(10);	

		final Cashpoint aaa = new Cashpoint(caaID1, 1000, GeneralUtil.getRandomCity());
		final Cashpoint aab = new Cashpoint(caaID1, 1000, GeneralUtil.getRandomCity());
		final Cashpoint aac = new Cashpoint(caaID2, 1000, GeneralUtil.getRandomCity());

		ActionListener al1 = new ActionListener(){
			public void actionPerformed(ActionEvent e){
				if(!d.pushCashpoint(aaa))
					System.out.println("aab nicht erfolgreich");

				System.out.println("\n");

				if(!d.pushCashpoint(aab))
					System.out.println("aab nicht erfolgreich");

				System.out.println("\n");

				if(!d.pushCashpoint(aac))
					System.out.println("aab nicht erfolgreich");

				System.out.println("\n");
			}
		};

		ActionListener al2 = new ActionListener(){
			public void actionPerformed(ActionEvent e){
				if(! d.pushAccount(a))
					System.out.println("a nicht erfolgreich !");

				System.out.println("\n");

				if(! d.pushAccount(b))
					System.out.println("b nicht erfolgreich !");

				System.out.println("\n");

				if(! d.pushAccount(c))
					System.out.println("c nicht erfolgreich !");

				System.out.println("\n");
			}
		};

		ActionListener al3 = new ActionListener(){
			public void actionPerformed(ActionEvent e){
				if(! d.pushCustomer(ca))
					System.out.println("ca nicht erfolgreich !");

				System.out.println("\n");

				if(! d.pushCustomer(cb))
					System.out.println("cb nicht erfolgreich !");

				System.out.println("\n");

				if(! d.pushCustomer(cc))
					System.out.println("cc nicht erfolgreich !");

				System.out.println("\n");
			}
		};
	
		Customer customer = null;
		Cashpoint cash = null;
		Account account = null;
		final DialogOne diag = new DialogOne();
		diag.setVisible(true);

		ActionListener al4 = new ActionListener(){
			public void actionPerformed(ActionEvent e){
				System.out.println(d.getCashpointByID(diag.tf3.getText()).toString());
			}
		};

		ActionListener al5 = new ActionListener(){
			public void actionPerformed(ActionEvent e){
				System.out.println(d.getAccountByCustomer(d.getCustomerByData(diag.tf1.getText(), diag.tf2.getText())).toString());
			}
		};

		ActionListener al6 = new ActionListener(){
			public void actionPerformed(ActionEvent e){
				System.out.println(d.getCustomerByData(diag.tf1.getText(), diag.tf2.getText()).toString());
			}
		};

		Button aa1 = new Button("Cashpoints");
		aa1.addActionListener(al1);
		Button bb1 = new Button("Accounts");
		bb1.addActionListener(al2);
		Button cc1 = new Button("Customers");
		cc1.addActionListener(al3);

		p1.add(reset); 
		p1.add(deleteT);
		p1.add(aa1); 
		p1.add(bb1); 
		p1.add(cc1);

		Button dd1 = new Button("getCashpoint");
		dd1.addActionListener(al4);
		Button ee1 = new Button("getAccount");
		ee1.addActionListener(al5);
		Button ff1 = new Button("getCustomer");
		ff1.addActionListener(al6);

		p2.add(dd1);
		p2.add(ee1);
		p2.add(ff1);

		f.add(p1);
		f.add(p2);
		f.setVisible(true);
	}
}
