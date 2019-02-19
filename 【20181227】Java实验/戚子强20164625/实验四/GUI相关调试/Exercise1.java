import java.awt.*;
import java.awt.event.*;
public class Exercise1 {
  Frame f=new Frame("Exercise");
  private int i=1;
	public static void main(String[] args) {
		new Exercise1().init();
	}
	public void init()
	{
		final Button btn=new Button();
		f.add(btn);
		f.setSize(300,300);
		f.setVisible(true);
		final Graphics g=btn.getGraphics();
		btn.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				
				g.setColor(Color.blue);
				g.setFont(new Font("宋体",Font.ITALIC,20));
				//g.clearRect(85,90,200,200);
				g.drawString("按键第"+(i++)+"次",85,90);
			}
		});
		
		f.addWindowListener(new WindowAdapter()
		{
			public void windowClosing(WindowEvent e)
			{
				f.setVisible(false);
				f.dispose();
				System.exit(0);
			}
		});
	}
}
