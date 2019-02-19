import javax.swing.*;
public class TestJScrollPane {
    TestJScrollPane()
	{
    	JFrame f=new JFrame("TestPane");
    	JScrollPane sp=new JScrollPane();
    	JTextArea ta=new JTextArea("",10,50);
    	sp.getViewport().setView(ta);
    	f.getContentPane().add(sp);
    	f.setSize(200,200);
    	f.setVisible(true);
    	f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	public static void main(String[] args) {
		new TestJScrollPane();
	}
}