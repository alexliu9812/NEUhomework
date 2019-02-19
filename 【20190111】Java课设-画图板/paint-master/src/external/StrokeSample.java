package external;
import javax.swing.*;
import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;
import java.awt.geom.Point2D;

public class StrokeSample extends JComponent implements ListCellRenderer {
    private Stroke stroke;
    private Dimension preferredSize;

    public StrokeSample(final Stroke stroke) {
        this.stroke = stroke;
        this.preferredSize = new Dimension(80, 18);
        setPreferredSize(this.preferredSize);
    }

    public Stroke getStroke() {
        return this.stroke;
    }


    public void setStroke(final Stroke stroke) {
        this.stroke = stroke;
        repaint();
    }

    public Dimension getPreferredSize() {
        return this.preferredSize;
    }

    public void paintComponent(final Graphics g) {

        final Graphics2D g2 = (Graphics2D) g;
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                RenderingHints.VALUE_ANTIALIAS_ON);
        final Dimension size = getSize();
        final Insets insets = getInsets();
        final double xx = insets.left;
        final double yy = insets.top;
        final double ww = size.getWidth() - insets.left - insets.right;
        final double hh = size.getHeight() - insets.top - insets.bottom;

        // calculate point one
        final Point2D one = new Point2D.Double(xx + 6, yy + hh / 2);
        // calculate point two
        final Point2D two = new Point2D.Double(xx + ww - 6, yy + hh / 2);
        // draw a circle at point one
        final Ellipse2D circle1 = new Ellipse2D.Double(one.getX() - 5,
                one.getY() - 5, 10, 10);
        final Ellipse2D circle2 = new Ellipse2D.Double(two.getX() - 6,
                two.getY() - 5, 10, 10);

        // draw a circle at point two
        g2.draw(circle1);
        g2.fill(circle1);
        g2.draw(circle2);
        g2.fill(circle2);

        // draw a line connecting the points
        final Line2D line = new Line2D.Double(one, two);
        if (this.stroke != null) {
            g2.setStroke(this.stroke);
            g2.draw(line);
        }

    }

    public Component getListCellRendererComponent(JList list, Object value,
                                                  int index, boolean isSelected, boolean cellHasFocus) {
        if (value instanceof Stroke) {
            setStroke((Stroke) value);
        } else {
            setStroke(null);
        }
        return this;
    }
}