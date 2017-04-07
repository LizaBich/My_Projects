package application;

/**Класс, описывающий пилота
 * @see Crew*/
public class Pilot extends Crew{
	/**ФИО пилота*/
	private String pilotname;
	
	/**Конструктор класса
	 * @see Crew
	 * @see Crew#Crew(String)
	 * @see Pilot
	*/
	Pilot(String str) {
		super("Пилот");
		this.pilotname = str;
	}
	
	/**Метод для управления самолётом. Переопределённый абстрактный 
	 * метод класса Crew
	 * @see Pilot
	 * @see Plane
	 * @see Plane#addHeight(float)
	 * @see Plane#subHeight(float)
	 * @see Crew
	 * @see Crew#planeControle(int, Plane, float)
	 * @param a - флаг для определения операции
	 * @param ob - объект типа Plane
	 * @param b - значение, на которое увеличиваем высоту*/
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
	
	/**Переопределение абстрактного метода.
	 * @see Crew
	 * @see Crew#setCoffe()*/
	public void setCoffe() {}
}
