package application;

/**����������� ����� ��� �������*/
abstract class Crew {
	
	/**��������� ����� �������*/
	public String work;
	
	/**����������� ������
	 * @see Crew*/
	Crew(String st) {
		this.work = st;
	}
	
	/**���������� �����
	 * @see Crew*/
	abstract void setCoffe();
	/**����������� �����
	 * @see Crew*/
	abstract int planeControle(int a, Plane ob, float b);
}
