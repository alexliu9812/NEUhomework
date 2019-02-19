import java.awt.*;
import java.awt.event.*;
public class DrawLineBuf extends Frame
{
	Image oimg=null;
	Graphics og=null;
    public static void main(String[] args)
    {
    	new DrawLineBuf().init();
    }
    public void init()
    {
    	setSize(300,300);
    	setVisible(true);
    	Dimension d=getSize();
    	oimg=createImage(d.width,d.height);
    	og=oimg.getGraphics();
    	addMouseListener(new MouseAdapter()
    	{
    		int orgX;
    		int orgY;
    		public void mousePressed(MouseEvent  e)
    		{
    			orgX=e.getX();
    			orgY=e.getY();
            } 
    		
    		public void mouseReleased(MouseEvent e)
    		{
    			Graphics g=getGraphics();
    			g.setColor(Color.red);
    			g.setFont(new Font("¡• È",Font.ITALIC|Font.BOLD,30));
    			g.drawString(new String(orgX+","+orgY),orgX,orgY);
    			g.drawString(new String(e.getX()+","+e.getY()),e.getX(),e.getY());
    			g.drawLine(orgX,orgY,e.getX(),e.getY());
    			og.setColor(Color.red);
    			og.setFont(new Font("¡• È",Font.ITALIC|Font.BOLD,30));
    			og.drawString(new String(orgX+","+orgY),orgX,orgY);
    			og.drawString(new String(e.getX()+","+e.getY()),e.getX(),e.getY());
    			og.drawLine(orgX,orgY,e.getX(),e.getY());
    		}
    	});
    	addWindowListener(new WindowAdapter()
    	{
    		public void windowClosing(WindowEvent e)
    		{
    			((Window)e.getSource()).dispose();
    			System.exit(0);
    		}
    	});
    }
    public void paint(Graphics g)
    {
  	if(oimg!=null)
     	g.drawImage(oimg,0,0,this);
    }
}