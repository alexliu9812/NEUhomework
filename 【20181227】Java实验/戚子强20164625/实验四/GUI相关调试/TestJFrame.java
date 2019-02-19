import javax.swing.*;
public class TestJFrame {

	public static void main(String[] args) {
		JFrame f=new JFrame("JFrame");
		f.getContentPane().add(new JButton("ok"));
		f.setSize(300,300);
		f.setVisible(true);
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
}
