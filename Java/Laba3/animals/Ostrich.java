package animals;

import javax.swing.JOptionPane;

/** Класс, описывающий страуса. Расширяет 
 * класс AbstractMammal
 * @see AbstractMammal*/
public class Ostrich extends AbstractBird {
	
	/**Вид птицы*/
	private String kindofanimal;             
	
	/**Конструктор класса.
	 * @see animals#AbstractMammal#AbstractMammal()*/
	public Ostrich(String str, int a, int num) {
		super(str, a, num);
		this.kindofanimal = "Страус";
	}
	
	public String eat() {
		this.getStatus(1);
		return super.setStatus();
	}
	
	public void fly() {
		JOptionPane.showMessageDialog(null, "Очень смешно! Я не умею!");
	}
	
	public void thanks() {
		JOptionPane.showMessageDialog(null, "Благодарно машет головой.");
	}
	
	public String setKind() {
		return this.kindofanimal;
	}
	
	public String setEx() {
		return "Не летает";
	}
	
	public void fun() {}
}
