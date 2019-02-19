package com.glede.paint;

import java.awt.*;
import java.io.Serializable;
import java.util.Vector;

/**
 * Created by Glede on 1/10/2019
 */

/**
 * A class that saves all information about one item
 * which should be painted on the paint board
 *
 * @author joker
 */
public abstract class DrawingItem implements Serializable {

    /**
     * Type of all inherited drawing item
     */
    public enum Type{
        IMAGE,TEXT,RECT,OVAL,SHAPE,POINTS,POLYGON,RESIZEPOINT
       ,图像,文字,矩形,圆形椭圆,形状,任意线,多边形,调整
    }

    /**
     * The color is used when you select an item on history panel
     */
    protected static final Color selectedColor=Color.RED;

    public static final Color getSelectedColor(){
        return selectedColor;
    }

    protected Type _type;
    protected transient ResizePoint resizePoint;
    protected transient HistoryButton relatedButton;
    protected boolean selectedPreview;

    protected DrawingItem(Type type, boolean isPreview){
        _type=type;
        selectedPreview = isPreview;
    }

    public Type getType(){
        return _type;
    }

    public void setType(Type t){
        _type =t;
    }

    public boolean isSelectedPreview() {
        return selectedPreview;
    }

    public void initResizePoint(){
        resizePoint=new ResizePoint(this);
    }

    public ResizePoint getResizePoint() {
        return resizePoint;
    }

    public HistoryButton getRelatedButton() {
        return relatedButton;
    }

    /**
     * Related button in history panel
     *
     * @param relatedButton
     */
    public void setRelatedButton(HistoryButton relatedButton) {
        this.relatedButton = relatedButton;
    }

    /**
     * Draw resize points in resize mode
     * @param graphics
     */
    public void drawResizePoint(Graphics graphics) {
        getResizePoint().draw(graphics);
    }

    /**
     * Draws the rectangle bound of an item when is selected in resize mode
     * @param graphics
     */
    public void drawBounds(Graphics graphics) {
        Graphics2D graphics2D = (Graphics2D) graphics;
        graphics2D.setStroke(StrokeLibrary.strokes[12].getStroke());
        graphics2D.setColor(Color.BLACK);
        graphics2D.draw(getBounds());
    }

    protected boolean isItem(){
        return !(this instanceof ResizePoint);
    }

    /**
     * Modify some of the properties of this item
     * @param resizePointRank selected resize point
     * @param posTo mouse position
     */
    public abstract void resize(int resizePointRank, Point posTo);

    /**
     * Reposition this item
     * @param pos
     */
    public abstract void reposition(Point pos);

    /**
     * Draw this item on param g
     * @param g
     */
    public abstract void draw(Graphics g);

    /**
     * @return A vector of points that can be selected in resize mode
     */
    protected abstract Vector<Point> getResizePoints();

    /**
     * @return A nearly copy of this item, used as preview
     */
    public abstract DrawingItem createPreview();

    /**
     * @param point
     * @return whether this item contains the point
     */
    public abstract boolean contains(Point point);

    /**
     * @return A rectangle which is the bound of this item
     */
    public abstract Rectangle getBounds();
}