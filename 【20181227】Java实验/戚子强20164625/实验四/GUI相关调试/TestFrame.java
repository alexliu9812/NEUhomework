//TestFrame.java

import java.awt.*;
public class TestFrame
{
	public static void main(String[] args)
	{
		Frame f=new Frame("Test for Frame");
		f.add(new Button("OK"));
		//f.add(new Button("ok"), "North");
		//f.add(new Button("cancel"));
		f.setSize(300,300);
		
	
		f.setVisible(true);
	}
}