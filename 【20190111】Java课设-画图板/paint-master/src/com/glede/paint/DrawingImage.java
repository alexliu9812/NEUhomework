package com.glede.paint;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.Vector;

/**
 * Created by Glede on 1/10/2019
 */
public class DrawingImage extends DrawingItem {
    private transient Image _image;
    private transient JFrame _imgObserver;
    private Rectangle _pos;
    public DrawingImage(Image image,Rectangle pos,JFrame imgObserver){
        this(image,pos,imgObserver,false);
    }
    public DrawingImage(Image image,Rectangle pos,JFrame imgObserver,boolean isPreview){
        super(Type.Í¼Ïñ,isPreview);
        _image=image;
        _pos=pos;
        _imgObserver=imgObserver;
        initResizePoint();
    }

    @Override
    public void reposition(Point pos) {
        _pos.x=pos.x;
        _pos.y=pos.y;
    }

    public void draw(Graphics g){
        Graphics2D graphics2D=(Graphics2D)g;
        graphics2D.drawImage(_image,_pos.x,_pos.y,_pos.width,_pos.height,_imgObserver);
    }

    @Override
    public Rectangle getBounds() {
        return _pos;
    }

    @Override
    public boolean contains(Point point) {
        return _pos.contains(point);
    }

    @Override
    protected Vector<Point> getResizePoints() {
        Vector<Point> points=new Vector<>();
        points.add(new Point(_pos.x,_pos.y));
        points.add(new Point(_pos.x+_pos.width,_pos.y+_pos.height));
        return points;
    }

    @Override
    public void resize(int resizePointRank, Point posTo) {
        switch (resizePointRank){
            case 0:
                _pos.x=posTo.x;
                _pos.y=posTo.y;
                break;
            case 1:
                int x=Math.min(_pos.x,posTo.x),y=Math.min(_pos.y,posTo.y),
                        disX=Math.abs(posTo.x-_pos.x),disY=Math.abs(posTo.y-_pos.y);
                _pos=new Rectangle(x,y,disX,disY);

        }
        resizePoint.reposition(null);
    }

    @Override
    public DrawingItem createPreview() {
        return new DrawingShape(selectedColor,
                new Rectangle(_pos.x,_pos.y,_pos.width,_pos.height),false,new BasicStroke(6f),true);
    }

    private void writeObject(ObjectOutputStream out) throws IOException {
        out.defaultWriteObject();
        ImageIO.write((BufferedImage)_image, "png", out); // png
    }

    private void readObject(ObjectInputStream in) throws IOException, ClassNotFoundException {
        in.defaultReadObject();
        _image=ImageIO.read(in);
        _imgObserver=Entry.getMainFormInstance();
    }
}
