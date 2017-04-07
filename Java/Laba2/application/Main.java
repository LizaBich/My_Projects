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

/**������ ����� �������� ������ ����� � ����������*/
public class Main extends Application {
	
	/**���������� ��� ������������� ��������� ������*/
	/**�������� �������*/
	private TextField nameplane;
	/**����� ������� ��� �����*/
	private TextField plwg;
	/**������������ ���������� ����������*/
	private TextField mxpl;	
	/**��� ������*/
	private TextField pilot;
	
	/**��������� ����� ��� ������ Main
	 * @see Main*/
	@Override
	public void start(Stage primaryStage) {
		try {
			/*���� ��� ���������� ��������� � ���� �������*/
			GridPane root = new GridPane();
			/*������� ������� ��������� ����*/
			root.setAlignment(Pos.CENTER);
			/*���������� ����� ���������*/
			root.setHgap(10);
			/*���������� ����� ��������*/
			root.setVgap(10);
			/*������� �������� �� ���� (������,������,�����,�����)*/
			root.setPadding(new Insets(25,25,25,25));
			
			/*����������, ������������ "��������" ����*/
			Text scenetitle = new Text("������� ������");
			/*��������� "��������": �����, ������, �����*/
			scenetitle.setFont(Font.font("Tahoma", FontWeight.NORMAL, 20));
			root.add(scenetitle, 0, 0, 2, 1);
			
			Label nameofplane = new Label("�������� �������");
			root.add(nameofplane, 0, 1);
			
			nameplane = new TextField();
			root.add(nameplane, 1, 1);
			
			
			Label planeweight = new Label("������� �����");
			root.add(planeweight, 0, 2);
			
			plwg = new TextField();
			root.add(plwg, 1, 2);
			
			Label maximumplaces = new Label("����. ���-�� \n���������� ����");
			root.add(maximumplaces, 0, 3);
			
			mxpl = new TextField();
			root.add(mxpl, 1, 3);
			
			Label pilotname = new Label("��� ������");
			root.add(pilotname, 0, 4);
			
			pilot = new TextField();
			root.add(pilot, 1, 4);
			
			Button ok = new Button("Ok");
			HBox hbBtn = new HBox(10);    										// ��������������� ������, ������� ������ ��� ������������ 
																				//������, 10 - ������ (�������)
			hbBtn.setAlignment(Pos.BOTTOM_RIGHT);   							// ������ ������ ��������� �� ������� ������� ����
			hbBtn.getChildren().add(ok);       									// ��������� ������ � ���������������� �������
			root.add(hbBtn, 1, 5);
			/*��������� �������� ��� ������ OK*/
			ok.setOnAction(new EventHandler<ActionEvent>() {
				
				@Override
				public void handle(ActionEvent e) {
					Stage primaryStage = (Stage) ok.getScene().getWindow();  	// ��������� ������ ����
					primaryStage.close();
					
					Stage stage2 = new Stage();
					SecondWindow sw = new SecondWindow(nameplane.getText(), Float.valueOf(plwg.getText()), Integer.valueOf(mxpl.getText()), pilot.getText());
					stage2.setScene(sw.addElem());
					stage2.show();
				}
			});
			
			/*�������� �����*/
			Scene scene = new Scene(root,400,300);
			scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
			primaryStage.setScene(scene);
			primaryStage.show();
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	/**����������� ����� main, ���������� ��� ������� ������ Main
	 * @see Main
	*/
	public static void main(String[] args) {
		launch(args);
	}
}
