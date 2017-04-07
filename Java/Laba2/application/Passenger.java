package application;

/**Класс для описания пассажира. Включается в класс типа Plane
 * @see Plane*/
public class Passenger {
	 /**Место пассажира в самолёте*/
	private int place;
	
	/**Конструктор класса Passenger
	 * @see Passenger*/
	Passenger() {
		this.place = 0;
	}
	
	/**Метод для определения места на борту
	 * @param a - незанятое место
	 * @see Passenger
	 * @see Passenger#exitFromPlane()*/
	public void entireToPlane(int a) {
		this.place = a;
	}
	
	/**Метод, обнуляющий номер места при удалении
	 * @see Passenger
	 * @see Passenger#antireToPlane(int)*/
	public void exitFromPlane() {
		this.place = 0;
	}
}
