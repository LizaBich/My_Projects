package animals;

/** ����������� �����, ����������� ����.
 *  ��������� ����� AbstractAnimal
 *  @see animals#AbstractAnimal*/
abstract class AbstractBird extends AbstractAnimal{
	
	/**������*/
	protected int wings;
	/**����� �����*/
	protected String animalclass;
	
	/**����������� ������
	 * @see animals#AbstractAnimal#AbstractAnimal()*/
	AbstractBird(String str, int a, int num) {
		super(str, a, num);
		this.wings = 2;
		this.animalclass = "�����";
	}
	
	public String setStatus() {
		return super.setStatus();
	}
	
	public String eat() {return null;}
	public void thanks() {}
	abstract void fly();
	public String setKind() {return null;}
	
	public String setEx() {
		return null;
	}
}
