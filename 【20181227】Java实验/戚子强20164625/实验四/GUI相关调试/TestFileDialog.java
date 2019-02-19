import java.awt.*;
import java.awt.event.*;
public class TestFileDialog {
	Frame f=new Frame();
	FileDialog fg1=new FileDialog(f,"保存",FileDialog.SAVE);
    FileDialog fg2=new FileDialog(f,"打开",FileDialog.LOAD);
    Button b1=new Button("保存");
	Button b2=new Button("打开");
	TestFileDialog()
	{
		FlowLayout fl=new FlowLayout();
		f.setLayout(fl);
		f.add(b1);
		f.add(b2);
		f.setBounds(0,0,400,200);
		b1.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				fg1.setVisible(true);
		    	System.out.println(fg1.getFile());
			}
		});
		b2.addActionListener(new ActionListener()
				{
					public void actionPerformed(ActionEvent e)
					{
						fg2.setVisible(true);
					}
				});
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
		new TestFileDialog();
	}
}
