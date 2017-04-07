package animals;

/** Класс, описывающий млекопитающее.
 * Расширяет класс AbstractAnimal
 * @see animals#AbstractAnimal*/
abstract class AbstractMammal extends AbstractAnimal {
	
	/** Лапы*/
	protected int paws;
	/** Класс млекопитающего*/
	protected String animalclass; 
	
	/** Конструктор класса.
	 * @see animals#AbstractAnimal#AbstractAnimal()*/
	AbstractMammal(String str, int a, int num) {
		super(str, a, num);
		this.paws = 4;
		this.animalclass = "Млекопитающее";
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
