package application;

import javax.swing.JOptionPane;

/**����� ��� �������� ����������.
 * @see Crew*/
public class Stewardess extends Crew {
	
	/**����������� ������
	 * @see Crew
	 * @see Crew#Crew(String)
	 * @see Stewardess*/
	Stewardess() {
		super("����������");
	}
	
	/**��������������� �����, ������� ������� �� ����� ���������.
	 * @see Stewardess
	 * @see Crew
	 * @see Crew#setCoffe()*/
	public void setCoffe() {
		JOptionPane.showMessageDialog(null, "����:\n1)���������\n2)�����\n3)��������");
	}
	
	/**��������������� �����.
	 * @see Crew
	 * @see Crew#planeControle(int, Plane, float)
	 * @see Pilot
	 * @see Pilot#planeControle(int, Plane, float)*/
	public int planeControle(int a, Plane ob, float b) {
		return 0;
	}
}
