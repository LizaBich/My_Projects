package animals;

import javax.swing.JOptionPane;

/** Класс, описывающий страуса. Расширяет 
 * класс AbstractMammal
 * @see AbstractMammal*/
public class Tiger extends AbstractMammal {
	
	/**Вид животного*/
	private String kindofanimal;              
	/**Особенность (полосы)*/
	public boolean strips;
	
	/**Конструктор класса.
	 * @see animals#AbstractMammal#AbstractMammal()*/
	public Tiger(String str, int a, int num) {
		super(str, a, num);
		this.strips = true;
		this.kindofanimal = "Тигр";
	}
	
	public String eat() {
		this.getStatus(1);
		return super.setStatus();
	}
	
	public void thanks() {
		JOptionPane.showMessageDialog(null, "Издаёт рык благодарности (шутка, он хочет схавать тебя).");
	}
	
	public String setKind() {
		return this.kindofanimal;
	}
	
	public String setEx() {
		return "Полосы";
	}
	
	public void fun() {}
}
