import java.awt.*;
import java.awt.event.*;
public class TestCardLayout {
	CardLayout c1=new CardLayout();
	Panel plCenter=new Panel();
	public static void main(String[] args) {
		new TestCardLayout().init();
	}
	public void init()
	{
		Frame f=new Frame("布局管理器");
		Panel plWest=new Panel();
		f.add(plWest,"West");
		f.add(plCenter);
		
		plWest.setLayout(new GridLayout(3,1));
		Button btnPrev=new Button("prev");
		plWest.add(btnPrev);
		Button btnNext=new Button("next");
		plWest.add(btnNext);
		Button btnThree=new Button("three");
		plWest.add(btnThree);
		
		plCenter.setLayout(c1);
		f.add(new Button("One"),"1");
		f.add(new Button("Two"),"North");
	    f.add(new Button("Three"),"3");
		f.add(new Button("Four"),"4");
		f.add(new Button("Five"),"5");
		
		class MyActionListener implements ActionListener
		{
			public void actionPerformed(ActionEvent e)
			{
				if(e.getActionCommand().equals("prev"))
					c1.previous(plCenter);
				else if(e.getActionCommand().equals("next"))
					c1.next(plCenter);
				else if(e.getActionCommand().equals("three"))
					c1.show(plCenter,"3");
			}
		}
		MyActionListener ma=new MyActionListener();
		btnPrev.addActionListener(ma);
		btnNext.addActionListener(ma);
		btnThree.addActionListener(ma);
		
		f.setSize(300,300);
		f.setVisible(true);
		f.addWindowListener(new WindowAdapter()
		{
			public void windowClosing(WindowEvent e)
			{
				System.exit(0);
			}
		});
	}
}
