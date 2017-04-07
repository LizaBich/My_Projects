package animals;

/** ����������� �����, ����������� ������ ��������� ��������.*/
public abstract class AbstractAnimal {
	
	/** ����*/
	protected boolean body;						
	/** ��� ���������.*/
	protected String sex;					
	/** ������ (��������� ��� ���).*/
	protected int status;						
	/** ������� ���������.*/
	protected int age;							
	/** ����� �������.*/
	protected int number; 						
	
	/** �����������.
	 * @param str - ��� ���������
	 * @param a - ������� ���������
	 * @param num - ����� �������*/
	AbstractAnimal(String str, int a, int num) {
		this.body = true;
		this.age = a;
		this.status = 0;
		this.sex = str;
		this.number = num;
	}
	
	/**@return ��� ���������.*/
	public String setSex() {
		return this.sex;
	}
	
	/**@return ������ ���������.*/
	public String setStatus() {
		if (this.status == 0) return "�������";
		return "���������";
	}
	
	/** ����� ������ ���������.
	 * @return �������� �������*/
	public int getStatus(int c) {
		this.status = c;
		return 0;
	}
	
	/**@return ��� ���������.*/
	public String setKind() {
		return null;
	}
	
	/**@return ����������� ���������.*/
	public String setEx() {
		return null;
	}
	
	/**@return ������� ���������.*/
	public String setAge() {
		return Integer.toString(this.age);
	}
	
	/**@return ����� �������.*/
	public String setNumber() {
		return Integer.toString(this.number);
	}
	
	/** ��������� ������.
	 * @return �����-�� ������.*/
	public String eat() {
		return null;
	}
	
	/** �������������.*/
	public void thanks() {}
	
	abstract void fun();
}
