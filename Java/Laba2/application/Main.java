package application;
	
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;

/**Данный класс является точкой входа в приложение*/
public class Main extends Application {
	
	/**Переменные для инициализации начальных данных*/
	/**Название самолёта*/
	private TextField nameplane;
	/**Масса самолёта при взлёте*/
	private TextField plwg;
	/**Максимальное количество пассажиров*/
	private TextField mxpl;	
	/**ФИО пилота*/
	private TextField pilot;
	
	/**Стартовый метод для класса Main
	 * @see Main*/
	@Override
	public void start(Stage primaryStage) {
		try {
			/*Слой для компоновки элементов в виде таблицы*/
			GridPane root = new GridPane();
			/*Задание позиции элементов слоя*/
			root.setAlignment(Pos.CENTER);
			/*Расстояние между столбцами*/
			root.setHgap(10);
			/*Расстояние между строками*/
			root.setVgap(10);
			/*Задание отступов от слоя (вверху,справа,снизу,слева)*/
			root.setPadding(new Insets(25,25,25,25));
			
			/*Переменная, отображающая "название" окна*/
			Text scenetitle = new Text("Введите данные");
			/*Параметры "названия": стиль, размер, шрифт*/
			scenetitle.setFont(Font.font("Tahoma", FontWeight.NORMAL, 20));
			root.add(scenetitle, 0, 0, 2, 1);
			
			Label nameofplane = new Label("Название самолёта");
			root.add(nameofplane, 0, 1);
			
			nameplane = new TextField();
			root.add(nameplane, 1, 1);
			
			
			Label planeweight = new Label("Взлётная масса");
			root.add(planeweight, 0, 2);
			
			plwg = new TextField();
			root.add(plwg, 1, 2);
			
			Label maximumplaces = new Label("Макс. кол-во \nпосадочных мест");
			root.add(maximumplaces, 0, 3);
			
			mxpl = new TextField();
			root.add(mxpl, 1, 3);
			
			Label pilotname = new Label("ФИО пилота");
			root.add(pilotname, 0, 4);
			
			pilot = new TextField();
			root.add(pilot, 1, 4);
			
			Button ok = new Button("Ok");
			HBox hbBtn = new HBox(10);    										// вспомогательный объект, который служит для выравнивания 
																				//кнопок, 10 - отступ (пиксели)
			hbBtn.setAlignment(Pos.BOTTOM_RIGHT);   							// кнопка буудет выравнена по правому нижнему краю
			hbBtn.getChildren().add(ok);       									// добавляем кнопку к вспомогательному объекту
			root.add(hbBtn, 1, 5);
			/*Обработка действия для кнопки OK*/
			ok.setOnAction(new EventHandler<ActionEvent>() {
				
				@Override
				public void handle(ActionEvent e) {
					Stage primaryStage = (Stage) ok.getScene().getWindow();  	// закрываем текщее окно
					primaryStage.close();
					
					Stage stage2 = new Stage();
					SecondWindow sw = new SecondWindow(nameplane.getText(), Float.valueOf(plwg.getText()), Integer.valueOf(mxpl.getText()), pilot.getText());
					stage2.setScene(sw.addElem());
					stage2.show();
				}
			});
			
			/*Создание сцены*/
			Scene scene = new Scene(root,400,300);
			scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
			primaryStage.setScene(scene);
			primaryStage.show();
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	/**Статический метод main, вызываемый при запуске класса Main
	 * @see Main
	*/
	public static void main(String[] args) {
		launch(args);
	}
}
