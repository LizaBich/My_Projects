package human;

import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;

/** �����, ����������� ����������*/
public class Viewer {
	
	/** �����, ����������� ����������� ���������� � ��������.
	 * @see animals#Elephant
	 * @see animals#Tiger
	 * @see animals#Ostrich
	 * @see animals#Flamingo*/
	public void seeTheAnimal(animals.AbstractAnimal ob, Display display) {
		Shell shell = new Shell(display);
		shell.setSize(300, 200);
		GridLayout lay = new GridLayout(2, true);
		GridData data = new GridData();
		data.horizontalAlignment = GridData.CENTER;
		data.grabExcessHorizontalSpace = true;
		data.horizontalSpan = 2;
		
		Label title1 = new Label(shell, SWT.NONE);
		title1.setText("���� �������������� ���!");
		title1.setLayoutData(data);
		
		Label title = new Label(shell, SWT.NONE);
		title.setText("����. � ��������");
		title.setLayoutData(data);
		
		new Label(shell, SWT.NONE).setText("���:");
		
		new Label(shell, SWT.NONE).setText(ob.setKind());
		
		new Label(shell, SWT.NONE).setText("���:");
		
		new Label(shell, SWT.NONE).setText(ob.setSex());
		
		new Label(shell, SWT.NONE).setText("�������:");
		
		new Label(shell, SWT.NONE).setText(ob.setAge());
		
		new Label(shell, SWT.NONE).setText("����� �������:");
		
		new Label(shell, SWT.NONE).setText(ob.setNumber());
		
		new Label(shell, SWT.NONE).setText("�����������:");
		
		new Label(shell, SWT.NONE).setText(ob.setEx());
		
		shell.setLayout(lay);
		shell.open();
		while (shell != null && !shell.isDisposed()) {
			
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
		if (!display.isDisposed()) display.update();
		return;
	}
}