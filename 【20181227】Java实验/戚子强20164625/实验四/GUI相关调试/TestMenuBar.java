import java.awt.*;
import java.awt.event.*;

public class TestMenuBar {
	MenuBar menubar=new MenuBar();
	Menu fileM=new Menu("File");
	Menu editM=new Menu("Edit");
	Menu toolsM=new Menu("Tools");
	Menu helpM=new Menu("Help");
	
	MenuItem fileMI1=new MenuItem("New");
	MenuItem fileMI2=new MenuItem("Open");
	MenuItem fileMI3=new MenuItem("Save");
	CheckboxMenuItem fileMI5=new CheckboxMenuItem("Quit",true);
	
    Menu filePrint=new Menu("print");
    MenuItem printM1=new MenuItem("preview");
    MenuItem printM2=new MenuItem("setting");
    
    TestMenuBar()
	{
    	FlowLayout f1=new FlowLayout();
    	
    	Frame f=new Frame("TestMenuBar");
    	f.setLayout(f1);
    	
    	menubar.add(fileM);
    	menubar.add(editM);
    	menubar.add(toolsM);
    	menubar.add(helpM);
    	
    	fileM.add(fileMI1);
    	fileM.add(fileMI2);
    	fileM.add(fileMI3);
    	
    	filePrint.add(printM1);
    	filePrint.add(printM2);
    	fileM.add(filePrint);
    	fileM.addSeparator();
    	fileM.add(fileMI5);
    	f.setMenuBar(menubar);
    	f.setBounds(0,0,250,200);
    	f.setVisible(true);
    	f.addWindowListener(new WindowAdapter()
    	{
    		public void windowClosing(WindowEvent e)
    		{
    			System.exit(0);
    		}
    	});
    	printM1.addActionListener(new MenuListener());
    	printM2.addActionListener(new MenuListener());
    	
	}
	public static void main(String[] args) {
		new TestMenuBar();
	}
}
class MenuListener implements ActionListener
{
	public void actionPerformed(ActionEvent e)
	{
		if(e.getActionCommand().equals("preview"))
		   System.out.println("preview");
		else if (e.getActionCommand().equals("setting"))
			System.out.println("setting");
	}
}
