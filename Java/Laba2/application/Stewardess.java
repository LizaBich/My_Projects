package application;

import javax.swing.JOptionPane;

/**Класс для описания стюардессы.
 * @see Crew*/
public class Stewardess extends Crew {
	
	/**Конструктор класса
	 * @see Crew
	 * @see Crew#Crew(String)
	 * @see Stewardess*/
	Stewardess() {
		super("Стюардесса");
	}
	
	/**Переопределённый метод, который выводит на экран сообщение.
	 * @see Stewardess
	 * @see Crew
	 * @see Crew#setCoffe()*/
	public void setCoffe() {
		JOptionPane.showMessageDialog(null, "Кофе:\n1)Каппучино\n2)Латте\n3)Эспрессо");
	}
	
	/**Переопределённый метод.
	 * @see Crew
	 * @see Crew#planeControle(int, Plane, float)
	 * @see Pilot
	 * @see Pilot#planeControle(int, Plane, float)*/
	public int planeControle(int a, Plane ob, float b) {
		return 0;
	}
}
