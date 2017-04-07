package application;

/**�����, ����������� ������
 * @see Crew*/
public class Pilot extends Crew{
	/**��� ������*/
	private String pilotname;
	
	/**����������� ������
	 * @see Crew
	 * @see Crew#Crew(String)
	 * @see Pilot
	*/
	Pilot(String str) {
		super("�����");
		this.pilotname = str;
	}
	
	/**����� ��� ���������� ��������. ��������������� ����������� 
	 * ����� ������ Crew
	 * @see Pilot
	 * @see Plane
	 * @see Plane#addHeight(float)
	 * @see Plane#subHeight(float)
	 * @see Crew
	 * @see Crew#planeControle(int, Plane, float)
	 * @param a - ���� ��� ����������� ��������
	 * @param ob - ������ ���� Plane
	 * @param b - ��������, �� ������� ����������� ������*/
	public int planeControle(int a, Plane ob, float b) {
		switch(a) {
		case 0: 
			ob.addHeight(b);
			break;
		case 1:
			ob.subHeight(b);
			break;
		}
		return 0;
	}
	
	/**��������������� ������������ ������.
	 * @see Crew
	 * @see Crew#setCoffe()*/
	public void setCoffe() {}
}
