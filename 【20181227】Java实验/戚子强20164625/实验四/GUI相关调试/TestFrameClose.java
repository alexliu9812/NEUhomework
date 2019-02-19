//TestFrame 可以关闭 

import java.awt.*;
import java.awt.event.*;
public class TestFrameClose  
{
	Frame f=new Frame("Window Can Be Closed");
	public static void main(String[] args)
	{
		TestFrameClose tf=new TestFrameClose();
		tf.init();
	}
	public void init()   
	{
		Button btn=new Button("退出");
		btn.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e)
	       {
		  f.setVisible(false);
		   f.dispose();
		  System.exit(0);
	      }
		}
		
		);//注册事件监听器对象
	
		f.add(btn);
		f.setSize(300,300);
		f.setVisible(true);
	}
	

}