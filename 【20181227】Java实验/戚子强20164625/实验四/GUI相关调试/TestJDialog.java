import javax.swing.*;
import java.awt.event.*;
public class TestJDialog {

	public static void main(String[] args) {
		JOptionPane.showMessageDialog(null,"程序开始启动");
		String str=JOptionPane.showInputDialog(null,"输入你的姓名");
		while(!str.equals("neuneu"))
		{
			JOptionPane.showMessageDialog(null,"姓名有误，请重新输入");
			str=JOptionPane.showInputDialog(null,"输入你的姓名");
		}
		final JFrame f=new JFrame("TestJDialog");
		
		
		f.setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
		//f.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		f.addWindowListener(new WindowAdapter()
		{
			public void windowClosing(WindowEvent e)
			{
				int retval=JOptionPane.showConfirmDialog(f,"你真的要结束吗？","结束程序",JOptionPane.YES_NO_OPTION);
				if(retval==JOptionPane.YES_OPTION)
					System.exit(0);
			}
		});
		f.setSize(200,200);
		f.setVisible(true);
	}
}
