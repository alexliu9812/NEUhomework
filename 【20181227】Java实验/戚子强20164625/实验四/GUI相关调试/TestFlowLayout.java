import java.awt.*;
public class TestFlowLayout {

	public static void main(String[] args) {
		Frame f=new Frame("布局管理器");
		f.setLayout(new FlowLayout(FlowLayout.LEFT));
	//	f.setLayout(new FlowLayout(FlowLayout.LEFT, 50,100));
		f.add(new Button("第一个按钮"));
		f.add(new Button("第二个按钮"));
		f.add(new Button("第三个按钮"));
		f.add(new Button("第四个按钮"));
		f.setSize(300,300);
		f.setVisible(true);
	}
}