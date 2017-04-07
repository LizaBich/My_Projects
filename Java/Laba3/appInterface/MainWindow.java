package appInterface;

import javax.swing.JOptionPane;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;

/** Класс для интерфейса.*/
public class MainWindow {
	
	/** Кнопка для просмотра инфы о животном.*/
	static Button look;
	/** Кнопка, чтобы покормить.*/
	static Button feedAnimal;
	/** Кнопка, чтобы почистить клетку.*/
	static Button clean;
	/** Кнопка, чтобы добавить новое животное.*/
	static Button add;
	/** Объект типа Zoo
	 * @see zoo#Zoo*/
	static zoo.Zoo myzoo;
	/** Общее количество животных.*/
    static int number = 0;
    static Label label;
    /** Лэйбл для указания количества слонов.*/
    static Label elephant;
    /** Количество слонов.*/
    static int numelephant = 0;
    /** Лэйбл для указания количества тигров.*/
    static Label tiger;
    /** Количество тигров.*/
    static int numtiger = 0;
    /** Лэйбл для указания количества страусов.*/
    static Label ostrich;
    /** Количество страусов.*/
    static int numostrich = 0;
    /** Лэйбл для указания количества фламинго.*/
    static Label flamingo;
    /** Количество фламинго.*/
    static int numflamingo = 0;
    private static Display display;
    /** Объект посетитель.*/
    private static human.Viewer viever;
    
    static Combo combo;
    static String ansex;
    
	/** Метод, формирующий главное окно.
	 * @see MainWindow
	 * @return Возвращает окно.*/
	public static Shell ConfigureShell() {
		final Shell shell = new Shell(display, SWT.SHELL_TRIM | SWT.RESIZE);
		shell.setText("Welcome to the Zoo!");
		shell.setSize(375, 250);
		
		GridLayout lay = new GridLayout(3, true);
		GridData gridData = new GridData();
		gridData.horizontalAlignment = GridData.FILL;
		gridData.grabExcessHorizontalSpace = true;
		
		//1
		Label lab1 = new Label(shell, SWT.NONE);
		lab1.setText("Посетитель:");
		
		//2
		new Label(shell, SWT.NONE).setText("Всего зверей в зоопарке:");
		
		//3
		label = new Label(shell, SWT.NONE);
		label.setText(Integer.toString(number));
		
		//4
		look = new Button(shell, SWT.PUSH);
		look.setText("Посмотреть на зверя");
		look.setLayoutData(gridData);
		look.addListener(SWT.Selection, new Listener() {

			@Override
			public void handleEvent(Event event) {
				if (myzoo.animallist.size() == 0) {
					JOptionPane.showMessageDialog(null, "Извините, но на данный момент зоопарк пуст");
				}
				else {
					viever.seeTheAnimal(myzoo.takeAVisitor(), display);
				}
			}
			
		});
		
		;
		//5
		new Label(shell, SWT.NONE).setText("Слонов в зоопарке:");
		
		//6
		elephant = new Label(shell, SWT.NONE);
		elephant.setText(Integer.toString(numelephant));
		
		//7
		new Label(shell, SWT.NONE);
		
		//8
		new Label(shell, SWT.NONE).setText("Тигров в зоопарке:");
		
		//9
		tiger = new Label(shell, SWT.NONE);
		tiger.setText(Integer.toString(numtiger));
		
		//10
		new Label(shell, SWT.NONE).setText("Работник:");
		
		//11
		new Label(shell, SWT.NONE).setText("Фламинго в зоопарке:");
		
		//12
		flamingo = new Label(shell, SWT.NONE);
		flamingo.setText(Integer.toString(numflamingo));
		
		//13
		feedAnimal = new Button(shell, SWT.PUSH);
		feedAnimal.setText("Кормить животное");
		feedAnimal.setLayoutData(gridData);
		feedAnimal.addListener(SWT.Selection, new Listener() {

			@Override
			public void handleEvent(Event event) {
				if (myzoo.animallist.size() == 0) {
					JOptionPane.showMessageDialog(null, "Извините, но на данный момент зоопарк пуст");
				}
				else {
					myzoo.employee.feedTheAnimal(myzoo.takeAVisitor());
				}
			}
		});
		
		//14
		new Label(shell, SWT.NONE).setText("Страусов в зоопарке:");
		
		//15
		ostrich = new Label(shell, SWT.NONE);
		ostrich.setText(Integer.toString(numostrich));
		
		//16
		clean = new Button(shell, SWT.PUSH);
		clean.setText("Чистить клетки");
		clean.setLayoutData(gridData);
		clean.addListener(SWT.Selection, new Listener() {

			@Override
			public void handleEvent(Event event) {
				if (myzoo.animallist.size() == 0) {
					JOptionPane.showMessageDialog(null, "Извините, но на данный момент зоопарк пуст");
				}
				else {
					myzoo.employee.cleanTheCage(myzoo.takeAVisitor());
				}
			}
		});
		
		//17, 18, 19, 20, 21
		new Label(shell, SWT.NONE);
		new Label(shell, SWT.NONE);
		new Label(shell, SWT.NONE);
		new Label(shell, SWT.NONE);
		new Label(shell, SWT.NONE);
		
		//22
		add = new Button(shell, SWT.PUSH);
		add.setText("Добавить животное");
		add.setLayoutData(gridData);
		add.addListener(SWT.Selection, new Listener() {

			@Override
			public void handleEvent(Event event) {
				Shell newshell = new Shell(display);
				MainWindow.addAnimal(newshell);
			}
			
		});
		
		//23, 24
		new Label(shell, SWT.NONE);
		new Label(shell, SWT.NONE);
		
		shell.setLayout(lay);
		return shell;
	}
	
