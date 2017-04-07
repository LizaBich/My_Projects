package animals;

import javax.swing.JOptionPane;

/** Класс, описывающий фламинго. Расширяет 
 * класс AbstractMammal
 * @see AbstractMammal*/
public class Flamingo extends AbstractBird {
	
	/**Вид птицы*/
	private String kindofanimal;            
	
	/**Конструктор класса.
	 * @see animals#AbstractMammal#AbstractMammal()*/
	public Flamingo(String str, int a, int num) {
		super(str, a, num);
		this.kindofanimal = "Фламинго";
	}
	
	public String eat() {
		this.getStatus(1);
		return super.setStatus();
	}
	
	public void fly() {
		JOptionPane.showMessageDialog(null, "Окай, секу. Сча полечу.");
	}
	
	public void thanks() {
		JOptionPane.showMessageDialog(null, "Исполняет танец благодарности.");
	}
	
	public String setKind() {
		return this.kindofanimal;
	}
	
	public String setEx() {
		return "Розовый";
	}
	
	public void fun() {}
}
