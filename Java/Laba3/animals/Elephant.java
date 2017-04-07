package animals;

import javax.swing.JOptionPane;

/** Класс, описывающий слона. Расширяет 
 * класс AbstractMammal
 * @see AbstractMammal*/
public class Elephant extends AbstractMammal {
	
	/**Вид животного*/
	private String kindofanimal;           
	/**Особенность (хобот)*/
	private boolean trunk;				
	
	/**Конструктор класса.
	 * @see animals#AbstractMammal#AbstractMammal()*/
	public Elephant(String str, int a, int num) {
		super(str, a, num);
		this.trunk = true;
		this.kindofanimal = "Слон";
	}
	
	public String eat() {
		this.getStatus(1);
		return super.setStatus();
	}
	
	public void thanks() {
		JOptionPane.showMessageDialog(null, "Тянется хоботом, чтобы поблагодарить \n(А ну иди сюда, тварь!!!).");
	}
	
	public String setKind() {
		return this.kindofanimal;
	}
	
	public String setEx() {
		return "Хобот";
	}
	
	public void fun() {}
}