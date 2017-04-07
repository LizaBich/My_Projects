package animals;

import javax.swing.JOptionPane;

/** �����, ����������� �������. ��������� 
 * ����� AbstractMammal
 * @see AbstractMammal*/
public class Ostrich extends AbstractBird {
	
	/**��� �����*/
	private String kindofanimal;             
	
	/**����������� ������.
	 * @see animals#AbstractMammal#AbstractMammal()*/
	public Ostrich(String str, int a, int num) {
		super(str, a, num);
		this.kindofanimal = "������";
	}
	
	public String eat() {
		this.getStatus(1);
		return super.setStatus();
	}
	
	public void fly() {
		JOptionPane.showMessageDialog(null, "����� ������! � �� ����!");
	}
	
	public void thanks() {
		JOptionPane.showMessageDialog(null, "���������� ����� �������.");
	}
	
	public String setKind() {
		return this.kindofanimal;
	}
	
	public String setEx() {
		return "�� ������";
	}
	
	public void fun() {}
}
