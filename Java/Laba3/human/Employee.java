package human;

import javax.swing.JOptionPane;

/**  ласс, описывающий рабочего зоопарка.
 * @see zoo#Zoo*/
public class Employee {
	
	/** ћетод, позвол€ющий кормить животное.
	 * @see animals#Elephant
	 * @see animals#Tiger
	 * @see animals#Ostrich
	 * @see animals#Flamingo*/
	public void feedTheAnimal(animals.AbstractAnimal ob) {
		JOptionPane.showMessageDialog(null, ob.setKind() + " " + ob.eat());
		ob.thanks();
	}
	
	/** ћетод, позвол€ющий чистить клетку.
	 * @see animals#Elephant
	 * @see animals#Tiger
	 * @see animals#Ostrich
	 * @see animals#Flamingo*/
	public void cleanTheCage(animals.AbstractAnimal ob) {
		JOptionPane.showMessageDialog(null, " летка номер " + ob.setNumber() + " убрана.");
	}
}
