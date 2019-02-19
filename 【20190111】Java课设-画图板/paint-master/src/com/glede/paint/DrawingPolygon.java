package com.glede.paint;

import java.awt.*;
import java.util.Vector;

/**
 * Created by Glede on 1/10/2019
 */
public class DrawingPolygon extends DrawingItem {
    private Color _color;
    private Polygon _shape;
    private Stroke _stroke;
    private boolean _fill;
    boolean _isPolygon;
    public DrawingPolygon(Color color,Polygon shape,boolean fill,Stroke stroke){
        this(color,shape,fill,stroke,false);
    }
    public DrawingPolygon(Color color,Polygon shape,boolean fill,Stroke stroke,boolean isPreview){
        super(Type.¶à±ßÐÎ,isPreview);
        _color=color;
        _shape=shape;
        _fill=fill;
        _stroke=fill?null:stroke;
        initResizePoint();
    }

    public void reposition(Point pos) {
        Point delta=new Point(pos.x-_shape.xpoints[0],pos.y-_shape.ypoints[0]);
        for(int i=0;i<_shape.npoints;i++){
            _shape.xpoints[i]+=delta.x;
            _shape.ypoints[i]+=delta.y;
        }
    }
    public void draw(Graphics g){
        Graphics2D graphics2D=(Graphics2D)g;
        graphics2D.setColor(_color);
        if(_fill) {
            graphics2D.fillPolygon(_shape);
        }else {
            graphics2D.setStroke(_stroke);
            graphics2D.drawPolygon(_shape);
        }
    }

    @Override
    public void resize(int resizePointRank, Point posTo) {
        _shape.xpoints[resizePointRank]=posTo.x;
        _shape.ypoints[resizePointRank]=posTo.y;
        resizePoint.reposition(null);
    }

    @Override
    public boolean contains(Point point) {
        return _shape.contains(point);
    }

    @Override
    public Rectangle getBounds() {
        _shape.invalidate();
        return _shape.getBounds();
    }

    @Override
    protected Vector<Point> getResizePoints() {
        Vector<Point> points=new Vector<>();
        for(int i=0;i<_shape.npoints;i++){
            points.add(new Point(_shape.xpoints[i],_shape.ypoints[i]));
        }
        return points;
    }

    @Override
    public DrawingItem createPreview() {
        return new DrawingPolygon(selectedColor,_shape,_fill,_stroke,true);
    }
}
