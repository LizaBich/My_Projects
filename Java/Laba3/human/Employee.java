package human;

import javax.swing.JOptionPane;

/** �����, ����������� �������� ��������.
 * @see zoo#Zoo*/
public class Employee {
	
	/** �����, ����������� ������� ��������.
	 * @see animals#Elephant
	 * @see animals#Tiger
	 * @see animals#Ostrich
	 * @see animals#Flamingo*/
	public void feedTheAnimal(animals.AbstractAnimal ob) {
		JOptionPane.showMessageDialog(null, ob.setKind() + " " + ob.eat());
		ob.thanks();
	}
	
	/** �����, ����������� ������� ������.
	 * @see animals#Elephant
	 * @see animals#Tiger
	 * @see animals#Ostrich
	 * @see animals#Flamingo*/
	public void cleanTheCage(animals.AbstractAnimal ob) {
		JOptionPane.showMessageDialog(null, "������ ����� " + ob.setNumber() + " ������.");
	}
}
