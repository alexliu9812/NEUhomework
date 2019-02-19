//TestFrame 可以关闭 

import java.awt.*;
import java.awt.event.*;
public class TestFrameClose2
{
	Frame f=new Frame("Window Can Be Closed");
	public static void main(String[] args)
	{
		TestFrameClose2 tf=new TestFrameClose2();
		tf.init();
	}
	public void init()        
	{
		Button btn=new Button("退出");
		btn.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
	        {
		      f.setVisible(false);
		      f.dispose();		
		      System.exit(0);   	      
	        }
		});//注册事件监听器对象
		MouseListener mml = new MyMouseListener();
		MouseListener mml2 = new MyMouseListener2();
	//	Font f1 = new Font("仿宋体", Font.ITALIC, 50);
	//	Color c1 = new Color (250, 0, 0);
		Button btn2 = new Button("new button");
	//	btn2.setFont(f1);
	//	btn.setFont(f1);
	//	btn2.setBackground(c1);
	//	btn2.setForeground(Color.cyan);
		btn2.addMouseListener(mml);
		btn.addMouseListener(mml);
		btn.addMouseListener(mml2);
		f.add(btn);
		f.add(btn2, "North");
		f.setSize(300,300);
		f.setVisible(true);
	}
	
	  class MyMouseListener extends MouseAdapter{
	  public void mouseEntered(MouseEvent e)
	  {
	  	
		System.out.println("mouse 1 entered"+ e.getSource().toString());
	  }
	  }
	  
	  class MyMouseListener2 extends MouseAdapter{
	  public void mouseEntered(MouseEvent e)
	  {
	  	
		System.out.println("mouse 2 entered"+ e.getSource().toString());
	  }
      }	
	
}