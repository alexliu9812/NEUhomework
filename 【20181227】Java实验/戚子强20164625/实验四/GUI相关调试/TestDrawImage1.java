import java.awt.*;
import java.awt.event.*;
public class TestDrawImage1
{
	public static void main(String args[])
	{
		Frame f=new Frame("DrawImage");
	//	Image img=f.getToolkit().getImage("d:\\javakejian05\\xmas.jpg");
		
	//	f.getGraphics().drawImage(img,0,0,f);
	
		f.setSize(300,300);
		f.setVisible(true);
		
		f.addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent e)
			{
				System.exit(0);
			}
		});
		
		//Frame f=new Frame("DrawImage");
	   Image img=f.getToolkit().getImage("d:\\javakejian05\\xmas.jpg");
		f.getGraphics().drawImage(img,0,0,f); 
	}
}