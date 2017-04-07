package animals;

/** �����, ����������� �������������.
 * ��������� ����� AbstractAnimal
 * @see animals#AbstractAnimal*/
abstract class AbstractMammal extends AbstractAnimal {
	
	/** ����*/
	protected int paws;
	/** ����� ��������������*/
	protected String animalclass; 
	
	/** ����������� ������.
	 * @see animals#AbstractAnimal#AbstractAnimal()*/
	AbstractMammal(String str, int a, int num) {
		super(str, a, num);
		this.paws = 4;
		this.animalclass = "�������������";
	}
	
	/**@see animals#AbstractAnimal#setStatus()*/
	public String setStatus() {
		return super.setStatus();
	}
	
	public String eat() {return null;}
	public void thanks() {}
	public String setKind() {
		return null;
	}
	
	public String setEx() {
		return null;
	}
	
}