	/** Метод, создающий новое окно для добавления животного.
	 * @see MainWindow*/
	public static void addAnimal(Shell newshell) {
		newshell.setText("Add new animal.");
		newshell.setSize(250, 150);
		GridLayout lay = new GridLayout(2, true);
		GridData gridData = new GridData();
		gridData.horizontalAlignment = GridData.FILL;
		gridData.grabExcessHorizontalSpace = true;
		
		new Label(newshell, SWT.NONE).setText("Вид: ");
		
		Text kindof = new Text(newshell, SWT.SINGLE | SWT.BORDER);
		kindof.setLayoutData(gridData);
		
		new Label(newshell, SWT.NONE).setText("Пол: ");
		
		
		String[] data = {"Самец", "Самка"};
		combo = new Combo(newshell, SWT.DROP_DOWN | SWT.SINGLE | SWT.H_SCROLL);
		combo.removeAll();
		for (int i = 0; i < 2; i++) {
			combo.add(data[i]);
		}
		combo.addListener(SWT.Selection, new Listener() {

			@Override
			public void handleEvent(Event event) {
				ansex = combo.getText();
			}
			
		});
		
		new Label(newshell, SWT.NONE).setText("Возраст: ");
		
		Text ageof = new Text(newshell, SWT.SINGLE | SWT.BORDER);
		ageof.setLayoutData(gridData);
		
		Button done = new Button(newshell, SWT.PUSH);
		done.setText("Готово");
		done.addSelectionListener(new SelectionAdapter() {

			@Override
			public void widgetSelected(SelectionEvent event) {
				if (kindof.getText().compareTo("Слон") == 0) {
					myzoo.addElephant(ansex, Integer.parseInt(ageof.getText()), myzoo.animallist.size() + 1);
					numelephant++;
					elephant.setText(Integer.toString(numelephant));
				}
				if (kindof.getText().compareTo("Тигр") == 0) {
					myzoo.addTiger(ansex, Integer.parseInt(ageof.getText()), myzoo.animallist.size() + 1);
					numtiger++;
					tiger.setText(Integer.toString(numtiger));
				}
				if (kindof.getText().compareTo("Фламинго") == 0) {
					myzoo.addFlamingo(ansex, Integer.parseInt(ageof.getText()), myzoo.animallist.size() + 1);
					numflamingo++;
					flamingo.setText(Integer.toString(numflamingo));
				}
				if (kindof.getText().compareTo("Страус") == 0) {
					myzoo.addOstrich(ansex, Integer.parseInt(ageof.getText()), myzoo.animallist.size() + 1);
					numostrich++;
					ostrich.setText(Integer.toString(numostrich));
				}
				number++;
				label.setText(Integer.toString(number));
				newshell.close();
			}
		});
		
		newshell.setLayout(lay);
		newshell.open();
		while (newshell != null && !newshell.isDisposed()) {
			
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
		if (!display.isDisposed()) display.update();
	}

	/** Главный метод, с которого стартует приложение.
	 * @see MainWindow*/
	public static void main(String[] args) {
		display = new Display();
		myzoo = new zoo.Zoo("Минский зоопарк");
		viever = new human.Viewer();
		Shell shell = ConfigureShell();
		shell.open();
		while (!shell.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
	}

}
