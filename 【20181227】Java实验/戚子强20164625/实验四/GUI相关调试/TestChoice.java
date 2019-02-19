import java.awt.*;
import java.awt.event.*;
public class TestChoice {
    Choice ch=new Choice();
    TestChoice()
	{
    	ch.add("choice1");
    	ch.add("choice2");
    	ch.add("choice3");
    	ch.addItemListener(new MyItemListener());
    	FlowLayout f1=new FlowLayout();
    	Frame f=new Frame("TestChoice");
    	f.setLayout(f1);
    	f.add(ch);
    	f.setBounds(0,0,200,100);
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
		new TestChoice();
	}
	
	class MyItemListener implements ItemListener
	{
	   public void itemStateChanged(ItemEvent e)
	   {
	   	   System.out.println(ch.getSelectedItem());
	   	   System.out.println(e.getItem());
	   	   
	   }
	}
}
