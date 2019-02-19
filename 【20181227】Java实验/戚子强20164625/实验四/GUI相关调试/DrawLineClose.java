import java.awt.*;
import java.awt.event.*;
public class DrawLineClose 
{
	Frame f=new Frame("DrawLine");
	public static void main(String[] args)
	{
		new DrawLineClose().init();
	}
	public void init()
	{
		f.setSize(300,300);
		f.setVisible(true);
		f.addWindowListener(new WindowAdapter()
		{
			public void windowClosing(WindowEvent e)
			{
				f.setVisible(false);
				f.dispose();
				System.exit(0);
			}
		});
		f.addMouseListener(new MouseAdapter()
		{
			int orgX;
			int orgY;
			public void mousePressed(MouseEvent e)
			{
				orgX=e.getX();
				orgY=e.getY();
			}
			public void mouseReleased(MouseEvent e)
			{
				Graphics g=f.getGraphics();
				g.setColor(Color.red);
				g.setFont(new Font("¡• È",Font.ITALIC|Font.BOLD,30));
				g.drawString(new String(orgX+","+orgY),orgX,orgY);
				g.drawString(new String(e.getX()+","+e.getY()),e.getX(),e.getY());
				g.drawLine(orgX,orgY,e.getX(),e.getY());
			}
		});
	}
}