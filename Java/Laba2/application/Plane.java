package application;

import java.util.Stack;
import javax.swing.JOptionPane;

/**Класс, описывающий самолёт*/
public class Plane {
	/**Название самолёта*/
	private String name;
	/**Взлётная масса*/
	private float weight;
	/**Высота, на которой находится самолёт*/
	private float height;		//высота
	
	/**Пассажиры на борту
	 * @see Passenger*/
	public Stack<Passenger> paseng;
	/**Члены экипажа
	 * @see Crew
	 * @see Pilot
	 * @see Stewardess*/
	public Crew crew[];
	
	/**Место, которое будет присвоено очередному пассажиру*/
	private int pl;
	/**Максимальное количество мест на борту*/
	private int maxpl;

	/**Конструктор класса Plane
	 * @see Plane
	*/
	Plane(String st, float a, int b, String str) {
		this.name = new String(st);
		paseng = new Stack<Passenger>();
		this.weight = a;
		this.height = 0;
		this.pl = b;
		this.maxpl = b;
		crew = new Crew[2];
		crew[0] = new Pilot(str);
		crew[1] = new Stewardess();
	}
	
	/**Метод, позволяющий увеличить высоту
	 * @see Plane*/
	public void addHeight(float a) {
		this.height += a;
	}
	
	/**Метод, позволяющий уменьшить высоту
	 * @see Plane*/
	public void subHeight(float a) {
		this.height -= a;
	}
	
	/**Метод для добавления пассажира
	 * @see Plane
	 * @see Passenger
	 * @see Passenger#entireToPlane(int)*/
	public int addPas() {
		if (this.pl == 0) {
			JOptionPane.showMessageDialog(null, "Свободных мест нет. Приносим свои извинения.");
			return 0;
		}
		int n = this.pl;
		Passenger ob = new Passenger();
		ob.entireToPlane(n);
		paseng.push(ob);
		this.pl--;
		return 0;
	}
	
	/**Метод для удаления пассажира
	 * @see Plane
	 * @see Passenger
	 * @see Passenger#exitFromPlane()*/
	public void deletePassenger() {
		if (this.pl == this.maxpl) return;
		Passenger ob = new Passenger();
		ob = paseng.pop();
		ob.exitFromPlane();
		this.pl++;
	}
	
	/**
	 * @see Plane
	 * @return Возвращает название самолёта*/
	public String getName() {
		return this.name;
	}
	
	/**
	 * @see Plane
	 * @return Возвращает взлётную массу*/
	public float getWeight() {
		return this.weight;
	}
	
	/**
	 * @see Plane
	 * @return Возвращает очередное незанятое место*/
	public int getPassenger() {
		return this.pl;
	}
	
	/**@see Plane
	 * @return Возвращает максимальное ко-во мест*/
	public int getMaxPassenger() {
		return this.maxpl;
	}
	
	/**@see Plane
	 * @return Возвращает текущую высоту*/
	public float setHeight() {
		return this.height;
	}
}
