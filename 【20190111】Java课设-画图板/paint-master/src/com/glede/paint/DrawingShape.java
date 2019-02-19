package com.glede.paint;


import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.util.Vector;

/**
 * Created by Glede on 1/10/2019
 */
public class DrawingShape extends DrawingItem {
    private Color _color;
    private Shape _shape;
    private Stroke _stroke;
    private boolean _fill;
    public DrawingShape(Color color,Shape shape,boolean fill,Stroke stroke,boolean isPreview){
        super(Type.–Œ◊¥,isPreview);
        init(color,shape,fill,stroke);
    }
    public DrawingShape(Color color,Shape shape,boolean fill,Stroke stroke){
        this(color,shape,fill,stroke,false);
    }
    private void  init(Color color,Shape shape,boolean fill,Stroke stroke){
        _color=color;
        _shape=shape;
        _fill=fill;
        _stroke=fill?null:stroke;
        initResizePoint();
        if(_shape instanceof Rectangle){
            setType(Type.æÿ–Œ);
        }
        if(_shape instanceof Ellipse2D.Double){
            setType(Type.‘≤–ŒÕ÷‘≤);
        }
        if(_shape instanceof Ellipse2D.Float){
            setType(Type.‘≤–ŒÕ÷‘≤);
        }
    }
    public void reposition(Point pos){
        if(_shape instanceof Rectangle){
            Rectangle rectangle=(Rectangle)_shape;
            rectangle.x= pos.x;
            rectangle.y=pos.y;
            _shape=rectangle;
        }
        if(_shape instanceof Ellipse2D.Double){
            Ellipse2D.Double oval=(Ellipse2D.Double) _shape;
            oval.x= pos.x;
            oval.y=pos.y;
            _shape=oval;
        }
        if(_shape instanceof Ellipse2D.Float){
            Ellipse2D.Float oval=(Ellipse2D.Float) _shape;
            oval.x= pos.x;
            oval.y=pos.y;
            _shape=oval;
        }
    }

    @Override
    public Rectangle getBounds() {
        return _shape.getBounds();
    }

    @Override
    public boolean contains(Point point) {
        return _shape.contains(point);
    }

    @Override
    protected Vector<Point> getResizePoints() {
        Vector<Point> points=new Vector<>();
        if(_shape instanceof Rectangle){
            Rectangle rectangle=(Rectangle)_shape;
            points.add(new Point(rectangle.x,rectangle.y));
            points.add(new Point(rectangle.x+rectangle.width,rectangle.y+rectangle.height));
        }
        if(_shape instanceof Ellipse2D.Double){
            Ellipse2D.Double oval=(Ellipse2D.Double) _shape;
            points.add(new Point((int)oval.x,(int)oval.y));
            points.add(new Point((int)(oval.x+oval.width),(int) (oval.y+oval.height)));
        }
        if(_shape instanceof Ellipse2D.Float){
            Ellipse2D.Float oval=(Ellipse2D.Float) _shape;
            points.add(new Point((int)oval.x,(int)oval.y));
            points.add(new Point((int)(oval.x+oval.width),(int) (oval.y+oval.height)));
        }
        return points;
    }
    @Override
    public void resize(int resizePointRank, Point posTo) {
        switch (resizePointRank){
            case 0:
                if(_shape instanceof Rectangle){
                    Rectangle rectangle=(Rectangle)_shape;
                    rectangle.x=posTo.x;
                    rectangle.y=posTo.y;
                }
                if(_shape instanceof Ellipse2D.Double){
                    Ellipse2D.Double oval=(Ellipse2D.Double) _shape;
                    oval.x=posTo.x;
                    oval.y=posTo.y;
                }
                if(_shape instanceof Ellipse2D.Float){
                    Ellipse2D.Float oval=(Ellipse2D.Float) _shape;
                    oval.x=posTo.x;
                    oval.y=posTo.y;
                }
                break;
            case 1:

                if(_shape instanceof Rectangle){
                    Rectangle rectangle=(Rectangle)_shape;
                    int x=Math.min(rectangle.x,posTo.x),y=Math.min(rectangle.y,posTo.y),
                            disX=Math.abs(posTo.x-rectangle.x),disY=Math.abs(posTo.y-rectangle.y);
                    _shape=new Rectangle(x,y,disX,disY);

                }
                if(_shape instanceof Ellipse2D.Double){
                    Ellipse2D.Double oval=(Ellipse2D.Double) _shape;
                    Double x=Math.min(oval.x,posTo.x),y=Math.min(oval.y,posTo.y),
                            disX=Math.abs(posTo.x-oval.x),disY=Math.abs(posTo.y-oval.y);
                    _shape=new Ellipse2D.Double(x,y,disX,disY);
                }
                if(_shape instanceof Ellipse2D.Float){
                    Ellipse2D.Float oval=(Ellipse2D.Float) _shape;
                    Float x=Math.min(oval.x,posTo.x),y=Math.min(oval.y,posTo.y),
                            disX=Math.abs(posTo.x-oval.x),disY=Math.abs(posTo.y-oval.y);
                    _shape=new Ellipse2D.Float(x,y,disX,disY);
                }
                break;
        }
        resizePoint.reposition(null);
    }

    public void draw(Graphics g){
//        getResizePoint().setShow(true);
        Graphics2D graphics2D=(Graphics2D)g;
        graphics2D.setColor(_color);
        if(_fill) {
            graphics2D.fill(_shape);
        }else {
            graphics2D.setStroke(_stroke);
            graphics2D.draw(_shape);
        }
    }

    @Override
    public DrawingItem createPreview() {
        return new DrawingShape(selectedColor,_shape,_fill,_stroke,true);
    }
}
