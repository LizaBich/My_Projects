package animals;

/** јбстрактный класс, описывающий любого обитател€ зоопарка.*/
public abstract class AbstractAnimal {
	
	/** “ело*/
	protected boolean body;						
	/** ѕол обитател€.*/
	protected String sex;					
	/** —татус (накормлен или нет).*/
	protected int status;						
	/** ¬озраст обитател€.*/
	protected int age;							
	/** Ќомер вольера.*/
	protected int number; 						
	
	/**  онструктор.
	 * @param str - пол обитател€
	 * @param a - возраст обитател€
	 * @param num - номер вольера*/
	AbstractAnimal(String str, int a, int num) {
		this.body = true;
		this.age = a;
		this.status = 0;
		this.sex = str;
		this.number = num;
	}
	
	/**@return пол обитател€.*/
	public String setSex() {
		return this.sex;
	}
	
	/**@return статус обитател€.*/
	public String setStatus() {
		if (this.status == 0) return "голоден";
		return "накормлен";
	}
	
	/** «адаЄт статус обитател€.
	 * @return значение статуса*/
	public int getStatus(int c) {
		this.status = c;
		return 0;
	}
	
	/**@return вид животного.*/
	public String setKind() {
		return null;
	}
	
	/**@return особенность обитател€.*/
	public String setEx() {
		return null;
	}
	
	/**@return возраст обитател€.*/
	public String setAge() {
		return Integer.toString(this.age);
	}
	
	/**@return номер вольера.*/
	public String setNumber() {
		return Integer.toString(this.number);
	}
	
	/** ќбитатель кушает.
	 * @return какую-то строку.*/
	public String eat() {
		return null;
	}
	
	/** Ѕлагодарность.*/
	public void thanks() {}
	
	abstract void fun();
}
