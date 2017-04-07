package animals;

import javax.swing.JOptionPane;

/** �����, ����������� �������. ��������� 
 * ����� AbstractMammal
 * @see AbstractMammal*/
public class Tiger extends AbstractMammal {
	
	/**��� ���������*/
	private String kindofanimal;              
	/**����������� (������)*/
	public boolean strips;
	
	/**����������� ������.
	 * @see animals#AbstractMammal#AbstractMammal()*/
	public Tiger(String str, int a, int num) {
		super(str, a, num);
		this.strips = true;
		this.kindofanimal = "����";
	}
	
	public String eat() {
		this.getStatus(1);
		return super.setStatus();
	}
	
	public void thanks() {
		JOptionPane.showMessageDialog(null, "����� ��� ������������� (�����, �� ����� ������� ����).");
	}
	
	public String setKind() {
		return this.kindofanimal;
	}
	
	public String setEx() {
		return "������";
	}
	
	public void fun() {}
}
