package com.glede.paint;

import java.awt.*;
import java.util.Vector;

public class ResizePoint extends DrawingItem {
    Vector<Point> points;
    DrawingItem item;
    boolean show;
    private final double radius = 10;

    @Override
    public Rectangle getBounds() {
        return null;
    }

    @Override
    public boolean contains(Point point) {
        return false;
    }

    private static final Stroke dash = new SerializableStroke(1.5f,
            SerializableStroke.CAP_BUTT,
            SerializableStroke.JOIN_ROUND,
            1f, new float[]{15, 10,},
            0f);

    private static final Stroke ordinary=new SerializableStroke();

    private static final Color colorWhite = new Color(1.0f, 1.0f, 1.0f, 0.4f);
    private static final Color colorBlack = new Color(0.0f, 0.0f, 0.0f, 0.4f);

    public ResizePoint(DrawingItem itemRef) {
        super(Type.调整, true);
        show = false;
        points = itemRef.getResizePoints();
        item = itemRef;
    }

    void setShow(boolean show) {
        this.show = show;
    }

    void setItem(DrawingItem itemRef) {
        points = itemRef.getResizePoints();
        item = itemRef;
    }

    public ResizePoint() {
        super(Type.调整, true);
    }

    public boolean valid() {
        return points != null && item != null;
    }

    @Override
    public void reposition(Point point) {
        if (point == null) {
            points = item.getResizePoints();
        } else {
            Point delta = new Point(point.x - points.elementAt(0).x,
                    point.y - points.elementAt(0).y);
            for (Point x : points) {
                x.x += delta.x;
                x.y += delta.y;
            }
        }
    }

    @Override
    public void resize(int resizePointRank, Point posTo) {
        reposition(null);
    }

    public DrawingItem getItem() {
        return item;
    }

    public int selected(Point point) {
        for (int i = 0; i < points.size(); i++) {
            double a = point.x - points.elementAt(i).x, b = point.y - points.elementAt(i).y;
            a = a * a;
            b = b * b;
            if (a + b <= radius * radius) {
                return i;
            }
        }
        return -1;
    }
    private void setDrawColor(Graphics2D graphics2D,boolean white){
        if (white) {
            if (show)
                graphics2D.setColor(Color.WHITE);
            else
                graphics2D.setColor(colorWhite);
        }
        else {
            if (show) {
                graphics2D.setColor(Color.BLACK);
            } else {
                graphics2D.setColor(colorBlack);
            }
        }

    }
    @Override
    public void draw(Graphics g) {
        Graphics2D graphics2D = (Graphics2D) g;
        graphics2D.setStroke(new BasicStroke(1));
        for (int i = 1; i < points.size(); i++) {
            Point x = points.elementAt(i - 1), y = points.elementAt(i);
            setDrawColor(graphics2D,true);
            graphics2D.setStroke(ordinary);
            graphics2D.drawLine(x.x, x.y, y.x, y.y);
            setDrawColor(graphics2D,false);
            graphics2D.setStroke(dash);
            graphics2D.drawLine(x.x, x.y, y.x, y.y);
        }
        for (Point point : points) {
            setDrawColor(graphics2D,true);
            graphics2D.fillOval(point.x - (int) radius, point.y - (int) radius,
                    (int) radius * 2, (int) radius * 2);
            setDrawColor(graphics2D,false);
            graphics2D.drawOval(point.x - (int) radius, point.y - (int) radius,
                    (int) radius * 2, (int) radius * 2);
        }
    }

    @Override
    protected Vector<Point> getResizePoints() {
        return null;
    }

    @Override
    public DrawingItem createPreview() {
        return null;
    }
}
