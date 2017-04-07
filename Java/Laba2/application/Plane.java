package application;

import java.util.Stack;
import javax.swing.JOptionPane;

/**�����, ����������� ������*/
public class Plane {
	/**�������� �������*/
	private String name;
	/**������� �����*/
	private float weight;
	/**������, �� ������� ��������� ������*/
	private float height;		//������
	
	/**��������� �� �����
	 * @see Passenger*/
	public Stack<Passenger> paseng;
	/**����� �������
	 * @see Crew
	 * @see Pilot
	 * @see Stewardess*/
	public Crew crew[];
	
	/**�����, ������� ����� ��������� ���������� ���������*/
	private int pl;
	/**������������ ���������� ���� �� �����*/
	private int maxpl;

	/**����������� ������ Plane
	 * @see Plane
	*/
	Plane(String st, float a, int b, String str) {
		this.name = new String(st);
		paseng = new Stack<Passenger>();
		this.weight = a;
		this.height = 0;
		this.pl = b;
		this.maxpl = b;
		crew = new Crew[2];
		crew[0] = new Pilot(str);
		crew[1] = new Stewardess();
	}
	
	/**�����, ����������� ��������� ������
	 * @see Plane*/
	public void addHeight(float a) {
		this.height += a;
	}
	
	/**�����, ����������� ��������� ������
	 * @see Plane*/
	public void subHeight(float a) {
		this.height -= a;
	}
	
	/**����� ��� ���������� ���������
	 * @see Plane
	 * @see Passenger
	 * @see Passenger#entireToPlane(int)*/
	public int addPas() {
		if (this.pl == 0) {
			JOptionPane.showMessageDialog(null, "��������� ���� ���. �������� ���� ���������.");
			return 0;
		}
		int n = this.pl;
		Passenger ob = new Passenger();
		ob.entireToPlane(n);
		paseng.push(ob);
		this.pl--;
		return 0;
	}
	
	/**����� ��� �������� ���������
	 * @see Plane
	 * @see Passenger
	 * @see Passenger#exitFromPlane()*/
	public void deletePassenger() {
		if (this.pl == this.maxpl) return;
		Passenger ob = new Passenger();
		ob = paseng.pop();
		ob.exitFromPlane();
		this.pl++;
	}
	
	/**
	 * @see Plane
	 * @return ���������� �������� �������*/
	public String getName() {
		return this.name;
	}
	
	/**
	 * @see Plane
	 * @return ���������� ������� �����*/
	public float getWeight() {
		return this.weight;
	}
	
	/**
	 * @see Plane
	 * @return ���������� ��������� ��������� �����*/
	public int getPassenger() {
		return this.pl;
	}
	
	/**@see Plane
	 * @return ���������� ������������ ��-�� ����*/
	public int getMaxPassenger() {
		return this.maxpl;
	}
	
	/**@see Plane
	 * @return ���������� ������� ������*/
	public float setHeight() {
		return this.height;
	}
}
