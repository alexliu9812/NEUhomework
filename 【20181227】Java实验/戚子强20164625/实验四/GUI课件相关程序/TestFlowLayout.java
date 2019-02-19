
import java.awt.*;
public class TestFlowLayout {

    public static void main(String[] args) {
        Frame f=new Frame("FlowLayout");
        f.setLayout(new
                FlowLayout(FlowLayout.LEFT));
        f.add(new Button("第一个按钮"));
        f.add(new Button("第二个按钮"));
        f.add(new Button("第三个按钮"));
        f.add(new Button("第四个按钮"));
        f.setSize(300,300);
        f.setVisible(true);
    }
}
