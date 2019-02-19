import java.awt.*;
public class TestBorderLayout {

	public static void main(String[] args) {
		Frame f=new Frame("布局管理器");
		f.add(new Button("第一个按钮"),BorderLayout.NORTH);
		f.add(new Button("第二个按钮"),BorderLayout.EAST);
		f.add(new Button("第三个按钮"),BorderLayout.WEST);
		f.add(new Button("第四个按钮"),BorderLayout.SOUTH);
		f.setSize(300,300);
		f.setVisible(true);
	}
}

