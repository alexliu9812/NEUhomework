import java.awt.*;
import java.awt.event.*;
public class TestPane {
    TestPane()
	{
    	Frame f=new Frame("TestPane");
    	ScrollPane sp=new ScrollPane();
    	TextArea ta=new TextArea("",10,50,TextArea.SCROLLBARS_NONE);
    	sp.add(ta);
    	f.add(sp);
    	f.setSize(200,200);
    	f.setVisible(true);
    	f.addWindowListener(new WindowAdapter()
    	{
    		public void windowClosing(WindowEvent e)
    		{
    			System.exit(0);
    		}
    	});
	}
	public static void main(String[] args) {
		new TestPane();
	}
}
