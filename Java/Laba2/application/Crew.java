package application;

/**Абстрактный класс для экипажа*/
abstract class Crew {
	
	/**Должность члена экипажа*/
	public String work;
	
	/**Конструктор класса
	 * @see Crew*/
	Crew(String st) {
		this.work = st;
	}
	
	/**Абстрактый метод
	 * @see Crew*/
	abstract void setCoffe();
	/**Абстрактный метод
	 * @see Crew*/
	abstract int planeControle(int a, Plane ob, float b);
}
