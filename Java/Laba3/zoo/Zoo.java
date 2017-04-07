package zoo;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import javax.swing.JOptionPane;

/** �����, ����������� �������.*/
public class Zoo {
	
	/** �������� ��������.*/
	private String name;
	/** ���������, ���������� ��������.*/
	public ArrayList<animals.AbstractAnimal> animallist;
	/** ������� ��������.
	 * @see human#Employee*/
	public human.Employee employee;
	
	/** ����������� ������.
	 * @see Zoo
	 * @param str - �������� ��������*/
	public Zoo(String str) {
		this.name = str;
		this.employee = new human.Employee();
		this.animallist = new ArrayList<animals.AbstractAnimal>();
	}
	
	/** �����, ����������� � ��������� �����.
	 * @see animals#Elephant
	 * @param str - ��� �����.
	 * @param a - ������� �����.
	 * @param num - ����� �������.*/
	public void addElephant(String str, int a, int num) {
		animals.Elephant ob = new animals.Elephant(str, a, num);
		animals.AbstractAnimal pointer = ob;
		this.animallist.add(pointer);
	}
	
	/** �����, ����������� � ��������� �����.
	 * @see animals#Tiger
	 * @param str - ��� �����.
	 * @param a - ������� �����.
	 * @param num - ����� �������.*/
	public void addTiger(String str, int a, int num) {
		animals.Tiger ob = new animals.Tiger(str, a, num);
		animals.AbstractAnimal pointer = ob;
		this.animallist.add(pointer);
	}
	
	/** �����, ����������� � ��������� �������.
	 * @see animals#Ostrich
	 * @param str - ��� �������.
	 * @param a - ������� �������.
	 * @param num - ����� �������.*/
	public void addOstrich(String str, int a, int num) {
		animals.Ostrich ob = new animals.Ostrich(str, a, num);
		animals.AbstractAnimal pointer = ob;
		this.animallist.add(pointer);
	}
	
	/** �����, ����������� � ��������� ��������.
	 * @see animals#Flamingo
	 * @param str - ��� ��������.
	 * @param a - ������� ��������.
	 * @param num - ����� �������.*/
	public void addFlamingo(String str, int a, int num) {
		animals.Flamingo ob = new animals.Flamingo(str, a, num);
		animals.AbstractAnimal pointer = ob;
		this.animallist.add(pointer);
	}
	
	/** �����, �������� ��������� ��������.
	 * @see animals#AbstractAnimal
	 * @return ������ �������� ������ �� �����������.*/
	private animals.AbstractAnimal setRandomAnimal() {
		Random rand = new Random();
		int pos = 0;
		pos = rand.nextInt(this.animallist.size());
		return this.animallist.get(pos);
	}
	
	/** ������� �������� ����������.
	 * @see animals#AbstractAnimal
	 * @return ������ �������� ������ �� �����������.*/
	public animals.AbstractAnimal takeAVisitor() {
		return this.setRandomAnimal();
	}
}
