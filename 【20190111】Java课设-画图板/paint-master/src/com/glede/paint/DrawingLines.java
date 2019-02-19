package com.glede.paint;

//import external.BetterBasicStroke;

import java.awt.*;
import java.awt.geom.Line2D;
import java.util.Vector;

/**
 * Created by Glede on 1/10/2019
 */
public class DrawingLines extends DrawingItem {
    private Color _color;
    private Vector<Point> _points;
    private Stroke _stroke;
    public DrawingLines(Color color,Vector<Point> points,Stroke stroke){
        this(color,points,stroke,false);
    }
    public DrawingLines(Color color,Vector<Point> points,Stroke stroke,boolean isPreview){
        super(Type.ÐÎ×´,isPreview);
        _color=color;
        if (isPreview)
            _points=points;
        else
            _points=(Vector<Point>) points.clone();
        _stroke= stroke;
        initResizePoint();
    }

    @Override
    public void resize(int resizePointRank, Point posTo) {
        _points.elementAt(resizePointRank).x=posTo.x;
        _points.elementAt(resizePointRank).y=posTo.y;

        resizePoint.reposition(null);
    }

    public void reposition(Point pos) {
        Point delta=new Point(pos.x-_points.elementAt(0).x,pos.y-_points.elementAt(0).y);
        for (Point x:_points){
            x.x+=delta.x;
            x.y+=delta.y;
        }
    }

    @Override
    protected Vector<Point> getResizePoints() {
        return (Vector<Point>) _points.clone();
    }

    @Override
    public Rectangle getBounds() {
        int minX = Integer.MAX_VALUE, minY = Integer.MAX_VALUE,
                maxX = 0, maxY = 0;
        for (Point p : _points) {
            maxX = Math.max(maxX, p.x);
            maxY = Math.max(maxY, p.y);
            minX = Math.min(minX, p.x);
            minY = Math.min(minY, p.y);
        }
        return new Rectangle(minX, minY, maxX - minX, maxY - minY);
    }

    @Override
    public boolean contains(Point point) {
        for (int i = 1; i < _points.size(); i++) {
            Line2D.Double lineNow = new Line2D.Double(
                    _points.elementAt(i - 1), _points.elementAt(i));
            if (lineNow.contains(point)) return true;
        }
        return false;
    }
    public void draw(Graphics g){
        Graphics2D graphics2D=(Graphics2D)g;
        graphics2D.setColor(_color);
        graphics2D.setStroke(_stroke);
        for(int i=1;i<_points.size();i++){
            Point x=_points.elementAt(i),y=_points.elementAt(i-1);
            graphics2D.drawLine(x.x,x.y,y.x,y.y);
        }
//        for(Point x:_points){
//            graphics2D.drawLine(x.x,x.y,x.x,x.y);
//        }
    }

    @Override
    public DrawingItem createPreview() {
        return new DrawingLines(selectedColor,_points,_stroke,true);
    }
}
