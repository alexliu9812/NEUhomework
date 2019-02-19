//TestFrame.java

import java.awt.*;
import java.awt.event.*;
public class testFrame3
{
	public static void main(String[] args)
	{
		Frame f=new Frame("Test for Frame");
		f.add(new Button("OK"));
		//f.add(new Button("ok"), "North");
		//f.add(new Button("cancel"));
		f.setSize(300,300);
	    f.setVisible(true);
	    f.addWindowListener(new MyWindowListener());
	}
}

class MyWindowListener implements WindowListener {

 public void windowActivated(WindowEvent e) {
 }
      // 将 Window 设置为活动 Window 时调用。 
 public void windowClosed(WindowEvent e){
      System.out.println("Window is closed.");

 } 
         // 因对窗口调用 dispose 而将其关闭时调用。 
 public void windowClosing(WindowEvent e){
 	  System.out.println("Windown is closing");
 	  e.getWindow().setVisible(false);
      ((Window)e.getComponent()).dispose();
      System.exit(0);

 } 
         // 用户试图从窗口的系统菜单中关闭窗口时调用。 
 public void windowDeactivated(WindowEvent e) {
 }
          //当 Window 不再是活动 Window 时调用。 
 public void windowDeiconified(WindowEvent e){
 	System.out.println("Window is deiconfied.\n");
 } 
          //窗口从最小化状态变为正常状态时调用。 
 public void windowIconified(WindowEvent e){
 	System.out.println("Window is iconfied.\n");
 } 
    //      窗口从正常状态变为最小化状态时调用。 
 public void windowOpened(WindowEvent e){
 } 
 

	
}