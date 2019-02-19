//TestFrame 可以关闭 

import java.awt.*;
import java.awt.event.*;
//import java.io.*;
public class TestFrameClose3 
{
	Frame f=new Frame("Window Can Be Closed");
	public static void main(String[] args)
	{
		TestFrameClose3 tf=new TestFrameClose3();
		tf.init();
	
	}
	public void init()        
	{
		Button btn=new Button("退出");
		Button btn2 = new Button("test2");
		MouseListener mml= new MyMouseListener();
		btn.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
	        {
              System.out.println(e.getActionCommand());
		      f.setVisible(false);
		      f.dispose();		
		      System.exit(0);   	      
	        }
		});//注册事件监听器对象
		btn.addMouseListener(mml);
		btn2.addMouseListener(mml);
	    Color mc = new Color(200, 0, 0);
        btn2.setBackground(mc);
        Font mf = new Font("sdfsa", Font.ITALIC, 30);
        btn2.setForeground(Color.WHITE);
        btn2.setFont(mf);
		btn.addMouseListener(new MyMouseListener2());
		f.add(btn);
		f.add(btn2, "North");
	//	f.setSize(300,300);
		f.pack();
		f.setVisible(true);
	}
	
	public void paint(Graphics g)
	{        
		
		System.out.println("paint() is called ");
 	   
	}
	
    class MyMouseListener extends MouseAdapter{
	  public void mouseEntered(MouseEvent e)
	  {
		System.out.println("mouse entered"+ e.paramString());
	  }
    }	
    	
    class MyMouseListener2 extends MouseAdapter{
	  public void mouseEntered(MouseEvent e)
	  {
		System.out.println("mouse entered 2");
	  }
    }
}
