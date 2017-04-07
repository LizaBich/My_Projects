package application;

import javax.swing.JOptionPane;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Orientation;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.FlowPane;
import javafx.scene.layout.GridPane;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.stage.Stage;

/**Класс, позволяющий работать с основным окном*/
public class SecondWindow {
	
	
	private Label nameofplane;
	private Label planeweight;
	private Label maxpassenger;
	private Label pilotname;
	private Label currentpas;
	private Button plcontrole;
	private Button addpassenger;
	private Button deletepassenger;
	private Button callstewardess;
	
	/**Свойсто - самолёт, на котором летим*/
	private Plane plane;
	
	/**Конструктор класса, в который передаются параметры, введённые в начальном окне
	 * @see SecondWindow*/
	SecondWindow(String st, float a, int b, String str) {
		
		plane = new Plane(st, a, b, str);
		
		nameofplane = new Label();
		planeweight = new Label();
		maxpassenger = new Label();
		pilotname = new Label();
		currentpas = new Label();
		
		plcontrole = new Button("Управление самолётом");
		plcontrole.setPrefSize(150, 10);
		plcontrole.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent event) {
				plainControl();
			}
		});
		
		addpassenger = new Button("Добавить пассажира");
		addpassenger.setPrefSize(150, 10);
		addpassenger.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent ev) {
				plane.addPas();
				currentpas.setText(Integer.toString(plane.getMaxPassenger() - plane.getPassenger()));
			}
		});
		
		deletepassenger = new Button("Удалить пассажира");
		deletepassenger.setPrefSize(150, 10);
		deletepassenger.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent eve) {
				plane.deletePassenger();
				currentpas.setText(Integer.toString(plane.getMaxPassenger() - plane.getPassenger()));
			}
		});
		
		
		callstewardess = new Button("Стюардесса");
		callstewardess.setPrefSize(150, 10);
		callstewardess.setOnAction(new EventHandler<ActionEvent>() {

			@Override
			public void handle(ActionEvent a) {
				plane.crew[1].setCoffe();
			}
		});
		
		nameofplane.setText(st);
		planeweight.setText(Float.toString(a));
		maxpassenger.setText(Integer.toString(b));
		pilotname.setText(str);
		currentpas.setText(Integer.toString(plane.getPassenger() - plane.getPassenger()));
		
	}
	
	/**Метод класса SecondWindow, помогающий расположить элементы
	 * @see SecondWindow
	 * @retun Возвращает сцену, на которой размещены элементы*/
	public Scene addElem() {
		
		FlowPane mainpane = new FlowPane();
		mainpane.setPadding(new Insets(25,25,25,25));
		mainpane.setAlignment(Pos.CENTER);
		mainpane.setOrientation(Orientation.VERTICAL);
		
		mainpane.getChildren().add(this.infoBar1());
		
		FlowPane but = new FlowPane();
		but.setAlignment(Pos.CENTER);
		but.setVgap(10);
		but.setHgap(10);
		but.getChildren().add(plcontrole);
		but.getChildren().add(addpassenger);
		but.getChildren().add(deletepassenger);
		but.getChildren().add(callstewardess);
		
		mainpane.getChildren().add(but);
		
		Scene scene = new Scene(mainpane,400,300);
		scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
		
		return scene;
	}
	
	/**Метод класса SecondWindow, заполняющий информационное поле
	 * @see SecondWindow
	 * @see SecondWindow#addElem()
	 * @return Возвращает слой в виде таблицы, который размещается на главном слое
	*/
	private GridPane infoBar1() {
		GridPane gp = new GridPane();
		gp.setAlignment(Pos.CENTER);
		gp.setHgap(10);  // пробелы между строками
		gp.setVgap(20);  // и столбцами
		gp.setPadding(new Insets(0,25,25,0));	// пространство вокру сетки (вверху,справа,снизу,слева)
		
		Text title1 = new Text("Инфо о рейсе.");
		title1.setFont(Font.font("Tahoma", FontWeight.NORMAL, 20));   // задание стиля, размера и шрифта
		gp.add(title1, 0, 0);   // 0 - столбец, 0 - строка, 2 - промежуток между столбцами, 1 - промежуток между строками
		
		gp.add(new Label("Название:"), 0, 1);
		gp.add(nameofplane, 1, 1);
		gp.add(new Label("ФИО пилота:"), 2, 1);
		gp.add(pilotname, 3, 1);
		
		gp.add(new Label("Макс. кол-во \nпассажиров:"), 0, 2);
		gp.add(maxpassenger, 1, 2);
		
		gp.add(new Label("Текущее кол-во \nпассажиров:"), 2, 2);
		gp.add(currentpas, 3, 2);
		
		gp.add(new Label("Взлётная масса:"), 0, 3);
		gp.add(planeweight, 1, 3);
		
		return gp;
	}
	
	/**Метод, вызываемый при нажатии на кнопку "Управление самолётом".
	 * @see SecondWindow#SecondWindow()
	*/
	private void plainControl() {
		Stage stg = new Stage();
		Label planeheight = new Label();
		planeheight.setText(Float.toString(plane.setHeight()));
		
		Button but1 = new Button("Набрать высоту");
		but1.setOnAction(new EventHandler<ActionEvent>() {
			
			@Override
			public void handle(ActionEvent event) {
				plane.crew[0].planeControle(0, plane, 100);
				planeheight.setText(Float.toString(plane.setHeight()));
			}
		});
		
		Button but2 = new Button("Потерять высоту");
		but2.setOnAction(new EventHandler<ActionEvent>() {
			
			@Override
			public void handle(ActionEvent event) {
				if (plane.setHeight() == 0) {
					JOptionPane.showMessageDialog(null, "Нельзя уменьшить высоту!");
					return;
				}
				plane.crew[0].planeControle(1, plane, 100);
				planeheight.setText(Float.toString(plane.setHeight()));
			}
		});
		
		FlowPane st = new FlowPane();
		st.setAlignment(Pos.CENTER);
		st.setHgap(10);  // пробелы между строками
		st.setVgap(20);  // и столбцами
		st.setOrientation(Orientation.VERTICAL);
		
		Text title1 = new Text("Управление самолётом");
		title1.setFont(Font.font("Tahoma", FontWeight.NORMAL, 20));   // задание стиля, размера и шрифта
		st.getChildren().add(title1);   // 0 - столбец, 0 - строка, 2 - промежуток между столбцами, 1 - промежуток между строками
		
		st.getChildren().add(new Label("Высота увеличивается и уменьшается на 100 м. при нажатии\nТекущая высота:"));
		st.getChildren().add(planeheight);
		
		FlowPane st1 = new FlowPane();
		st1.setAlignment(Pos.CENTER);
		st1.setHgap(10);  // пробелы между строками
		st1.setVgap(20);  // и столбцами
		st1.getChildren().add(but1);
		st1.getChildren().add(but2);
		
		st.getChildren().add(st1);
		
		Scene scene = new Scene(st,450,300);
		scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
		stg.setScene(scene);
		stg.show();
	}
	
}
