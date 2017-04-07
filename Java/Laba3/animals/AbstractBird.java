package animals;

/** Абстрактный класс, описывающий птиц.
 *  Расширяет класс AbstractAnimal
 *  @see animals#AbstractAnimal*/
abstract class AbstractBird extends AbstractAnimal{
	
	/**Крылья*/
	protected int wings;
	/**Класс птицы*/
	protected String animalclass;
	
	/**Конструктор класса
	 * @see animals#AbstractAnimal#AbstractAnimal()*/
	AbstractBird(String str, int a, int num) {
		super(str, a, num);
		this.wings = 2;
		this.animalclass = "Птица";
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
