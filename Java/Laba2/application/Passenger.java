package application;

/**����� ��� �������� ���������. ���������� � ����� ���� Plane
 * @see Plane*/
public class Passenger {
	 /**����� ��������� � �������*/
	private int place;
	
	/**����������� ������ Passenger
	 * @see Passenger*/
	Passenger() {
		this.place = 0;
	}
	
	/**����� ��� ����������� ����� �� �����
	 * @param a - ��������� �����
	 * @see Passenger
	 * @see Passenger#exitFromPlane()*/
	public void entireToPlane(int a) {
		this.place = a;
	}
	
	/**�����, ���������� ����� ����� ��� ��������
	 * @see Passenger
	 * @see Passenger#antireToPlane(int)*/
	public void exitFromPlane() {
		this.place = 0;
	}
}
