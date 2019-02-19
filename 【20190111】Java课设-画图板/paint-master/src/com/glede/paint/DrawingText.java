package com.glede.paint;

import java.awt.*;
import java.util.Vector;

/**
 * Created by Glede on 1/10/2019
 */
public class DrawingText extends DrawingItem {
    private String text;
    private Point pos;
    private Font font;
    private Color color;
    public DrawingText(String text, Point pos,Font font,Color color){
        this(text,pos,font,color,false);
    }
    public DrawingText(String text, Point pos,Font font,Color color,boolean isPreview){
        super(Type.ÎÄ×Ö,isPreview);
        this.text=text;
        this.font=font;
        this.pos=pos;
        this.color=color;
        initResizePoint();
    }
    public void draw(Graphics g){
        Graphics2D graphics2D=(Graphics2D )g;
        graphics2D.setFont(font);
        graphics2D.setColor(color);
        graphics2D.drawString(text,pos.x,pos.y);
    }

    @Override
    public boolean contains(Point point) {
        return false;
    }

    @Override
    public Rectangle getBounds() {
        int sizeY = font.getSize();
        int sizeX = sizeY * text.length();
        return new Rectangle(pos.x, pos.y - sizeY, sizeX, sizeY);
    }

    @Override
    protected Vector<Point> getResizePoints() {
        Vector<Point> points=new Vector<>();
        points.add(pos);
        return points;
    }

    @Override
    public void resize(int resizePointRank, Point posTo) {
        if(resizePointRank==0){
            reposition(posTo);
        }
        resizePoint.reposition(null);
    }

    public void reposition(Point pos) {
        this.pos.x=pos.x;
        this.pos.y=pos.y;
    }
    @Override
    public DrawingItem createPreview() {
        return new DrawingText(text,pos,font,selectedColor,true);
    }
}
