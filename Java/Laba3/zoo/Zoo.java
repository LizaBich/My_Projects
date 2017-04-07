package zoo;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import javax.swing.JOptionPane;

/** Класс, описывающий зоопарк.*/
public class Zoo {
	
	/** Название зоопарка.*/
	private String name;
	/** Коллекция, содержащая животных.*/
	public ArrayList<animals.AbstractAnimal> animallist;
	/** Рабочий зоопарка.
	 * @see human#Employee*/
	public human.Employee employee;
	
	/** Конструктор класса.
	 * @see Zoo
	 * @param str - название зоопарка*/
	public Zoo(String str) {
		this.name = str;
		this.employee = new human.Employee();
		this.animallist = new ArrayList<animals.AbstractAnimal>();
	}
	
	/** Метод, добавляющий в коллекцию слона.
	 * @see animals#Elephant
	 * @param str - пол слона.
	 * @param a - возраст слона.
	 * @param num - номер вольера.*/
	public void addElephant(String str, int a, int num) {
		animals.Elephant ob = new animals.Elephant(str, a, num);
		animals.AbstractAnimal pointer = ob;
		this.animallist.add(pointer);
	}
	
	/** Метод, добавляющий в коллекцию тигра.
	 * @see animals#Tiger
	 * @param str - пол тигра.
	 * @param a - возраст тигра.
	 * @param num - номер вольера.*/
	public void addTiger(String str, int a, int num) {
		animals.Tiger ob = new animals.Tiger(str, a, num);
		animals.AbstractAnimal pointer = ob;
		this.animallist.add(pointer);
	}
	
	/** Метод, добавляющий в коллекцию страуса.
	 * @see animals#Ostrich
	 * @param str - пол страуса.
	 * @param a - возраст страуса.
	 * @param num - номер вольера.*/
	public void addOstrich(String str, int a, int num) {
		animals.Ostrich ob = new animals.Ostrich(str, a, num);
		animals.AbstractAnimal pointer = ob;
		this.animallist.add(pointer);
	}
	
	/** Метод, добавляющий в коллекцию фламинго.
	 * @see animals#Flamingo
	 * @param str - пол фламинго.
	 * @param a - возраст фламинго.
	 * @param num - номер вольера.*/
	public void addFlamingo(String str, int a, int num) {
		animals.Flamingo ob = new animals.Flamingo(str, a, num);
		animals.AbstractAnimal pointer = ob;
		this.animallist.add(pointer);
	}
	
	/** Метод, выдающий рандомное животное.
	 * @see animals#AbstractAnimal
	 * @return ссылку базового класса на производный.*/
	private animals.AbstractAnimal setRandomAnimal() {
		Random rand = new Random();
		int pos = 0;
		pos = rand.nextInt(this.animallist.size());
		return this.animallist.get(pos);
	}
	
	/** Передаёт животное посетителю.
	 * @see animals#AbstractAnimal
	 * @return ссылку базового класса на производный.*/
	public animals.AbstractAnimal takeAVisitor() {
		return this.setRandomAnimal();
	}
}
