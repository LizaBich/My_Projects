package animals;

import javax.swing.JOptionPane;

/** �����, ����������� �����. ��������� 
 * ����� AbstractMammal
 * @see AbstractMammal*/
public class Elephant extends AbstractMammal {
	
	/**��� ���������*/
	private String kindofanimal;           
	/**����������� (�����)*/
	private boolean trunk;				
	
	/**����������� ������.
	 * @see animals#AbstractMammal#AbstractMammal()*/
	public Elephant(String str, int a, int num) {
		super(str, a, num);
		this.trunk = true;
		this.kindofanimal = "����";
	}
	
	public String eat() {
		this.getStatus(1);
		return super.setStatus();
	}
	
	public void thanks() {
		JOptionPane.showMessageDialog(null, "������� �������, ����� ������������� \n(� �� ��� ����, �����!!!).");
	}
	
	public String setKind() {
		return this.kindofanimal;
	}
	
	public String setEx() {
		return "�����";
	}
	
	public void fun() {}
}