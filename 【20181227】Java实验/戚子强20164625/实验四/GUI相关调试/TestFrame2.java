//TestFrame.java

import java.awt.*;
import java.awt.event.*;

public class TestFrame2
{
	public static void main(String[] args)
	{
		Frame f=new Frame("Test for Frame");
		f.add(new Button("ok"));
		f.setSize(300,300);
		f.setVisible(true);
		f.addWindowListener(new MyWindowListener());
	}
}
class MyWindowListener extends WindowAdapter
{
	public void windowClosing(WindowEvent e)
	{
		e.getWindow().setVisible(false);
		((Window)e.getComponent()).dispose();
		System.exit(0);
	}

	public void windowDeiconified(WindowEvent e){
		  System.out.println("Deiconified is called");
		}
	public void windowIconified(WindowEvent e){
		  System.out.println("Iconified is called");
		}

}