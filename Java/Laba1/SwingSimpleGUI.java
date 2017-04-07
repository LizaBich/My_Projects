import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SwingSimpleGUI extends JFrame {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	SwingSimpleGUI(){
		super("Laba 1");
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setSize(250, 100);
		addComponents(this.getContentPane());
	}
	
	private void addComponents(Container inner){
		inner.setLayout(new GridBagLayout());
		GridBagConstraints cons = new GridBagConstraints();
		cons.fill = GridBagConstraints.HORIZONTAL;
		
		cons.gridx = 0;
		cons.gridy = 0;
		cons.insets = new Insets(1,2,1,2);
		inner.add(new JLabel("Десятичная"), cons);
		
		cons.gridx = 1;
		cons.gridy = 0;
		cons.insets = new Insets(1,2,1,2);
		inner.add(new JLabel("Двоичная"), cons);
		
		cons.gridx = 0;
		cons.gridy = 1;
		cons.insets = new Insets(1,2,1,2);
		JTextField tfield = new JTextField();
		inner.add(tfield, cons);
		
		cons.gridx = 1;
		cons.gridy = 1;
		cons.insets = new Insets(1,2,1,2);
		JLabel bin = new JLabel();
		inner.add(bin, cons);
		
		cons.gridx = 0;
		cons.gridy = 2;
		cons.insets = new Insets(1,2,1,2);
		JButton convert = new JButton("Конвертировать");
		convert.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent event){
				int deg = Integer.parseInt(tfield.getText());
				bin.setText(getConvert(deg));
			}
		});
		inner.add(convert, cons);
	}
	
	private String getConvert(int deg) {
		
		String temp = "";
				int b;
				while (deg != 0) {
					b = deg%2;
					temp = b + temp;
					deg = deg/2;
				}
		return temp;
	}
	
	public static void main(String[] args){
		SwingSimpleGUI m = new SwingSimpleGUI();
		m.setVisible(true);
	}
}
